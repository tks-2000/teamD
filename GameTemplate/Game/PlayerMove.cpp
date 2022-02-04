#include "stdafx.h"
#include "PlayerMove.h"

namespace {
	/// @brief �ʏ�̈ړ����x
	const float NORMAL_VELOCITY = 0.9f;
	/// @brief �_�b�V���̈ړ����x
	const float DASH_VELOCITY = 0.95f;
	/// @brief �{�[���ɐڐG���锻��
	const float COLLIDE_RATE = 0.0f;
	/// @brief �{�[���ɐڐG���鋗��
	const float COLLIDE_DISTANCE = 80.0f;
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
	//�g�p����f�[�^�������ė���
	m_ball = FindGO<Ball>(BALL_NAME);
	m_se = FindGO<Se>(SE_NAME);
	m_timer = FindGO<Timer>(TIMER_NAME);
	//�X�^�~�i�̏����l�͍ő��
	m_stamina = MAX_STANIMA;
	return true;
}

void PlayerMove::Update()
{
	//�����f�[�^�̏������I���܂ł͎��s���Ȃ�
	if (m_setUp == false) {
		return;
	}

	//�X�e�B�b�N���͂��󂯎��
	m_Lstickx = g_pad[m_playerNum]->GetLStickXF();
	m_Lsticky = g_pad[m_playerNum]->GetLStickYF();

	//�ړ��ł��Ȃ��Ƃ��c
	if (IsCanMove() == false) {
		//�X�e�B�b�N���͂��󂯕t���Ȃ�
		m_Lstickx = 0.0f;
		m_Lsticky = 0.0f;
	}

	//�ړ��E��]���s��
	Move();
	Rotation();

	//�ړ��Ɖ�]��`����
	m_player->SetCharaCon(m_moveSpeed);
	m_player->SetQrot(m_qRot);
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

bool PlayerMove::IsCanMove() const
{
	//�^�C�}�[���Q�[���i�s���łȂ��E�_���[�W���E�K�[�h�u���C�N���̏ꍇ
	if (m_timer->IsTimerExecution() == false || m_player->IsDamage() == true || m_plAction->IsGuardBreak() == true) {
		//�ړ��ł��Ȃ�
		return false;
	}
	//����ȊO�ł́c
	else {
		//�ړ��ł���
		return true;
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
	if (m_plReinforcement->IsSelfPowerUp() == true) {
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
		//�X�^�~�i���񕜂���
		StaminaRecovery();
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
	if (m_stamina >= MAX_STANIMA) {
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

void PlayerMove::Rotation()
{
	//�_���[�W���E�K�[�h���E�K�[�h�u���C�N���͉�]���s��Ȃ�
	if (m_player->IsDamage() == true || m_plAction->IsGuard() == true || m_plAction->IsGuardBreak() == true) {
		//�ҋ@�A�j���[�V�������Đ�
		m_player->SetAnimation(enAnimation_Idle);
		return;
	}
	//�����Ă��Ȃ��Ƃ�����]���s��Ȃ�
	if (m_moveSpeed.x == 0.0f && m_moveSpeed.z == 0.0f) {
		//�ҋ@�A�j���[�V�������Đ�
		m_player->SetAnimation(enAnimation_Idle);
		return;
	}

	//�ړ����x�ŕ��������߂�
	m_direction = m_moveSpeed;
	//�c�����̗v�f������
	m_direction.y = 0.0f;
	//���K�����ĕ����x�N�g���ɂ���
	m_direction.Normalize();
	//�v���C���[�ɕ�����n��
	m_player->SetDirection(m_direction);
	//���������]�����߂�
	m_qRot.SetRotation(Vector3::AxisY, atan2(m_direction.x, m_direction.z));
}