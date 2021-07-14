#include "stdafx.h"
#include "Player.h"

namespace {

	/// @brief キック可能な距離
	const float KICK_POSSIBLE_DISTANCE = 200.0f;
	/// @brief ガード可能な距離
	const float GUARD_DISTANCE = 90.0f;
	/// @brief ボールと接触する距離
	const float COLLIDE_DISTANCE = 80.0f;
	/// @brief 落下扱いになる高さ
	const float FALLING_HEIGHT = -3000.0f;
	/// @brief バーストエフェクトを再生する判定を行う高さ
	const float BURST_HEIGHT = -500.0f;
	/// @brief 1Pの初期位置
	const Vector3 PLAYER1_STARTPOS = { -500.0f,500.0f,500.0f };
	/// @brief 2Pの初期位置
	const Vector3 PLAYER2_STARTPOS = { 500.0f,500.0f,500.0f };
	/// @brief 3Pの初期位置
	const Vector3 PLAYER3_STARTPOS = { -500.0f,500.0f,-500.0f };
	/// @brief 4Pの初期位置
	const Vector3 PLAYER4_STARTPOS = { 500.0f,500.0f,-500.0f };
	/// @brief ポイントライトの高さ
	const float POINT_LIGHT_HEIGHT = 50.0f;
	/// @brief プレイヤーの半径
	const float PLAYER_RADIUS = 20.0f;
	/// @brief プレイヤーの高さ
	const float PLAYER_HEIGHT = 50.0f;
	/// @brief 通常時の摩擦力
	const float NORMAL_FRICTION = 0.01f;
	/// @brief ダメージ中の摩擦力
	const float DAMAGE_FRICYION = 0.001f;
	/// @brief ダメージを受けて復帰するのにかかる時間
	const float DAMAGE_RETURN_TIME = 100.0f;
	/// @brief 横方向に吹き飛ぶ勢い
	const float BLOW_AWAY_RATE = 2.0f;
	/// @brief 縦方向に吹き飛ぶ勢い
	const float BLOW_AWAY_HEIGHT_RATE = 1.0f;
	/// @brief アイテムを取ったときの吹き飛ぶ勢い
	const float DECREASE_BLOW_AWAY_RATE = 1.0f;
	/// @brief プレイヤーモデルの表示優先度
	const int PRIORITY = 1;
	/// @brief プレイヤーのリスポーン時の無敵時間
	const float MUTEKI_TIME = 3.0f;
	/// @brief リスポーン時の無敵時間の初期化
	const float TIME_ZERO = 0.0f;
	/// @brief スコアの加算数値
	const int SCORE_ADD = 100;
	/// @brief スコアの減算数値
	const int SCORE_PULL = -100;
	/// @brief キックのクールタイム
	const int KICK_COOLTIME = 20;
	/// @brief ジャストガード可能な時間
	const float POSSIBLE_JUST_GUARD_TIME = 0.01f;
	/// @brief ジャストガード発動時の強化時間
	const float POWERUP_TIME = 10.0f;
	/// @brief 通常のキック力
	const float NORMAL_KICK_POWER = 1.5f;
	/// @brief 強化状態のキック力
	const float POWERFUL_KICK_POWER = 4.0f;
	/// @brief アイテムを取ったときに増えるキック力
	const float KICK_POWER_ADDITION_AMOUNT = 1.0f;
	/// @brief 通常の移動速度
	const float NORMAL_VELOCITY = 0.9f;
	/// @brief ダッシュの移動速度
	const float DASH_VELOCITY = 0.95f;
	/// @brief アイテムを取ったときに増える速度
	const float VELOCITY_ADDITION_AMOUNT = 0.02f;
	/// @brief 通常のガード耐久値低下量
	const float GUARD_DECREASE_VALUE = 0.3f;
	/// @brief 強化状態のガード耐久値低下量
	const float POWERFUIL_GUARD_DECREASE_VALUE = 0.15f;
	/// @brief アイテムを取ったときのガード耐久値軽減率
	const float GUARD_ADDITION_AMOUNT = 0.1f;
	/// @brief スタミナの最大値
	const float MAX_STANIMA = 6.0f;
	/// @brief 通常のスタミナ低下量
	const float STAMINA_DECREASE_VALUE = 2.0f;
	/// @brief 強化状態のスタミナ低下量
	const float POWERFUIL_STAMINA_DECREASE_VALUE = 1.0f;
	/// @brief アイテムによる強化時間
	const float ITEM_POWERUP_TIME = 10.0f;
	/// @brief 勢いよく当たった扱いになる速度
	const float STRONG_HIT = 20.0f;
}

