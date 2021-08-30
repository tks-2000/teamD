#include "stdafx.h"
#include "PlayerMove.h"

namespace {
	/// @brief �ʏ�̈ړ����x
	const float NORMAL_VELOCITY = 0.9f;
	/// @brief �_�b�V���̈ړ����x
	const float DASH_VELOCITY = 0.95f;
	/// @brief �{�[���ɐڐG���锻��
	const float COLLIDE_RATE = 0.0f;
	/// @brief �ʏ펞�̖��C��
	const float NORMAL_FRICTION = 0.01f;
	/// @brief �_���[�W���̖��C��
	const float DAMAGE_FRICYION = 0.001f;
	/// @brief �ʏ펞�̏d��
	const float NORMAL_GRAVITY = 5.0f;
	/// @brief �_���[�W���̏d��
	const float DAMAGE_GRAVITY = 2.5f;
	/// @brief �_���[�W���󂯂ĕ��A����̂ɂ����鎞��
	const float DAMAGE_RETURN_TIME = 100.0f;
	/// @brief �������ɐ�����Ԑ���
	const float BLOW_AWAY_RATE = 2.0f;
	/// @brief �c�����ɐ�����Ԑ���
	const float BLOW_AWAY_HEIGHT_RATE = 1.0f;
	/// @brief �A�C�e����������Ƃ��̐�����Ԑ���
	const float DECREASE_BLOW_AWAY_RATE = 1.0f;
	/// @brief �A�C�e����������Ƃ��ɑ����鑬�x
	const float VELOCITY_ADDITION_AMOUNT = 0.02f;
	/// @brief �X�^�~�i�̍ő�l
	const float MAX_STANIMA = 6.0f;
	/// @brief �ʏ�̃X�^�~�i�ቺ��
	const float STAMINA_DECREASE_VALUE = 2.0f;
	/// @brief ������Ԃ̃X�^�~�i�ቺ��
	const float POWERFUIL_STAMINA_DECREASE_VALUE = 1.0f;
	/// @brief �����悭�������������ɂȂ�{�[���̑��x
	const float STRONG_HIT = 20.0f;
}

PlayerMove::PlayerMove()
{
	m_setUp = false;
}

PlayerMove::~PlayerMove()
{

}

bool PlayerMove::Start()
{
	m_se = FindGO<Se>(SE_NAME);
	m_ball = FindGO<Ball>(BALL_NAME);
	m_stamina = MAX_STANIMA;
	return true;
}

void PlayerMove::SetPlayerNumber(const int plNum)
{
	m_playerNum = plNum;
	m_player = FindGO<Player>(PLAYER_NAME[m_playerNum]);
	m_plAction = FindGO<PlayerAction>(PLAYER_ACTION_NAME[m_playerNum]);
	m_plEffect = FindGO<PlayerEffect>(PLAYER_EFFECT_NAME[m_playerNum]);
	m_plReinforcement = FindGO<PlayerReinforcement>(PLAYER_REINFORCEMENT_NAME[m_playerNum]);
	m_setUp = true;
}

void PlayerMove::Move()
{
	// �X�e�B�b�N���͂ŃJ���������Ɉړ�
	m_moveSpeed += g_camera3D->GetRight() * m_Lstickx;
	m_moveSpeed += g_camera3D->GetForward() * m_Lsticky;

	//�����̏�Ԃɂ���Ĉړ��Ɏg���p�����[�^�[������
	DetermineParameters();

	//�_�b�V����
	if (IsDash() == true) {
		//�_�b�V�������s
		Dash();
	}
	//�_�b�V�����Ă��Ȃ��Ƃ�
	else {
		//���s�����s
		Walk();
		if (m_stamina < MAX_STANIMA) {
			//�X�^�~�i���񕜂���
			StaminaRecovery();
		}
	}

	//�X�^�~�i�̏�Ԃ𒲂ׂ�
	StaminaManagement();

	//���x�����Z����
	m_moveVelocity += m_addVelocity;
	//�ړ����x��ݒ�
	m_moveSpeed *= m_moveVelocity;
	//�d�͂�������
	m_moveSpeed.y -= m_gravity;
	//�ړ����x�ɉ��������C�͂�������
	m_moveSpeed -= m_moveSpeed * m_friction;

	//Y�����̈ړ����x���������ړ����x���擾
	Vector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	//�ړ����x�����ȉ��ɂȂ�����~�܂�
	if (moveSpeedXZ.LengthSq() < 0.1f) {
		MoveStop();
	}
	//m_player->SetMoveSpeed(m_moveSpeed);
	m_player->SetCharaCon(m_moveSpeed);
}

