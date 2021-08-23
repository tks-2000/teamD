#include "stdafx.h"
#include "PlayerMove.h"

namespace {
	/// @brief 通常の移動速度
	const float NORMAL_VELOCITY = 0.9f;
	/// @brief ダッシュの移動速度
	const float DASH_VELOCITY = 0.95f;
	/// @brief 通常時の摩擦力
	const float NORMAL_FRICTION = 0.01f;
	/// @brief ダメージ中の摩擦力
	const float DAMAGE_FRICYION = 0.001f;
	/// @brief 通常時の重力
	const float NORMAL_GRAVITY = 5.0f;
	/// @brief ダメージ中の重力
	const float DAMAGE_GRAVITY = 2.5f;
	/// @brief ダメージを受けて復帰するのにかかる時間
	const float DAMAGE_RETURN_TIME = 100.0f;
	/// @brief 横方向に吹き飛ぶ勢い
	const float BLOW_AWAY_RATE = 2.0f;
	/// @brief 縦方向に吹き飛ぶ勢い
	const float BLOW_AWAY_HEIGHT_RATE = 1.0f;
	/// @brief アイテムを取ったときの吹き飛ぶ勢い
	const float DECREASE_BLOW_AWAY_RATE = 1.0f;
	/// @brief アイテムを取ったときに増える速度
	const float VELOCITY_ADDITION_AMOUNT = 0.02f;
	/// @brief スタミナの最大値
	const float MAX_STANIMA = 6.0f;
	/// @brief 通常のスタミナ低下量
	const float STAMINA_DECREASE_VALUE = 2.0f;
	/// @brief 強化状態のスタミナ低下量
	const float POWERFUIL_STAMINA_DECREASE_VALUE = 1.0f;
	/// @brief 勢いよく当たった扱いになるボールの速度
	const float STRONG_HIT = 20.0f;
	/// @brief リスポーンコマンドを押し続けて発動するまでの時間
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
	// スティック入力でカメラ方向に移動
	m_moveSpeed += g_camera3D->GetRight() * m_Lstickx;
	m_moveSpeed += g_camera3D->GetForward() * m_Lsticky;

	DetermineParameters();

	//ダッシュ時
	if (IsDash() == true) {
		//ダッシュを実行
		Dash();
	}
	//ダッシュしていないとき
	else {
		//歩行を実行
		Walk();
	}

	//速度を加算する
	m_moveVelocity += m_addVelocity;
	//移動速度を設定
	m_moveSpeed *= m_moveVelocity;
	//移動速度に応じた摩擦力を加える
	m_moveSpeed -= m_moveSpeed * m_friction;
	//重力を加える
	m_moveSpeed.y -= m_gravity;

	//Y方向の移動速度を除いた移動速度を取得
	Vector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	//移動速度が一定以下になったら止まる
	if (moveSpeedXZ.LengthSq() < 0.1f) {
		MoveStop();
	}
	m_player->SetMoveSpeed(m_moveSpeed);
	m_player->SetCharaCon(m_moveSpeed);
}

void PlayerMove::DetermineParameters()
{
	//ダメージ状態かどうかで処理を分ける
	if (m_player->IsDamage() == true) {
		//ダメージ中に変化するパラメーターを設定する
		m_gravity = NORMAL_GRAVITY;
		m_friction = NORMAL_FRICTION;
	}
	//そうでないなら
	else {
		//通常パラメーターを設定する
		m_gravity = DAMAGE_GRAVITY;
		m_friction = DAMAGE_FRICYION;
	}

	//プレイヤーがパワーアップ状態のとき
	if (m_plReinforcement->IsPowerUp() == true) {
		//スタミナ消費を軽減
		m_staminaDecreaseValue = POWERFUIL_STAMINA_DECREASE_VALUE;
	}
	//そうでないなら
	else {
		//通常のスタミナ消費
		m_staminaDecreaseValue = STAMINA_DECREASE_VALUE;
	}

	//プレイヤーが速度強化状態だったら…
	if (m_plReinforcement->IsSpeedUp() == true && m_player->IsDamage() == false) {
		//加算する速度を設定する
		m_addVelocity = VELOCITY_ADDITION_AMOUNT;
	}
	//プレイヤーが速度強化状態でない場合…
	else {
		//加算する速度を０にする
		m_addVelocity = 0.0f;
	}
}

void PlayerMove::Walk()
{
	//移動速度を標準にする
	m_moveVelocity = NORMAL_VELOCITY;
	//スタミナを回復させる
	StaminaRecovery();
	//歩くアニメーションを再生
	m_player->SetAnimation(enAnimation_Walk);
}

void PlayerMove::Dash()
{
	//移動速度をダッシュ時の速度に変更
	m_moveVelocity = DASH_VELOCITY;
	//スタミナを低下させる
	m_stamina -= g_gameTime->GetFrameDeltaTime() * m_staminaDecreaseValue;
	//ダッシュエフェクト再生処理
	m_plEffect->PlayDashEffect();
	//ダッシュアニメーションを再生
	m_player->SetAnimation(enAnimation_Run);
}

void PlayerMove::StaminaRecovery()
{
	//スタミナを回復する
	m_stamina += g_gameTime->GetFrameDeltaTime();
	//スタミナが最大値を超えたら…
	if (m_stamina > MAX_STANIMA) {
		//スタミナを最大値に設定
		m_stamina = MAX_STANIMA;
	}
}

void PlayerMove::ReSpawnCountAdd()
{
	//リスポーン時間を加算
	m_reSpawnTime += g_gameTime->GetFrameDeltaTime();
	//リスポーン可能な時間を超えたら…
	if (m_reSpawnTime > RESPAWN_TIME) {
		//プレイヤーをリスポーンさせる
		m_player->ReSpawn();
		m_reSpawnTime = 0.0f;
	}
}

void PlayerMove::ReSpawn()
{

}

void PlayerMove::Rotation()
{
	//移動速度で方向を決める
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
	//スタミナが無くなったら…
	if (m_stamina < 0.0f) {
		//ダッシュできなくする
		m_dash = false;
		//スタミナ切れのSEを鳴らす
		m_se->PlayStaminaOverSe();
	}
	//スタミナが最大値を超えたら…
	if (m_stamina > MAX_STANIMA) {
		//ダッシュを可能にする
		m_dash = true;
		//スタミナ回復のSEを鳴らす
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