Player::Player()
{
	//プレイヤーの初期状態を設定
	m_moveVelocity = NORMAL_VELOCITY;
	m_stamina = MAX_STANIMA;
	m_kickPower = NORMAL_KICK_POWER;
	m_gravity = 5.0f;
	m_charaCon.Init(PLAYER_RADIUS, PLAYER_HEIGHT, m_position);
}

Player::~Player()
{
	//プレイヤーモデルを削除
	DeleteGO(m_skinModelRender);
}

bool Player::Start()
{
	//必要なデータを取得
	m_timer = FindGO<Timer>(TIMER_NAME);
	m_score = FindGO<Score>(SCORE_NAME);
	m_lig = FindGO<Lighting>(LIGHTING_NAME);
	m_plEffect = FindGO<PlayerEffect>(PLAYER_EFFECT_NAME);
	m_ball = FindGO<Ball>(BALL_NAME);
	m_se = FindGO<Se>(SE_NAME);

	m_animationClips[enAnimation_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimation_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimation_Run].Load("Assets/animData/unitychan/run.tka");

	m_animationClips[enAnimation_Idle].SetLoopFlag(true);
	m_animationClips[enAnimation_Walk].SetLoopFlag(true);
	m_animationClips[enAnimation_Run].SetLoopFlag(true);

	m_skinModelRender = NewGO<SkinModelRender>(PRIORITY);

	/*m_skinModelRender->InitA(UNITYCHAN_MODEL, "Assets/modelData/unityChan.tks", m_animationClips, enAnimation_Num);
	m_skinModelRender->PlayAnimation(enAnimation_Idle, 1.0f);*/


	m_ui = FindGO<GameUI>(GAME_UI_NAME);

	return true;
}

void Player::SetPlayerNumber(int num)
{

	//受け取った番号に応じて自分が何Pかを設定する
	m_myNumber = num;
	switch (num)
	{
	case 0: {
		m_playerColor = RED;
		m_startPos = PLAYER1_STARTPOS;
		m_skinModelRender->InitA(UNITYCHAN_MULTI_FILEPATH[num], "Assets/modelData/unityChan.tks", enModelUpAxisY, m_animationClips, enAnimation_Num,false);
	}break;
	case 1: {
		m_playerColor = BLUE;
		m_startPos = PLAYER2_STARTPOS;
		m_skinModelRender->InitA(UNITYCHAN_MULTI_FILEPATH[num], "Assets/modelData/unityChan.tks", enModelUpAxisY, m_animationClips, enAnimation_Num,false);
	}break;
	case 2: {
		m_playerColor = YELLOW;
		m_startPos = PLAYER3_STARTPOS;
		m_skinModelRender->InitA(UNITYCHAN_MULTI_FILEPATH[num], "Assets/modelData/unityChan.tks", enModelUpAxisY, m_animationClips, enAnimation_Num,false);
	}break;
	case 3: {
		m_playerColor = GREEN;
		m_startPos = PLAYER4_STARTPOS;
		m_skinModelRender->InitA(UNITYCHAN_MULTI_FILEPATH[num], "Assets/modelData/unityChan.tks", enModelUpAxisY, m_animationClips, enAnimation_Num,false);
	}break;
	}
	m_position = m_startPos;
	m_charaCon.SetPosition(m_position);

	m_lig->SetPointLightColor(m_myNumber, m_playerColor);
	m_lig->SetPointLightRange(m_myNumber, 500.0f);

	
	m_skinModelRender->PlayAnimation(enAnimation_Idle, 1.0f);

}