void PlayerMove::DetermineParameters()
{
	//�_���[�W��Ԃ��ǂ����ŏ����𕪂���
	if (m_player->IsDamage() == true) {
		//�_���[�W���ɕω�����p�����[�^�[��ݒ肷��
		m_gravity = NORMAL_GRAVITY;
		m_friction = NORMAL_FRICTION;
	}
	//�����łȂ��Ȃ�
	else {
		//�ʏ�p�����[�^�[��ݒ肷��
		m_gravity = DAMAGE_GRAVITY;
		m_friction = DAMAGE_FRICYION;
	}

	//�v���C���[���p���[�A�b�v��Ԃ̂Ƃ�
	if (m_plReinforcement->IsPowerUp() == true) {
		//�X�^�~�i������y��
		m_staminaDecreaseValue = POWERFUIL_STAMINA_DECREASE_VALUE;
	}
	//�����łȂ��Ȃ�
	else {
		//�ʏ�̃X�^�~�i����
		m_staminaDecreaseValue = STAMINA_DECREASE_VALUE;
	}

	//�v���C���[���h�䋭����Ԃ�������c
	if (m_plReinforcement->IsDefenseUp() == true) {
		//������Ԑ�����h�䋭����Ԓ��̐����ɂ���
		m_blowAwayRate = DECREASE_BLOW_AWAY_RATE;
	}
	//�v���C���[���h�䋭����ԂłȂ��ꍇ�c
	else {
		//������Ԑ�����ʏ펞�̐����ɂ���
		m_blowAwayRate = BLOW_AWAY_RATE;
	}

	//�v���C���[�����x������Ԃ�������c
	if (m_plReinforcement->IsSpeedUp() == true && m_player->IsDamage() == false) {
		//���Z���鑬�x��ݒ肷��
		m_addVelocity = VELOCITY_ADDITION_AMOUNT;
	}
	//�v���C���[�����x������ԂłȂ��ꍇ�c
	else {
		//���Z���鑬�x���O�ɂ���
		m_addVelocity = 0.0f;
	}
}

void PlayerMove::ToBallVectorCalculation()
{
	//�{�[���̍��W���玩���̍��W�������Ď�������{�[���Ɍ������ĐL�т�x�N�g�����v�Z����
	m_toBallVec = m_ball->GetPosition() - m_player->GetPosition();
	//�{�[���Ƃ̋����������Ōv�Z����
	BallDistanceCalculation();
	//�c����������
	m_toBallVec.y = 0.0f;
	//���K������
	m_toBallVec.Normalize();
	
}

void PlayerMove::BallDistanceCalculation()
{
	//�{�[���Ɍ������ĐL�т�x�N�g�����璷�����擾����
	m_ballDistance = m_toBallVec.Length();
}

void PlayerMove::BallCollide()
{
	//�{�[���ւ̃x�N�g���ƃ{�[���̌����œ�����p�x�����߂�
	float matchRate = Dot(m_ball->GetMoveDirection(), m_toBallVec);
	//�{�[���������Ă��Ȃ��E�v���C���[���K�[�h���E�ڐG����łȂ��ꍇ�c
	if (m_ball->IsMove() == false || m_plAction->IsGuard() == true || matchRate > COLLIDE_RATE) {
		//�������I������
		return;
	}

	//�{�[���Ǝ����̈ʒu���琁����΂������������߂�
	Vector3 repulsiveForce = m_player->GetPosition() - m_ball->GetPosition();
	//�c�����̐���������
	repulsiveForce.y = 0.0f;
	//���K�����ĕ����x�N�g���ɂ���
	repulsiveForce.Normalize();
	//�{�[���̈ړ������𐁂���ԕ����Ƌt�����ɐݒ肷��
	m_ball->SetMoveDirection(repulsiveForce * -1.0f);

	//�v���C���[�����S���̖��G���Ԓ��̏ꍇ�c
	if (m_player->IsDie() == true) {
		//�_���[�W���󂯂Ȃ������Ƃ���SE��炷
		m_se->PlayNoDamageCollideSe();
		//�������I������
		return;
	}

	//������Ԑ�������Z���Ĉړ��ʂ����߂�
	repulsiveForce *= m_ball->GetVelocity() * m_blowAwayRate;

	//�c�����͕ʂɌv�Z����
	repulsiveForce.y = m_ball->GetVelocity() * BLOW_AWAY_HEIGHT_RATE;

	//�ړ����x�ɐ�����Ԑ�����ݒ肷��
	m_moveSpeed = repulsiveForce * 2.0f;

	//�K�[�h�u���C�N���̏ꍇ�c
	if (m_plAction->IsGuardBreak() == true) {
		//�s���s�\�G�t�F�N�g������
		m_plEffect->StopKnockOutEffect();
		//�s���s�\SE������
		m_se->StopStanSe(m_playerNum);
	}
	//�_���[�W���łȂ��ꍇ�c
	if (m_player->IsDamage() == false) {
		//�s���s�\�G�t�F�N�g���Đ�
		m_plEffect->PlayKnockOutEffect();
		//�s���s�\SE��炷
		m_se->PlayStanSe(m_playerNum);
	}

	//�v���C���[���_���[�W���ɐݒ肷��
	m_player->SetDamage();

	//�{�[���̑��x�������������������̂ɂȂ鑬�x�𒴂��Ă�����c
	if (m_ball->GetVelocity() > STRONG_HIT) {
		//������������SE��炷
		m_se->PlayStrongCollideSe();
	}
	//�{�[���̑��x�������������������̂ɂȂ鑬�x�𒴂��Ă��Ȃ�������c
	else {
		//�キ��������SE��炷
		m_se->PlayWeakCollideSe();
	}
	
	//�U�����Ă����v���C���[�̔ԍ����L������
	m_player->SetHaveAttackedPlayer(m_ball->GetPlayerInformation());

	//�U�����Ă����v���C���[�������ł͂Ȃ��ꍇ�c
	if (m_player->GetHaveAttackedPlayer() != m_playerNum) {
		//�U�����Ă����v���C���[�ɃX�R�A�����Z����
		m_score->AddScore200(m_player->GetHaveAttackedPlayer());
	}
}

