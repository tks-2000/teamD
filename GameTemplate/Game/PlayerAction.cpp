#include "stdafx.h"
#include "PlayerAction.h"

namespace {
	/// @brief �ő�V�[���h�ϋv�l
	const float MAX_GUARD_DURABILITY = 100.0f;
	/// @brief �W���X�g�K�[�h�\�Ȏ���
	const float POSSIBLE_JUST_GUARD_TIME = 0.01f;
	/// @brief �W���X�g�K�[�h�������̋�������
	const float POWERUP_TIME = 10.0f;
	/// @brief �ʏ�̃K�[�h�ϋv�l�ቺ��
	const float NORMAL_GUARD_DECREASE_VALUE = 0.3f;
	/// @brief �h�䋭����Ԃ̃K�[�h�ϋv�l�ቺ��
	const float POWERFUIL_GUARD_DECREASE_VALUE = 0.15f;
	/// @brief �ʏ�̃K�[�h�ϋv�l�񕜗�
	const float NORMAL_GUARD_RECOVERY_VALUE = 0.3f;
	/// @brief ������Ԃ̃K�[�h�ϋv�l�񕜗�
	const float POWERFUIL_GUARD_RECOVERY_VALUE = 0.6f;
	/// @brief �L�b�N�\�ȋ���
	const float KICK_POSSIBLE_DISTANCE = 200.0f;
	/// @brief �L�b�N�\�Ȉ�v��
	const float KICK_POSSIBLE_RATE = 0.0f;
	/// @brief �ʏ�̃L�b�N��
	const float NORMAL_KICK_POWER = 1.5f;
	/// @brief ������Ԃ̃L�b�N��
	const float POWERFUL_KICK_POWER = 4.0f;
	/// @brief �A�C�e����������Ƃ��ɑ�����L�b�N��
	const float KICK_POWER_ADDITION_AMOUNT = 1.0f;
	/// @brief �L�b�N�{�^��
	const EnButton KICK_BUTTON = enButtonA;
}

PlayerAction::PlayerAction()
{
	//�������s���̂ŏ����������ɐݒ�
	m_setUp = false;
}

PlayerAction::~PlayerAction()
{

}

bool PlayerAction::Start()
{
	//�g�p����f�[�^�������ė���
	m_ball = FindGO<Ball>(BALL_NAME);
	m_timer = FindGO<Timer>(TIMER_NAME);
	m_se = FindGO<Se>(SE_NAME);
	m_score = FindGO<Score>(SCORE_NAME);
	//�K�[�h�ϋv�l�̏����l�͍ő��
	m_guardDurability = MAX_GUARD_DURABILITY;
	return true;
}

void PlayerAction::Update()
{
	//������������܂ł͏������s��Ȃ�
	if (m_setUp == false) {
		return;
	}
	//��Ԃɂ���ĕω�����p�����[�^�[������
	DetermineParameters();

	//�K�[�h���Ȃ�c
	if (IsGuard() == true) {
		//�K�[�h�̏������s��
		Guard();
	}
	//�K�[�h���Ă��Ȃ��Ȃ�c
	else {
		//�K�[�h�ϋv�l�񕜂̏������s��
		GuardDecreaseRecovery();
		//�K�[�h���Ԃ�0�łȂ�(���O�܂ŃK�[�h���Ă���)�Ƃ��c
		if (m_guardTime != 0.0f) {
			//�K�[�h������SE��炷
			m_se->PlayGuardEndSe();
			//�K�[�h���Ԃ�0�ɐݒ肷��
			m_guardTime = 0.0f;
		}
	}

	//�L�b�N�\�ȂƂ��ɃL�b�N�{�^���������ꂽ��c
	if (IsCanKick() == true && g_pad[m_playerNum]->IsTrigger(KICK_BUTTON) == true) {
		//�L�b�N�̏������s��
		Kick();
	}
}

void PlayerAction::SetPlayerNumber(const int num)
{
	//�����̃v���C���[�ԍ���ݒ�
	m_playerNum = num;
	//�����Ɠ����v���C���[�ԍ��̃f�[�^�����
	m_player = FindGO<Player>(PLAYER_NAME[m_playerNum]);
	m_plCollide = FindGO<PlayerCollide>(PLAYER_COLLID_NAME[m_playerNum]);
	m_plEffect = FindGO<PlayerEffect>(PLAYER_EFFECT_NAME[m_playerNum]);
	m_plMove = FindGO<PlayerMove>(PLAYER_MOVE_NAME[m_playerNum]);
	m_plReinforcement = FindGO<PlayerReinforcement>(PLAYER_REINFORCEMENT_NAME[m_playerNum]);
	//��������
	m_setUp = true;
}

