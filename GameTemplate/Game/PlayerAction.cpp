#include "stdafx.h"
#include "PlayerAction.h"

namespace {
	/// @brief 最大シールド耐久値
	const float MAX_GUARD_DURABILITY = 100.0f;
	/// @brief ジャストガード可能な時間
	const float POSSIBLE_JUST_GUARD_TIME = 0.01f;
	/// @brief ジャストガード発動時の強化時間
	const float POWERUP_TIME = 10.0f;
	/// @brief 通常のガード耐久値低下量
	const float NORMAL_GUARD_DECREASE_VALUE = 0.3f;
	/// @brief 防御強化状態のガード耐久値低下量
	const float POWERFUIL_GUARD_DECREASE_VALUE = 0.15f;
	/// @brief 通常のガード耐久値回復量
	const float NORMAL_GUARD_RECOVERY_VALUE = 0.3f;
	/// @brief 強化状態のガード耐久値回復量
	const float POWERFUIL_GUARD_RECOVERY_VALUE = 0.6f;
	/// @brief キック可能な距離
	const float KICK_POSSIBLE_DISTANCE = 200.0f;
	/// @brief キック可能な一致率
	const float KICK_POSSIBLE_RATE = 0.0f;
	/// @brief 通常のキック力
	const float NORMAL_KICK_POWER = 1.5f;
	/// @brief 強化状態のキック力
	const float POWERFUL_KICK_POWER = 4.0f;
	/// @brief アイテムを取ったときに増えるキック力
	const float KICK_POWER_ADDITION_AMOUNT = 1.0f;
	/// @brief キックボタン
	const EnButton KICK_BUTTON = enButtonA;
}

PlayerAction::PlayerAction()
{
	//準備を行うので準備未完了に設定
	m_setUp = false;
}

PlayerAction::~PlayerAction()
{

}

bool PlayerAction::Start()
{
	//使用するデータを持って来る
	m_ball = FindGO<Ball>(BALL_NAME);
	m_timer = FindGO<Timer>(TIMER_NAME);
	m_se = FindGO<Se>(SE_NAME);
	m_score = FindGO<Score>(SCORE_NAME);
	//ガード耐久値の初期値は最大に
	m_guardDurability = MAX_GUARD_DURABILITY;
	return true;
}

void PlayerAction::Update()
{
	//準備完了するまでは処理を行わない
	if (m_setUp == false) {
		return;
	}
	//状態によって変化するパラメーターを決定
	DetermineParameters();

	//ガード中なら…
	if (IsGuard() == true) {
		//ガードの処理を行う
		Guard();
	}
	//ガードしていないなら…
	else {
		//ガード耐久値回復の処理を行う
		GuardDecreaseRecovery();
		//ガード時間が0でない(直前までガードしていた)とき…
		if (m_guardTime != 0.0f) {
			//ガード解除のSEを鳴らす
			m_se->PlayGuardEndSe();
			//ガード時間を0に設定する
			m_guardTime = 0.0f;
		}
	}

	//キック可能なときにキックボタンが押されたら…
	if (IsCanKick() == true && g_pad[m_playerNum]->IsTrigger(KICK_BUTTON) == true) {
		//キックの処理を行う
		Kick();
	}
}

void PlayerAction::SetPlayerNumber(const int num)
{
	//自分のプレイヤー番号を設定
	m_playerNum = num;
	//自分と同じプレイヤー番号のデータを入手
	m_player = FindGO<Player>(PLAYER_NAME[m_playerNum]);
	m_plCollide = FindGO<PlayerCollide>(PLAYER_COLLID_NAME[m_playerNum]);
	m_plEffect = FindGO<PlayerEffect>(PLAYER_EFFECT_NAME[m_playerNum]);
	m_plMove = FindGO<PlayerMove>(PLAYER_MOVE_NAME[m_playerNum]);
	m_plReinforcement = FindGO<PlayerReinforcement>(PLAYER_REINFORCEMENT_NAME[m_playerNum]);
	//準備完了
	m_setUp = true;
}

bool PlayerAction::IsCanGuard()
{
	//・ダメージ中でない
	//・ガードブレイクしていない
	//・タイマーがゲーム進行中
	//全てが満たされている場合…
	if (m_player->IsDamage() == false && m_guardBreak == false && m_timer->IsTimerExecution() == true) {
		//ガードが可能
		return true;
	}
	//そうでないなら…
	else {
		//ガード不可能
		return false;
	}
}

bool PlayerAction::IsGuard()
{
	//ガード不可状態なら…
	if (IsCanGuard() == false) {
		//ガードしていない
		return false;
	}
	//ガード可能状態なら…
	else {
		//ガードボタンが押されているなら…
		if (g_pad[m_playerNum]->IsPress(enButtonLB1) == true) {
			//ガードしている
			return true;
		}
		//ガードボタンが押されていないなら…
		else {
			//ガードしていない
			return false;
		}
	}
}

bool PlayerAction::IsCanKick()
{
	//プレイヤーの向きとプレイヤーからボールに向かうベクトルの内積を計算
	float matchRate = Dot(m_plMove->GetDirection(), m_plCollide->GetToBallVector());

	//・プレイヤーがダメージ状態でない
	//・プレイヤーがガード中でない
	//・プレイヤーとボールとの距離がキック可能範囲以下
	//・プレイヤーの向きとプレイヤーからボールに向かうベクトルの内積の結果が一致率を超えている
	//全てを満たしている場合
	if (m_player->IsDamage() == false &&
		IsGuard() == false && 
		m_plCollide->GetBallDistance() <= KICK_POSSIBLE_DISTANCE &&
		matchRate > KICK_POSSIBLE_RATE) {
		//キック可能
		return true;
	}
	//どれか一つでも満たしていない場合…
	else {
		//キック不可能
		return false;
	}
}

