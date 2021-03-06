#include "stdafx.h"
#include "PlayerMove.h"

namespace {
	/// @brief 通常の移動速度
	const float NORMAL_VELOCITY = 0.9f;
	/// @brief ダッシュの移動速度
	const float DASH_VELOCITY = 0.95f;
	/// @brief ボールに接触する判定
	const float COLLIDE_RATE = 0.0f;
	/// @brief ボールに接触する距離
	const float COLLIDE_DISTANCE = 80.0f;
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
	//使用するデータを持って来る
	m_ball = FindGO<Ball>(BALL_NAME);
	m_se = FindGO<Se>(SE_NAME);
	m_timer = FindGO<Timer>(TIMER_NAME);
	//スタミナの初期値は最大に
	m_stamina = MAX_STANIMA;
	return true;
}

void PlayerMove::Update()
{
	//扱うデータの準備が終わるまでは実行しない
	if (m_setUp == false) {
		return;
	}

	//スティック入力を受け取る
	m_Lstickx = g_pad[m_playerNum]->GetLStickXF();
	m_Lsticky = g_pad[m_playerNum]->GetLStickYF();

	//移動できないとき…
	if (IsCanMove() == false) {
		//スティック入力を受け付けない
		m_Lstickx = 0.0f;
		m_Lsticky = 0.0f;
	}

	//移動・回転を行う
	Move();
	Rotation();

	//移動と回転を伝える
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
	//タイマーがゲーム進行中でない・ダメージ中・ガードブレイク中の場合
	if (m_timer->IsTimerExecution() == false || m_player->IsDamage() == true || m_plAction->IsGuardBreak() == true) {
		//移動できない
		return false;
	}
	//それ以外では…
	else {
		//移動できる
		return true;
	}
}

bool PlayerMove::IsDash()const
{
	//ダッシュ可能でガードしていないときにRB1が押されていたら…
	if (m_dash == true && m_plAction->IsGuard() == false && g_pad[m_playerNum]->IsPress(enButtonRB1)) {
		//スティック入力があったら…
		if (m_Lstickx != 0.0f || m_Lsticky != 0.0f) {
			//ダッシュしている
			return true;
		}
		//スティック入力が無かったら…
		else {
			//ダッシュしていない
			return false;
		}
	}
	//ダッシュ不可能・ガード中・RB1が押されていない場合
	else {
		//ダッシュしていない
		return false;
	}
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
	if (m_plReinforcement->IsSelfPowerUp() == true) {
		//スタミナ消費を軽減
		m_staminaDecreaseValue = POWERFUIL_STAMINA_DECREASE_VALUE;
	}
	//そうでないなら
	else {
		//通常のスタミナ消費
		m_staminaDecreaseValue = STAMINA_DECREASE_VALUE;
	}

	//プレイヤーが防御強化状態だったら…
	if (m_plReinforcement->IsDefenseUp() == true) {
		//吹き飛ぶ勢いを防御強化状態中の勢いにする
		m_blowAwayRate = DECREASE_BLOW_AWAY_RATE;
	}
	//プレイヤーが防御強化状態でない場合…
	else {
		//吹き飛ぶ勢いを通常時の勢いにする
		m_blowAwayRate = BLOW_AWAY_RATE;
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

void PlayerMove::Move()
{
	// スティック入力でカメラ方向に移動
	m_moveSpeed += g_camera3D->GetRight() * m_Lstickx;
	m_moveSpeed += g_camera3D->GetForward() * m_Lsticky;

	//自分の状態によって移動に使うパラメーターを決定
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
		//スタミナを回復する
		StaminaRecovery();
	}

	//スタミナの状態を調べる
	StaminaManagement();

	//速度を加算する
	m_moveVelocity += m_addVelocity;
	//移動速度を設定
	m_moveSpeed *= m_moveVelocity;
	//重力を加える
	m_moveSpeed.y -= m_gravity;
	//移動速度に応じた摩擦力を加える
	m_moveSpeed -= m_moveSpeed * m_friction;

	//Y方向の移動速度を除いた移動速度を取得
	Vector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	//移動速度が一定以下になったら止まる
	if (moveSpeedXZ.LengthSq() < 0.1f) {
		MoveStop();
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
	//スタミナ最大値だったら…
	if (m_stamina == MAX_STANIMA) {
		//終了する
		return;
	}
	//スタミナを回復する
	m_stamina += g_gameTime->GetFrameDeltaTime();
	//スタミナが最大値を超えたら…
	if (m_stamina >= MAX_STANIMA) {
		//ダッシュ不可だったら…
		if (m_dash == false) {
			//スタミナ回復のSEを鳴らす
			m_se->PlayStaminaRecoverySe();
			//ダッシュを可能にする
			m_dash = true;
		}
		//スタミナを最大値に設定
		m_stamina = MAX_STANIMA;
	}
}

void PlayerMove::StaminaManagement()
{
	//スタミナが無くなったら…
	if (m_stamina < 0.0f) {
		//ダッシュできなくする
		m_dash = false;
		//スタミナ切れのSEを鳴らす
		m_se->PlayStaminaOverSe();
	}
}

void PlayerMove::Rotation()
{
	//ダメージ中・ガード中・ガードブレイク中は回転を行わない
	if (m_player->IsDamage() == true || m_plAction->IsGuard() == true || m_plAction->IsGuardBreak() == true) {
		//待機アニメーションを再生
		m_player->SetAnimation(enAnimation_Idle);
		return;
	}
	//動いていないときも回転を行わない
	if (m_moveSpeed.x == 0.0f && m_moveSpeed.z == 0.0f) {
		//待機アニメーションを再生
		m_player->SetAnimation(enAnimation_Idle);
		return;
	}

	//移動速度で方向を決める
	m_direction = m_moveSpeed;
	//縦方向の要素を消す
	m_direction.y = 0.0f;
	//正規化して方向ベクトルにする
	m_direction.Normalize();
	//プレイヤーに方向を渡す
	m_player->SetDirection(m_direction);
	//方向から回転を求める
	m_qRot.SetRotation(Vector3::AxisY, atan2(m_direction.x, m_direction.z));
}