bool PlayerAction::IsCanGuard()
{
	//�E�_���[�W���łȂ�
	//�E�K�[�h�u���C�N���Ă��Ȃ�
	//�E�^�C�}�[���Q�[���i�s��
	//�S�Ă���������Ă���ꍇ�c
	if (m_player->IsDamage() == false && m_guardBreak == false && m_timer->IsTimerExecution() == true) {
		//�K�[�h���\
		return true;
	}
	//�����łȂ��Ȃ�c
	else {
		//�K�[�h�s�\
		return false;
	}
}

bool PlayerAction::IsGuard()
{
	//�K�[�h�s��ԂȂ�c
	if (IsCanGuard() == false) {
		//�K�[�h���Ă��Ȃ�
		return false;
	}
	//�K�[�h�\��ԂȂ�c
	else {
		//�K�[�h�{�^����������Ă���Ȃ�c
		if (g_pad[m_playerNum]->IsPress(enButtonLB1) == true) {
			//�K�[�h���Ă���
			return true;
		}
		//�K�[�h�{�^����������Ă��Ȃ��Ȃ�c
		else {
			//�K�[�h���Ă��Ȃ�
			return false;
		}
	}
}

bool PlayerAction::IsCanKick()
{
	//�v���C���[�̌����ƃv���C���[����{�[���Ɍ������x�N�g���̓��ς��v�Z
	float matchRate = Dot(m_plMove->GetDirection(), m_plCollide->GetToBallVector());

	if (m_kickCooling == true) {
		m_kickKankaku += 1;
		if (m_kickKankaku == 20) {
			m_kickCooling = false;
			m_kickKankaku = 0;
		}
		return false;
	}

	//�E�v���C���[���_���[�W��ԂłȂ�
	//�E�v���C���[���K�[�h���łȂ�
	//�E�v���C���[�ƃ{�[���Ƃ̋������L�b�N�\�͈͈ȉ�
	//�E�v���C���[�̌����ƃv���C���[����{�[���Ɍ������x�N�g���̓��ς̌��ʂ���v���𒴂��Ă���
	//�S�Ă𖞂����Ă���ꍇ
	if (m_player->IsDamage() == false &&
		IsGuard() == false && 
		m_plCollide->GetBallDistance() <= KICK_POSSIBLE_DISTANCE &&
		matchRate > KICK_POSSIBLE_RATE) {
		//�L�b�N�\
		return true;
	}
	//�ǂꂩ��ł��������Ă��Ȃ��ꍇ�c
	else {
		//�L�b�N�s�\
		return false;
	}
}

void PlayerAction::DetermineParameters()
{
	//�v���C���[��������ԂȂ�c
	if (m_plReinforcement->IsSelfPowerUp() == true) {
		//�K�[�h�ϋv�l�񕜗ʂ�������Ԃ̕��ɐݒ�
		m_guardRecoveryValue = POWERFUIL_GUARD_RECOVERY_VALUE;
		//�L�b�N�͂�������Ԃ̕��ɐݒ�
		m_kickPower = POWERFUL_KICK_POWER;
	}
	//�v���C���[��������ԂłȂ��Ȃ�c
	else {
		//�K�[�h�ϋv�l�񕜗ʂ�ʏ��Ԃ̕��ɐݒ�
		m_guardRecoveryValue = NORMAL_GUARD_RECOVERY_VALUE;
		//�L�b�N�͂�ʏ��Ԃ̕��ɐݒ�
		m_kickPower = NORMAL_KICK_POWER;
	}

	//�v���C���[���h�䋭����Ԃ�������c
	if (m_plReinforcement->IsDefenseUp() == true) {
		//�K�[�h�ϋv�l�ቺ�ʂ�h�䋭����Ԃ̕��ɐݒ�
		m_guardDecreaseValue = POWERFUIL_GUARD_DECREASE_VALUE;
	}
	//�v���C���[���h�䋭����ԂłȂ��Ȃ�c
	else {
		//�K�[�h�ϋv�l�ቺ�ʂ�ʏ��Ԃ̕��ɐݒ�
		m_guardDecreaseValue = NORMAL_GUARD_DECREASE_VALUE;
	}

	//�v���C���[���L�b�N�͋�����ԂȂ�c
	if (m_plReinforcement->IsKickUp() == true) {
		//�L�b�N�͂����Z����
		m_kickPower += KICK_POWER_ADDITION_AMOUNT;
	}
}