void PlayerAction::DetermineParameters()
{
	//プレイヤーが強化状態なら…
	if (m_plReinforcement->IsPowerUp() == true) {
		//ガード耐久値回復量を強化状態の物に設定
		m_guardRecoveryValue = POWERFUIL_GUARD_RECOVERY_VALUE;
		//キック力を強化状態の物に設定
		m_kickPower = POWERFUL_KICK_POWER;
	}
	//プレイヤーが強化状態でないなら…
	else {
		//ガード耐久値回復量を通常状態の物に設定
		m_guardRecoveryValue = NORMAL_GUARD_RECOVERY_VALUE;
		//キック力を通常状態の物に設定
		m_kickPower = NORMAL_KICK_POWER;
	}

	//プレイヤーが防御強化状態だったら…
	if (m_plReinforcement->IsDefenseUp() == true) {
		//ガード耐久値低下量を防御強化状態の物に設定
		m_guardDecreaseValue = POWERFUIL_GUARD_DECREASE_VALUE;
	}
	//プレイヤーが防御強化状態でないなら…
	else {
		//ガード耐久値低下量を通常状態の物に設定
		m_guardDecreaseValue = NORMAL_GUARD_DECREASE_VALUE;
	}

	//プレイヤーがキック力強化状態なら…
	if (m_plReinforcement->IsKickUp() == true) {
		//キック力を加算する
		m_kickPower += KICK_POWER_ADDITION_AMOUNT;
	}
}

void PlayerAction::Guard()
{
	//ガード中は移動速度を下げる
	m_guardMoveSpeed = m_plMove->GetMoveSpeed();
	m_guardMoveSpeed.x /= 2.0f;
	m_guardMoveSpeed.z /= 2.0f;
	m_plMove->SetMoveSpeed(m_guardMoveSpeed);

	//ガード中は耐久値が減り続ける
	m_guardDurability -= m_guardDecreaseValue;

	//ガード耐久値が0以下になったら…
	if (m_guardDurability <= 0.0f) {

		//ガードエフェクトを消してガードブレイクエフェクトを再生する
		m_plEffect->StopGuardEffect();
		m_plEffect->PlayGuardBreakEffect();
		//行動不能エフェクトも再生する
		m_plEffect->PlayKnockOutEffect();

		//SEも鳴らす
		m_se->PlayBreakSe();
		m_se->PlayStanSe(m_playerNum);

		//ガード耐久値を０に設定
		m_guardDurability = 0.0f;
		//ガードブレイク状態に変更
		m_guardBreak = true;

		//ガードが出来なくなるので処理を終わる
		return;
	}

	//シールドエフェクト発生処理
	m_plEffect->PlayGuardEffect();

	//ガード時間が0(直前までガードしていなかった)場合…
	if (m_guardTime == 0.0f) {
		//ガード開始エフェクトとSEを再生
		m_plEffect->PlayGuardBeginEffect();
		m_se->PlayGuardStartSe();
	}

	//ガード時間を進める
	m_guardTime += g_gameTime->GetFrameDeltaTime() * 0.1f;
}

void PlayerAction::GuardDecreaseRecovery()
{
	//ガード耐久値が最大値だった場合…
	if (m_guardDurability == MAX_GUARD_DURABILITY) {
		//処理を終了する
		return;
	}

	//ガード耐久値にガード耐久値回復量を加算する
	m_guardDurability += m_guardRecoveryValue;

	//ガード耐久値が最大値以上になったら…
	if (m_guardDurability >= MAX_GUARD_DURABILITY) {
		//ガードブレイク中だったら…
		if (m_guardBreak == true) {
			//ダメージ中でないなら…
			if (m_player->IsDamage() == false) {
				//行動不能エフェクトとSEを停止
				m_plEffect->StopKnockOutEffect();
				m_se->StopStanSe(m_playerNum);
			}

			//ガード回復のエフェクトとSEを再生
			m_plEffect->PlayShieldRepairEffect();
			m_se->PlayShieldRepairSe();

			//ガードブレイク状態から復帰する
			m_guardBreak = false;
		}
		//ガード耐久値を最大値に設定する
		m_guardDurability = MAX_GUARD_DURABILITY;
	}
}

void PlayerAction::Kick()
{
	//ボール移動方向をプレイヤーの向きに設定
	m_ball->SetMoveDirection(m_plMove->GetDirection());
	//ボールの速度にキック力を加える
	m_ball->Acceleration(m_kickPower);
	//ボールのライトカラーを自分のライトカラーに設定
	m_ball->SetBallLightColor(m_player->GetPlayerColor());
	//ボールに自分のプレイヤー番号を伝える
	m_ball->SetPlayerInformation(m_playerNum);
	//ボールを動かす
	m_ball->MoveStart();

	//プレイヤーが強化状態なら…
	if (m_plReinforcement->IsPowerUp() == true) {
		//強化状態のキックSEを鳴らす
		m_se->PlayPoweredKickSe();
	}
	//強化状態でないなら…
	else {
		//通常のキックSEを鳴らす
		m_se->PlayKickSe();
	}

	//キックエフェクトを再生
	m_plEffect->PlayKickEffect();
}