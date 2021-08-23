#include "stdafx.h"
#include "PlayerMove.h"

namespace {
	/// @brief �ʏ�̈ړ����x
	const float NORMAL_VELOCITY = 0.9f;
	/// @brief �_�b�V���̈ړ����x
	const float DASH_VELOCITY = 0.95f;
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
	/// @brief ���X�|�[���R�}���h�����������Ĕ�������܂ł̎���
	const float RESPAWN_TIME = 5.0f;
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
	}

	//���x�����Z����
	m_moveVelocity += m_addVelocity;
	//�ړ����x��ݒ�
	m_moveSpeed *= m_moveVelocity;
	//�ړ����x�ɉ��������C�͂�������
	m_moveSpeed -= m_moveSpeed * m_friction;
	//�d�͂�������
	m_moveSpeed.y -= m_gravity;

	//Y�����̈ړ����x���������ړ����x���擾
	Vector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	//�ړ����x�����ȉ��ɂȂ�����~�܂�
	if (moveSpeedXZ.LengthSq() < 0.1f) {
		MoveStop();
	}
	m_player->SetMoveSpeed(m_moveSpeed);
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
	//�X�^�~�i���񕜂���
	m_stamina += g_gameTime->GetFrameDeltaTime();
	//�X�^�~�i���ő�l�𒴂�����c
	if (m_stamina > MAX_STANIMA) {
		//�X�^�~�i���ő�l�ɐݒ�
		m_stamina = MAX_STANIMA;
	}
}

void PlayerMove::ReSpawnCountAdd()
{
	//���X�|�[�����Ԃ����Z
	m_reSpawnTime += g_gameTime->GetFrameDeltaTime();
	//���X�|�[���\�Ȏ��Ԃ𒴂�����c
	if (m_reSpawnTime > RESPAWN_TIME) {
		//�v���C���[�����X�|�[��������
		m_player->ReSpawn();
		m_reSpawnTime = 0.0f;
	}
}

void PlayerMove::ReSpawn()
{

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
	if (m_setUp == false) {
		return;
	}
	m_Lstickx = g_pad[m_playerNum]->GetLStickXF();
	m_Lsticky = g_pad[m_playerNum]->GetLStickYF();
	Move();
	Rotation();
}

void PlayerMove::CheckDash()
{
	//�X�^�~�i�������Ȃ�����c
	if (m_stamina < 0.0f) {
		//�_�b�V���ł��Ȃ�����
		m_dash = false;
		//�X�^�~�i�؂��SE��炷
		m_se->PlayStaminaOverSe();
	}
	//�X�^�~�i���ő�l�𒴂�����c
	if (m_stamina > MAX_STANIMA) {
		//�_�b�V�����\�ɂ���
		m_dash = true;
		//�X�^�~�i�񕜂�SE��炷
		m_se->PlayStaminaRecoverySe();
	}
}

bool PlayerMove::IsDash()const
{
	if (m_dash == true && m_plAction->IsGuard() == false && g_pad[m_playerNum]->IsPress(enButtonRB1)) {
		if (m_Lstickx != FLOAT_0 || m_Lsticky != FLOAT_0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}