void Player::Move()
{
	/// @brief スティック入力でカメラ方向に移動
	m_moveSpeed += g_camera3D->GetRight() * m_Lstickx;
	m_moveSpeed += g_camera3D->GetForward() * m_Lsticky;

	if (m_powerUp == true) {
		m_staminaDecreaseValue = POWERFUIL_STAMINA_DECREASE_VALUE;
	}
	else {
		m_staminaDecreaseValue = STAMINA_DECREASE_VALUE;
	}

	if (IsDash() == true) {
		m_moveVelocity = DASH_VELOCITY;

		m_stamina -= g_gameTime->GetFrameDeltaTime() * m_staminaDecreaseValue;

		m_anim = enAnimation_Run;
	}
	else {
		m_moveVelocity = NORMAL_VELOCITY;
		m_stamina += g_gameTime->GetFrameDeltaTime() * FLOAT_1;
		if (m_stamina > MAX_STANIMA) {
			m_stamina = MAX_STANIMA;
		}
		m_anim = enAnimation_Walk;
	}

	if (m_speedUp == true && m_damage == false) {
		m_moveVelocity += VELOCITY_ADDITION_AMOUNT;
	}

	m_moveSpeed *= m_moveVelocity;

	/// @brief 重力を加える
	if (m_damage == true) {
		m_moveSpeed.y -= m_gravity / 2.0f;
	}
	else {
		m_moveSpeed.y -= m_gravity;
	}

	/// @brief ダメージ中かどうかで摩擦力を変える
	if (m_damage == false) {
		m_friction = NORMAL_FRICTION;
	}
	else {
		m_friction = DAMAGE_FRICYION;
	}
	/// @brief 移動速度に摩擦力を加える
	m_moveSpeed -= m_moveSpeed * m_friction;

	if (m_damage == false && m_guard == false && m_breakGuard == false && m_moveSpeed.x != FLOAT_0 || m_moveSpeed.z != FLOAT_0) {
		m_direction = m_moveSpeed;
		m_direction.y = FLOAT_0;
		m_direction.Normalize();
	}

	Vector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = FLOAT_0;
	/// @brief 移動速度が一定以下で止まる
	if (moveSpeedXZ.LengthSq() < 0.1f) {
		m_moveSpeed.x = FLOAT_0;
		m_moveSpeed.z = FLOAT_0;
	}

	/// @brief プレイヤーが落下したらリスポーンする
	if (m_position.y < FALLING_HEIGHT) {

		if (m_haveAttackedPlayer != m_myNumber) {
			m_score->AddScore(m_haveAttackedPlayer);
		}
		m_score->DebuctionScore(m_myNumber);

		
		ReSpawn();
	}

	/// @brief バースト処理
	if (m_position.y < BURST_HEIGHT) {
		m_burstFlag = true;

		if (m_burstFlag == true && m_burstFlagPrevFrame == false) {
			if (m_damage == true || m_breakGuard == true) {
				m_plEffect->StopKnockOutEffect(m_myNumber);
				m_se->StopStanSe(m_myNumber);
			}
			m_plEffect->PlayBurstEffect(m_myNumber);
			m_se->PlayDefeatSe();
		}
	}


}

void Player::Rotation()
{
	/// @brief ダメージ中、ガード中、動いていないときは回転しない
	if (m_damage == true || m_guard == true || m_breakGuard == true || m_moveSpeed.x == FLOAT_0 && m_moveSpeed.z == FLOAT_0) {
		m_anim = enAnimation_Idle;
		return;
	}
	m_qRot.SetRotation(Vector3::AxisY, atan2(m_direction.x, m_direction.z));
}

void Player::IsKick()
{
	/// @brief ボールとの距離が一定以下の時のみ判定
	if (m_ballDistance < KICK_POSSIBLE_DISTANCE) {
		/// @brief プレイヤーの向きとボールへのベクトルの内積で蹴れる角度を制限
		float matchRate = Dot(m_direction, m_toBallVec);
		if (matchRate > 0.0f) {
			m_kickFlag = true;
		}
		else {
			m_kickFlag = false;
		}
	}
	else {
		m_kickFlag = false;
	}

	if (m_powerUp == true) {
		m_kickPower = POWERFUL_KICK_POWER;
		m_powerUpTime += g_gameTime->GetFrameDeltaTime() * FLOAT_1;
	}
	else
	{
		m_powerUpTime = FLOAT_0;
		m_kickPower = NORMAL_KICK_POWER;
	}
	if (m_powerUpTime > POWERUP_TIME) {
		m_powerUp = false;
	}
	if (m_kickUp == true) {
		m_kickPower += KICK_POWER_ADDITION_AMOUNT;
	}
}