void PlayerMove::Walk()
{
	//�ړ����x��W���ɂ���
	m_moveVelocity = NORMAL_VELOCITY;
	//�X�^�~�i���񕜂�����
	StaminaRecovery();
	//�����A�j���[�V�������Đ�
	m_player->SetAnimation(enAnimation_Walk);
}

void PlayerMove::Dash()
{
	//�ړ����x���_�b�V�����̑��x�ɕύX
	m_moveVelocity = DASH_VELOCITY;
	//�X�^�~�i��ቺ������
	m_stamina -= g_gameTime->GetFrameDeltaTime() * m_staminaDecreaseValue;
	//�_�b�V���G�t�F�N�g�Đ�����
	m_plEffect->PlayDashEffect();
	//�_�b�V���A�j���[�V�������Đ�
	m_player->SetAnimation(enAnimation_Run);
}

void PlayerMove::StaminaRecovery()
{
	//�X�^�~�i�ő�l��������c
	if (m_stamina == MAX_STANIMA) {
		//�I������
		return;
	}
	//�X�^�~�i���񕜂���
	m_stamina += g_gameTime->GetFrameDeltaTime();
	//�X�^�~�i���ő�l�𒴂�����c
	if (m_stamina > MAX_STANIMA) {
		//�_�b�V���s��������c
		if (m_dash == false) {
			//�X�^�~�i�񕜂�SE��炷
			m_se->PlayStaminaRecoverySe();
			//�_�b�V�����\�ɂ���
			m_dash = true;
		}
		//�X�^�~�i���ő�l�ɐݒ�
		m_stamina = MAX_STANIMA;
	}
}

void PlayerMove::Rotation()
{
	//�ړ����x�ŕ��������߂�
	if (m_player->IsDamage() == false && m_plAction->IsGuard() == false && m_plAction->IsGuardBreak() == false) {
		if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f) {
			m_direction = m_moveSpeed;
			m_direction.y = 0.0f;
			m_direction.Normalize();
			m_player->SetDirection(m_direction);
		}
	}
}

void PlayerMove::Update()
{
	//�����f�[�^�̏������I���܂ł͎��s���Ȃ�
	if (m_setUp == false) {
		return;
	}
	m_Lstickx = g_pad[m_playerNum]->GetLStickXF();
	m_Lsticky = g_pad[m_playerNum]->GetLStickYF();
	ToBallVectorCalculation();
	Move();
	Rotation();
}

void PlayerMove::StaminaManagement()
{
	//�X�^�~�i�������Ȃ�����c
	if (m_stamina < 0.0f) {
		//�_�b�V���ł��Ȃ�����
		m_dash = false;
		//�X�^�~�i�؂��SE��炷
		m_se->PlayStaminaOverSe();
	}
}

bool PlayerMove::IsDash()const
{
	//�_�b�V���\�ŃK�[�h���Ă��Ȃ��Ƃ���RB1��������Ă�����c
	if (m_dash == true && m_plAction->IsGuard() == false && g_pad[m_playerNum]->IsPress(enButtonRB1)) {
		//�X�e�B�b�N���͂���������c
		if (m_Lstickx != 0.0f || m_Lsticky != 0.0f) {
			//�_�b�V�����Ă���
			return true;
		}
		//�X�e�B�b�N���͂�����������c
		else {
			//�_�b�V�����Ă��Ȃ�
			return false;
		}
	}
	//�_�b�V���s�\�E�K�[�h���ERB1��������Ă��Ȃ��ꍇ
	else {
		//�_�b�V�����Ă��Ȃ�
		return false;
	}
}