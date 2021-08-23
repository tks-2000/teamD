#include "stdafx.h"
#include "PlayerAction.h"

namespace {
	/// @brief ガード可能な距離
	const float GUARD_DISTANCE = 90.0f;
	/// @brief 最大シールド耐久値
	const float MAX_GUARD_DURABILITY = 100.0f;
	/// @brief ジャストガード可能な時間
	const float POSSIBLE_JUST_GUARD_TIME = 0.01f;
	/// @brief ジャストガード発動時の強化時間
	const float POWERUP_TIME = 10.0f;
	/// @brief 通常のガード耐久値低下量
	const float GUARD_DECREASE_VALUE = 0.3f;
	/// @brief 強化状態のガード耐久値低下量
	const float POWERFUIL_GUARD_DECREASE_VALUE = 0.15f;
	/// @brief アイテムを取ったときのガード耐久値軽減率
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
	/// @brief ガード中は移動速度を下げる
	m_guardMoveSpeed = m_player->GetMoveSpeed();
	m_guardMoveSpeed.x /= 2.0f;
	m_guardMoveSpeed.z /= 2.0f;
	m_player->SetMoveSpeed(m_guardMoveSpeed);

	/// @brief ガード中は耐久値(guardDurability)が減り続ける
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

	//シールドエフェクト発生処理//
	m_plEffect->PlayGuardEffect();

	/// @brief ジャストガード判定時間を進める
	m_justGuardTime += g_gameTime->GetFrameDeltaTime() * 0.1f;

	/// @brief ガード耐久値が無くなったら
	if (m_guardDurability <= 0.0f) {
		/// @brief ガードブレイクする
		m_guardDurability = 0.0f;
		m_breakGuard = true;
		m_plEffect->StopGuardEffect();
		m_plEffect->PlayGuardBreakEffect();
		m_plEffect->PlayKnockOutEffect();
		m_se->PlayStanSe(m_playerNum);

		m_se->PlayBreakSe();
	}

	/// @brief ボールが動いていなければガード判定を行わない
	if (m_ball->IsMove() == false) {
		return;
	}

	/// @brief 接触したら
	if (m_ballDistance < GUARD_DISTANCE) {
		/// @brief 一度も接触していない場合
		if (m_shieldHit == false) {

			//ガードヒットエフェクトの発生
			m_plEffect->PlayShieldHitEffect();

			//ガードヒットseの再生処理
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
		/// @brief 接触していない
		m_shieldHit = false;
	}
}

void PlayerAction::GuardCollide()
{

	/// @brief ジャストガード判定時間内ならジャストガード発動
	if (m_justGuardTime < POSSIBLE_JUST_GUARD_TIME) {
		m_ball->SetVelocity(0.0f);

		/// @brief ジャストガードエフェクトの再生
		m_plEffect->PlayJustGuardEffect();
		m_se->PlayJustGuardSe();
		m_plReinforcement->ChangePowerUp();
	}
	else {
		/// @brief ボールの勢いに応じて耐久値を減らす
		float shieldDamage = m_ball->GetVelocity() * m_guradDecreaseValue * 10.0f;
		m_guardDurability -= shieldDamage;
		/// @brief ガードブレイクした場合
		if (m_guardDurability <= 0.0f)
		{
			/// @brief ガードエフェクトを消してガードブレイクエフェクトを再生する
			m_plEffect->StopGuardEffect();
			m_plEffect->PlayGuardBreakEffect();
			m_plEffect->PlayKnockOutEffect();
			m_guardDurability = 0.0f;
			m_breakGuard = true;

			m_se->PlayBreakSe();
			m_se->PlayStanSe(m_playerNum);

			return;
		}

		/// @brief ボールの勢いに応じてノックバックする。
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