void Player::KickBall()
{
	/// @brief ボールにキック方向とキック力を伝えて動かす
	m_ball->SetMoveDirection(m_direction);
	m_ball->Acceleration(m_kickPower);
	/// @brief ボールに蹴ったプレイヤーの色と数字を伝える
	m_ball->SetBallLightColor(m_playerColor);
	m_ball->SetPlayerInformation(m_myNumber);

	m_ball->MoveStart();

	//キック時、強化状態のとき
	if (m_powerUp) {
		m_se->PlayPoweredKickSe();
	}


}

bool Player::IsDash()
{
	if (m_dash == true && m_guard == false && g_pad[m_myNumber]->IsPress(enButtonRB1)) {
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

void Player::BallCollide()
{
	/// @brief ボールへのベクトルとボールの向きで当たる角度を決める
	float matchRate = Dot(m_ball->GetMoveDirection(), m_toBallVec);
	if (m_ball->IsMove() == false || m_guard == true || matchRate > 0.0f) {
		return;
	}

	/// @brief ボールと自分の位置から吹き飛ばされる方向を決める
	Vector3 repulsiveForce = m_position - m_ball->GetPosition();
	repulsiveForce.y = FLOAT_0;
	repulsiveForce.Normalize();

	if (m_guardUp == true) {
		repulsiveForce *= m_ball->GetVelocity() * DECREASE_BLOW_AWAY_RATE;
	}
	else {
		repulsiveForce *= m_ball->GetVelocity() * BLOW_AWAY_RATE;
	}

	
	repulsiveForce.y = m_ball->GetVelocity() * BLOW_AWAY_HEIGHT_RATE;

	if (m_dieFlag == false) {
		m_moveSpeed = repulsiveForce * FLOAT_2;




		if (m_breakGuard == true) {
			m_plEffect->StopKnockOutEffect(m_myNumber);
			m_se->StopStanSe(m_myNumber);
		}
		if (m_damage == false) {
			m_plEffect->PlayKnockOutEffect(m_myNumber);
			m_se->PlayStanSe(m_myNumber);
		}


		m_damage = true;
		if (m_ball->GetVelocity() > STRONG_HIT) {
			m_se->PlayStrongCollideSe();
		}
		else {
			m_se->PlayWeakCollideSe();
		}


		/// @brief 攻撃してきたプレイヤーの番号を記憶する
		m_haveAttackedPlayer = m_ball->GetPlayerInformation();

		if (m_haveAttackedPlayer != m_myNumber && m_dieFlag == false) {
			m_score->AddScore(m_haveAttackedPlayer);
		}
	}
	else {
		m_se->PlayNoDamageCollideSe();
	}
	m_ball->SetMoveDirection(repulsiveForce * FLOAT_MINUS_1);
}

void Player::Guard()
{
	/// @brief ガード中は移動速度を下げる
	m_moveSpeed.x /= FLOAT_2;
	m_moveSpeed.z /= FLOAT_2;

	/// @brief ガード中は耐久値(guardDurability)が減り続ける
	if (m_powerUp == true) {
		m_guradDecreaseValue = POWERFUIL_GUARD_DECREASE_VALUE;
	}
	else {
		m_guradDecreaseValue = GUARD_DECREASE_VALUE;
	}

	if (m_guardUp == true) {
		m_guradDecreaseValue -= GUARD_ADDITION_AMOUNT;
	}

	m_guardDurability -= m_guradDecreaseValue;

	//シールドエフェクト発生処理//
		//カウンターに値を加算
	m_guardEffectCouter += 1;
	//規定フレーム毎にエフェクトを発生
	if (m_guardEffectCouter % 20 == 1 &&
		m_breakGuard == false &&
		m_damage == false) {
		m_plEffect->PlayGuardEffect(m_myNumber);
	}

	/// @brief ジャストガード判定時間を進める
	m_justGuardTime += g_gameTime->GetFrameDeltaTime() * FLOAT_01;

	/// @brief ガード耐久値が無くなったら
	if (m_guardDurability <= 0.0f) {
		/// @brief ガードブレイクする
		m_guardDurability = 0.0f;
		m_breakGuard = true;
		m_plEffect->StopGuardEffect(m_myNumber);
		m_plEffect->PlayGuardBreakEffect(m_myNumber);
		m_plEffect->PlayKnockOutEffect(m_myNumber);
		m_se->PlayStanSe(m_myNumber);

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
			m_plEffect->PlayShieldHitEffect(m_myNumber);
			
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
		/// @brief ジャストガード判定時間内ならジャストガード発動
		if (m_justGuardTime < POSSIBLE_JUST_GUARD_TIME) {
			m_ball->SetVelocity(FLOAT_0);

			/// @brief ジャストガードエフェクトの再生
			m_plEffect->PlayJustGuardEffect(m_myNumber);
			m_se->PlayJustGuardSe();
			m_powerUp = true;
			m_powerUpTime = FLOAT_0;
		}
		else {
			/// @brief ボールの勢いに応じて耐久値を減らす
			float shieldDamage = m_ball->GetVelocity() * m_guradDecreaseValue * 10.0f;
			m_guardDurability -= shieldDamage;
			/// @brief ガードブレイクした場合
			if (m_guardDurability <= 0.0f)
			{
				/// @brief ガードエフェクトを消してガードブレイクエフェクトを再生する
				m_plEffect->StopGuardEffect(m_myNumber);
				m_plEffect->PlayGuardBreakEffect(m_myNumber);
				m_plEffect->PlayKnockOutEffect(m_myNumber);
				m_guardDurability = 0.0f;
				m_breakGuard = true;

				m_se->PlayBreakSe();
				m_se->PlayStanSe(m_myNumber);

				return;
			}

			/// @brief ボールの勢いに応じてノックバックする。
			Vector3 repulsiveForce = m_toBallVec * FLOAT_MINUS_1;
			repulsiveForce.Normalize();
			repulsiveForce *= m_ball->GetVelocity();
			repulsiveForce.y = m_ball->GetVelocity() * FLOAT_01;
			m_moveSpeed += repulsiveForce;
			m_ball->SetVelocity(m_ball->GetVelocity() / FLOAT_2);
			m_ball->SetMoveDirection(repulsiveForce * FLOAT_MINUS_1);
		}

	}
	else {
		/// @brief 接触していない
		m_shieldHit = false;
	}
}

void Player::ReSpawn() {
	/// @brief スタート位置にリスポーンさせる
	m_position = m_startPos;
	m_charaCon.SetPosition(m_position);
	m_damage = false;
	m_damageTime = FLOAT_0;
	m_breakGuard = false;
	m_guardDurability = 100.0f;
	m_mutekiTime = MUTEKI_TIME;
	m_lig->SetPointLightBlinking(m_myNumber, m_mutekiTime, 0.07f);
	m_dieFlag = true;

	//リスポーン時のエフェクトを再生
	m_plEffect->PlayRespawnEffect(m_myNumber);
	m_se->PlayReSpawnSe();
	m_powerUp = false;
	m_powerUpTime = FLOAT_0;
	m_itemPowerUp = false;
	m_itemPowerUpTime = FLOAT_0;

}

void Player::Muteki()
{
	m_mutekiTime -= g_gameTime->GetFrameDeltaTime();
	/// @brief リスポーン時に少しの間ボールに当たらなくなる
	if (m_mutekiTime <= TIME_ZERO) {
		m_dieFlag = false;
		m_burstFlag = false;
	}
}

void Player::Animation()
{
	switch (m_anim)
	{
	case enAnimation_Idle: {
		m_skinModelRender->PlayAnimation(enAnimation_Idle, 0.2f);
	}break;
	case enAnimation_Walk: {
		m_skinModelRender->PlayAnimation(enAnimation_Walk, 0.2f);
	}break;
	case enAnimation_Run: {
		m_skinModelRender->PlayAnimation(enAnimation_Run, 0.2f);
	}break;
	default:
		break;
	}
}

void Player::SetItemChangeState()
{
	//各フラグが前フレームと変化なしだったら処理しない
	if (m_kickUp == m_kickUpPrevFrame &&
		m_guardUp == m_guardUpPrevFrame &&
		m_speedUp == m_speedUpPrevFrame) {

		return;
	}

	//各フラグが1つでも前フレームと変化していたら処理に移行
	if (m_kickUp == true && m_kickUpPrevFrame == false) {
		m_itemBuffChageState = enItemBuff_Kick;
		m_plEffect->ChangeItemBuffEffect(m_myNumber, m_itemBuffChageState);
	}
	if (m_guardUp == true && m_guardUpPrevFrame == false) {
		m_itemBuffChageState = enItemBuff_Guard;
		m_plEffect->ChangeItemBuffEffect(m_myNumber, m_itemBuffChageState);
	}
	if (m_speedUp == true && m_speedUpPrevFrame == false) {
		m_itemBuffChageState = enItemBuff_Speed;
		m_plEffect->ChangeItemBuffEffect(m_myNumber, m_itemBuffChageState);
	}

}

void Player::RecordFlags()
{
	//現フレームのバースト状況を記録
	if (m_burstFlagPrevFrame != m_burstFlag) {
		m_burstFlagPrevFrame = m_burstFlag;
	}

	//アイテムパワーアップフラグ各種の記録
	if (m_kickUpPrevFrame != m_kickUp) {
		m_kickUpPrevFrame = m_kickUp;
	}
	
	if (m_guardUpPrevFrame != m_guardUp) {
		m_guardUpPrevFrame = m_guardUp;
	}

	if (m_speedUpPrevFrame != m_speedUp) {
		m_speedUpPrevFrame = m_speedUp;
	}

}

void Player::Update()
{
	//アイテムを取ったら自身のバフ状況を変更
	SetItemChangeState();
	
	//アイテムバフエフェクトの再生処理
	if (m_kickUp == true ||
		m_guardUp == true ||
		m_speedUp == true) {
		
		m_itemPowerUpCounter += 1;
		if (m_itemPowerUpCounter % 25 == 1) {
			m_plEffect->PlayItemBuffEffect(m_myNumber);
		}
	}


	/// @brief スティック入力を受け取る
	m_Lstickx = g_pad[m_myNumber]->GetLStickXF();
	m_Lsticky = g_pad[m_myNumber]->GetLStickYF();

	if (m_timer->IsTimerExecution() == false) {
		m_Lstickx = FLOAT_0;
		m_Lsticky = FLOAT_0;
	}

	/// @brief ダメージ中はスティック入力を受け付けない
	if (m_damage == true) {
		m_Lstickx = FLOAT_0;
		m_Lsticky = FLOAT_0;
		m_damageTime += FLOAT_1;
	}
	if (m_damageTime > DAMAGE_RETURN_TIME) {
		m_damageTime = FLOAT_0;
		if (m_breakGuard == false) {
			m_plEffect->StopKnockOutEffect(m_myNumber);
			m_se->StopStanSe(m_myNumber);
		}
		if (m_breakGuard != true) {
			m_plEffect->PlayRepairEffect(m_myNumber);
		}
		m_damage = false;
	}

	if (m_breakGuard == true)
	{
		m_Lstickx = FLOAT_0;
		m_Lsticky = FLOAT_0;
	}

	if (m_stamina < FLOAT_0) {
		m_dash = false;
		m_se->PlayStaminaOverSe();
	}

	if (m_dash == false && m_stamina >= MAX_STANIMA) {
		m_dash = true;
		m_se->PlayStaminaRecoverySe();
	}

	BallDistanceCalculation();
	Move();
	Rotation();
	IsKick();

	/// @brief キッククールタイム
	if (m_kickCooling == true)
	{
		m_kickCooler += 1;
		if (m_kickCooler == KICK_COOLTIME) {
			m_kickCooling = false;
			m_kickCooler = 0;
		}
	}

	

	/// @brief キックの不可避分岐
	if (m_damage == true || m_guard == true || m_breakGuard == true || m_kickCooling == true)
	{
		//キック不可
		m_readyKick = false;
	}
	else {
		//キック可
		m_readyKick = true;
	}

	if (m_kickFlag == true && m_readyKick == true && m_timer->IsTimerExecution() == true) {
		if (g_pad[m_myNumber]->IsTrigger(enButtonA)) {

			
			m_plEffect->PlayKickEffect(m_myNumber);
			m_se->PlayKickSe();

			KickBall();
		}
	}

	if (g_pad[m_myNumber]->IsTrigger(enButtonA)) {
		m_kickCooling = true;
	}
	/// @brief 非ガード時、ガード耐久値を回復
	if (m_guard == false) {
		m_guardDurability += 0.3f;
		m_justGuardTime = 0.0f;
	}
	/// @brief 再展開可能まで
	if (m_guardDurability >= 100.0f && m_breakGuard == true)
	{
		m_breakGuard = false;
		if (m_damage == false) {
			m_plEffect->StopKnockOutEffect(m_myNumber);
			m_se->StopStanSe(m_myNumber);
		}
		m_plEffect->PlayShieldRepairEffect(m_myNumber);
		m_se->PlayShieldRepairSe();

	}
	/// @brief ガード耐久値を100より上にならないようにする奴
	if (m_guardDurability >= 100.0f)
	{
		m_guardDurability = 100.0f;
	}

	/// @brief ボールとの距離が一定以下で吹き飛ぶ
	if (m_breakGuard == true) {
		if (m_ballDistance < GUARD_DISTANCE) {
			BallCollide();
			//ダメージエフェクト再生処理
			//前フレームにダメージ状態でなく、現フレームでダメージ状態のとき
			if (m_damagePrevFrame == false && m_damage == true) {
				m_plEffect->PlayDamageEffect(m_myNumber);
			}
		}
	}
	else {
		if (m_ballDistance < COLLIDE_DISTANCE) {
			BallCollide();
			//ダメージエフェクト再生処理
			//前フレームにダメージ状態でなく、現フレームでダメージ状態のとき
			if (m_damagePrevFrame == false && m_damage == true) {
				m_plEffect->PlayDamageEffect(m_myNumber);
			}
		}
	}
	if (m_guard == true && !g_pad[m_myNumber]->IsPress(enButtonLB1) && m_timer->IsTimerExecution() == true) {
		m_se->PlayGuardEndSe();
	}
	/// @brief LB1を押している間ガード
	if (g_pad[m_myNumber]->IsPress(enButtonLB1) && m_breakGuard == false && m_damage == false) {
		m_guard = true;
	}
	else {
		m_guard = false;
		m_guardEffectCouter = 0;
	}

	/// @brief ガード可能ならガードの処理
	if (m_guard == true && m_breakGuard == false && m_timer->IsTimerExecution() == true) {


		Guard();
	}

	//ボタン押下時かつガードブレイクしていないときに実行
	if (g_pad[m_myNumber]->IsTrigger(enButtonLB1) &&
		m_breakGuard == false &&
		m_damage == false &&
		m_timer->IsTimerExecution() == true) {
		//m_guardBeginEffect.Play();
		m_plEffect->PlayGuardBeginEffect(m_myNumber);
		m_se->PlayGuardStartSe();
	}

	if (m_dieFlag == true) {
		Muteki();
	}

	//パワーアップエフェクトの再生
	if (m_powerUp == true) {
		m_powerUpCounter += 1;
		if (m_powerUpCounter % 20 == 1) {
			m_plEffect->PlayKickBuffEffect(m_myNumber);
		}
	}
	else {
		m_powerUpCounter = 0.0f;
	}

	if (m_itemPowerUp == true) {
		m_itemPowerUpTime += g_gameTime->GetFrameDeltaTime();
	}
	else {
		m_kickUp = false;
		m_guardUp = false;
		m_speedUp = false;
	}
	if (m_itemPowerUpTime > ITEM_POWERUP_TIME) {
		m_itemPowerUp = false;
	}

	/// @brief 自分に当たるスポットライトの位置と方向を設定
	Vector3 pos = m_position;
	pos.y = POINT_LIGHT_HEIGHT;
	m_lig->SetPointLighitPos(m_myNumber, pos);

	/*Vector3 dir = m_position - m_lig->GetSpotLightPos(m_myNumber);
	m_lig->SetSpotLightDirection(m_myNumber, dir);*/

	/// @brief キャラクターコントローラーで座標を決める
	m_position = m_charaCon.Execute(m_moveSpeed, FLOAT_1);

	/// @brief モデルに座標と回転を伝える
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_qRot);

	/// @brief アニメーション
	Animation();

	if (g_pad[m_myNumber]->IsTrigger(enButtonStart)) {
		ReSpawn();
	}

	//現フレームのフラグ状態を記録
	RecordFlags();
}

void Player::BallDistanceCalculation()
{
	m_toBallVec = m_ball->GetPosition() - m_position;
	m_ballDistance = m_toBallVec.Length();
	m_toBallVec.y = FLOAT_0;
	m_toBallVec.Normalize();
}