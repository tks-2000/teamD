#include "stdafx.h"
#include "PlayerAction.h"

namespace {
	/// @brief �K�[�h�\�ȋ���
	const float GUARD_DISTANCE = 90.0f;
	/// @brief �ő�V�[���h�ϋv�l
	const float MAX_GUARD_DURABILITY = 100.0f;
	/// @brief �W���X�g�K�[�h�\�Ȏ���
	const float POSSIBLE_JUST_GUARD_TIME = 0.01f;
	/// @brief �W���X�g�K�[�h�������̋�������
	const float POWERUP_TIME = 10.0f;
	/// @brief �ʏ�̃K�[�h�ϋv�l�ቺ��
	const float GUARD_DECREASE_VALUE = 0.3f;
	/// @brief ������Ԃ̃K�[�h�ϋv�l�ቺ��
	const float POWERFUIL_GUARD_DECREASE_VALUE = 0.15f;
	/// @brief �A�C�e����������Ƃ��̃K�[�h�ϋv�l�y����
	const float GUARD_ADDITION_AMOUNT = 0.1f;
}

PlayerAction::PlayerAction()
{

}

PlayerAction::~PlayerAction()
{

}

bool PlayerAction::Start()
{
	m_timer = FindGO<Timer>(TIMER_NAME);
	return true;
}

void PlayerAction::SetPlayerNumber(const int num)
{
	m_playerNum = num;
	m_player = FindGO<Player>(PLAYER_NAME[m_playerNum]);
	m_plMove = FindGO<PlayerMove>(PLAYER_MOVE_NAME[m_playerNum]);
	m_plReinforcement = FindGO<PlayerReinforcement>(PLAYER_REINFORCEMENT_NAME[m_playerNum]);
}

bool PlayerAction::CheckGuard()
{
	if (m_breakGuard == false && m_timer->IsTimerExecution() == true) {
		return true;
	}
	else {
		return false;
	}
}

void PlayerAction::Guard()
{
	/// @brief �K�[�h���͈ړ����x��������
	m_guardMoveSpeed = m_player->GetMoveSpeed();
	m_guardMoveSpeed.x /= 2.0f;
	m_guardMoveSpeed.z /= 2.0f;
	m_player->SetMoveSpeed(m_guardMoveSpeed);

	/// @brief �K�[�h���͑ϋv�l(guardDurability)�����葱����
	if (m_plReinforcement->IsPowerUp() == true) {
		m_guradDecreaseValue = POWERFUIL_GUARD_DECREASE_VALUE;
	}
	else {
		m_guradDecreaseValue = GUARD_DECREASE_VALUE;
	}

	if (m_plReinforcement->IsDefenseUp() == true) {
		m_guradDecreaseValue -= GUARD_ADDITION_AMOUNT;
	}

	m_guardDurability -= m_guradDecreaseValue;

	//�V�[���h�G�t�F�N�g��������//
	m_plEffect->PlayGuardEffect();

	/// @brief �W���X�g�K�[�h���莞�Ԃ�i�߂�
	m_justGuardTime += g_gameTime->GetFrameDeltaTime() * 0.1f;

	/// @brief �K�[�h�ϋv�l�������Ȃ�����
	if (m_guardDurability <= 0.0f) {
		/// @brief �K�[�h�u���C�N����
		m_guardDurability = 0.0f;
		m_breakGuard = true;
		m_plEffect->StopGuardEffect();
		m_plEffect->PlayGuardBreakEffect();
		m_plEffect->PlayKnockOutEffect();
		m_se->PlayStanSe(m_playerNum);

		m_se->PlayBreakSe();
	}

	/// @brief �{�[���������Ă��Ȃ���΃K�[�h������s��Ȃ�
	if (m_ball->IsMove() == false) {
		return;
	}

	/// @brief �ڐG������
	if (m_ballDistance < GUARD_DISTANCE) {
		/// @brief ��x���ڐG���Ă��Ȃ��ꍇ
		if (m_shieldHit == false) {

			//�K�[�h�q�b�g�G�t�F�N�g�̔���
			m_plEffect->PlayShieldHitEffect();

			//�K�[�h�q�b�gse�̍Đ�����
			float takeDamage = m_ball->GetVelocity() * 3.0f;

			if (m_guardDurability <= takeDamage) {
				m_se->PlayBreakSe();
			}
			else {
				m_se->PlayShieldHitSe();
			}

			m_shieldHit = true;

		}
		GuardCollide();
	}
	else {
		/// @brief �ڐG���Ă��Ȃ�
		m_shieldHit = false;
	}
}

void PlayerAction::GuardCollide()
{

	/// @brief �W���X�g�K�[�h���莞�ԓ��Ȃ�W���X�g�K�[�h����
	if (m_justGuardTime < POSSIBLE_JUST_GUARD_TIME) {
		m_ball->SetVelocity(0.0f);

		/// @brief �W���X�g�K�[�h�G�t�F�N�g�̍Đ�
		m_plEffect->PlayJustGuardEffect();
		m_se->PlayJustGuardSe();
		m_plReinforcement->ChangePowerUp();
	}
	else {
		/// @brief �{�[���̐����ɉ����đϋv�l�����炷
		float shieldDamage = m_ball->GetVelocity() * m_guradDecreaseValue * 10.0f;
		m_guardDurability -= shieldDamage;
		/// @brief �K�[�h�u���C�N�����ꍇ
		if (m_guardDurability <= 0.0f)
		{
			/// @brief �K�[�h�G�t�F�N�g�������ăK�[�h�u���C�N�G�t�F�N�g���Đ�����
			m_plEffect->StopGuardEffect();
			m_plEffect->PlayGuardBreakEffect();
			m_plEffect->PlayKnockOutEffect();
			m_guardDurability = 0.0f;
			m_breakGuard = true;

			m_se->PlayBreakSe();
			m_se->PlayStanSe(m_playerNum);

			return;
		}

		/// @brief �{�[���̐����ɉ����ăm�b�N�o�b�N����B
		Vector3 repulsiveForce = m_toBallVec * -1.0f;
		repulsiveForce.Normalize();
		repulsiveForce *= m_ball->GetVelocity();
		repulsiveForce.y = m_ball->GetVelocity() * 0.1f;
		m_plMove->SetMoveSpeed(repulsiveForce);
		m_ball->SetVelocity(m_ball->GetVelocity() / 2.0f);
		m_ball->SetMoveDirection(repulsiveForce * -1.0f);
	}

}

void PlayerAction::Update()
{

}