void PlayerAction::Guard()
{
	//�K�[�h���͈ړ����x��������
	m_guardMoveSpeed = m_plMove->GetMoveSpeed();
	m_guardMoveSpeed.x /= 2.0f;
	m_guardMoveSpeed.z /= 2.0f;
	m_plMove->SetMoveSpeed(m_guardMoveSpeed);

	//�K�[�h���͑ϋv�l�����葱����
	m_guardDurability -= m_guardDecreaseValue;

	//�K�[�h�ϋv�l��0�ȉ��ɂȂ�����c
	if (m_guardDurability <= 0.0f) {

		//�K�[�h�G�t�F�N�g�������ăK�[�h�u���C�N�G�t�F�N�g���Đ�����
		m_plEffect->StopGuardEffect();
		m_plEffect->PlayGuardBreakEffect();
		//�s���s�\�G�t�F�N�g���Đ�����
		m_plEffect->PlayKnockOutEffect();

		//SE���炷
		m_se->PlayBreakSe();
		m_se->PlayStanSe(m_playerNum);

		//�K�[�h�ϋv�l���O�ɐݒ�
		m_guardDurability = 0.0f;
		//�K�[�h�u���C�N��ԂɕύX
		m_guardBreak = true;

		//�K�[�h���o���Ȃ��Ȃ�̂ŏ������I���
		return;
	}

	//�V�[���h�G�t�F�N�g��������
	m_plEffect->PlayGuardEffect();

	//�K�[�h���Ԃ�0(���O�܂ŃK�[�h���Ă��Ȃ�����)�ꍇ�c
	if (m_guardTime == 0.0f) {
		//�K�[�h�J�n�G�t�F�N�g��SE���Đ�
		m_plEffect->PlayGuardBeginEffect();
		m_se->PlayGuardStartSe();
	}

	//�K�[�h���Ԃ�i�߂�
	m_guardTime += g_gameTime->GetFrameDeltaTime() * 0.1f;
}

void PlayerAction::GuardDecreaseRecovery()
{
	//�K�[�h�ϋv�l���ő�l�������ꍇ�c
	if (m_guardDurability == MAX_GUARD_DURABILITY) {
		//�������I������
		return;
	}

	//�K�[�h�ϋv�l�ɃK�[�h�ϋv�l�񕜗ʂ����Z����
	m_guardDurability += m_guardRecoveryValue;

	//�K�[�h�ϋv�l���ő�l�ȏ�ɂȂ�����c
	if (m_guardDurability >= MAX_GUARD_DURABILITY) {
		//�K�[�h�u���C�N����������c
		if (m_guardBreak == true) {
			//�_���[�W���łȂ��Ȃ�c
			if (m_player->IsDamage() == false) {
				//�s���s�\�G�t�F�N�g��SE���~
				m_plEffect->StopKnockOutEffect();
				m_se->StopStanSe(m_playerNum);
			}

			//�K�[�h�񕜂̃G�t�F�N�g��SE���Đ�
			m_plEffect->PlayShieldRepairEffect();
			m_se->PlayShieldRepairSe();

			//�K�[�h�u���C�N��Ԃ��畜�A����
			m_guardBreak = false;
		}
		//�K�[�h�ϋv�l���ő�l�ɐݒ肷��
		m_guardDurability = MAX_GUARD_DURABILITY;
	}
}

void PlayerAction::Kick()
{
	//�{�[���ړ��������v���C���[�̌����ɐݒ�
	m_ball->SetMoveDirection(m_plMove->GetDirection());
	//�{�[���̑��x�ɃL�b�N�͂�������
	m_ball->Acceleration(m_kickPower);
	//�{�[���̃��C�g�J���[�������̃��C�g�J���[�ɐݒ�
	m_ball->SetBallLightColor(m_player->GetPlayerColor());
	//�{�[���Ɏ����̃v���C���[�ԍ���`����
	m_ball->SetPlayerInformation(m_playerNum);
	//�{�[���𓮂���
	m_ball->MoveStart();

	//�v���C���[��������ԂȂ�c
	if (m_plReinforcement->IsSelfPowerUp() == true) {
		//������Ԃ̃L�b�NSE��炷
		m_se->PlayPoweredKickSe();
	}
	//������ԂłȂ��Ȃ�c
	else {
		//�ʏ�̃L�b�NSE��炷
		m_se->PlayKickSe();
	}

	m_kickCooling = true;

	//�L�b�N�G�t�F�N�g���Đ�
	m_plEffect->PlayKickEffect();
}