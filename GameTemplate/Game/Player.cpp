#include "stdafx.h"
#include "Player.h"

namespace {
	/// @brief エフェクト用定数
	//キックエフェクトのファイルパス
	const char16_t* KICKEFFECT_FILEPATH = u"Assets/effect/kick.efk";					
	//キックエフェクト発生位置を決める値。0に近いほどプレイヤー寄り
	const float KICKEFFECT_POSITION_RATE = 0.8f;
	//キックエフェクトの拡大率
	const Vector3 KICKEFFECT_SCALE = { 25.0f,25.0f,1.0f };

	//ガードエフェクトファイルパス
	const char16_t* GUARDEFFECT_FILEPATH = u"Assets/effect/shield.efk";
	//ガードエフェクトの拡大率(立体なのでz軸方向にも拡大している)
	const Vector3 GUARDEFFECT_SCALE = { 80.0f,80.0f,80.0f };
	//ガードエフェクト発生位置のy座標を決めるための定数
	const float GUARDEFFECT_POS_Y = 80.0f;

	//ガード予兆エフェクトのファイルパス
	const char16_t* GUARDEFFECT_BEGIN_FILEPATH = u"Assets/effect/shield_begin.efk";
	//ガード予兆エフェクトの拡大率
	const Vector3 GUARDEFFECT_BEGIN_SCALE = { 20.0f,20.0f,1.0f };
	
	//ガード破壊エフェクトのファイルパス
	const char16_t* GUARDEFFECT_BREAK_FILEPATH = u"Assets/effect/shieldbreak.efk";
	//ガード破壊エフェクトの拡大率
	const Vector3 GUARDEFFECT_BREAK_SCALE = { 15.0f,15.0f,15.0f };

	//シールド回復エフェクトのファイルパス
	const char16_t* GUARDEFFECT_REPAIR_FILEPATH = u"Assets/effect/shieldrepair.efk";
	//シールド回復エフェクトの拡大率
	const Vector3 GUARDEFFECT_REPAIR_SCALE = { 12.5f,12.5f,12.5f };

	//ガードヒットエフェクトのファイルパス
	const char16_t* GUARDEFFECT_HIT_FILEPATH = u"Assets/effect/shieldhit.efk";
	//ガードヒットエフェクトの拡大率
	const Vector3 GUARDEFFECT_HIT_SCALE = { 17.0f,17.0f,17.0f };
	//ガードヒットエフェクト発生の距離
	const float GUARDEFFECT_HIT_DISTANCE = 150.0f;

	//行動不能エフェクトのファイルパス
	const char16_t* KNOCKOUTEFFECT_FILEPATH = u"Assets/effect/knockout.efk";
	//行動不能エフェクトのスケール
	const Vector3 KNOCKOUTEFFECT_SCALE = { 15.0f,15.0f,15.0f };

	/// @brief キック可能な距離
	const float KICK_POSSIBLE_DISTANCE = 200.0f;
	/// @brief ガード可能な距離
	const float GUARD_DISTANCE = 120.0f;
	/// @brief ボールと接触する距離
	const float COLLIDE_DISTANCE = 80.0f;
	/// @brief 落下扱いになる高さ
	const float FALLING_HEIGHT = -1000.0f;
	/// @brief 1Pの初期位置
	const Vector3 PLAYER1_STARTPOS = { -600.0f,200.0f,600.0f };
	/// @brief 2Pの初期位置
	const Vector3 PLAYER2_STARTPOS = { 600.0f,200.0f,600.0f };
	/// @brief 3Pの初期位置
	const Vector3 PLAYER3_STARTPOS = { -600.0f,200.0f,-600.0f };
	/// @brief 4Pの初期位置
	const Vector3 PLAYER4_STARTPOS = { 600.0f,200.0f,-600.0f };
	/// @brief スポットライトの高さ
	const float SPOT_LIGHT_HEIGHT = 800.0f;
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
	/// @brief プレイヤーモデルの表示優先度
	const int PRIORITY = 1;
	/// @brief プレイヤーのリスポーン時の無敵時間
	const float MUTEKI_TIME = 150.0f;
	/// @brief リスポーン時の無敵時間の初期化
	const float TIME_ZERO = 0.0f;
	/// @brief スコアの加算数値
	const int SCORE_ADD = 100;
	/// @brief スコアの減算数値
	const int SCORE_PULL = -100;
}

Player::Player()
{

	//プレイヤーの初期状態を設定
	//キック時のエフェクトを初期化
	m_kickEffect.Init(KICKEFFECT_FILEPATH);
	//ガード時のエフェクトを初期化
	m_guardEffect.Init(GUARDEFFECT_FILEPATH);
	//ガード予兆エフェクトを初期化
	m_guardBeginEffect.Init(GUARDEFFECT_BEGIN_FILEPATH);
	//ガード破壊のエフェクトを初期化
	m_guardBreakEffect.Init(GUARDEFFECT_BREAK_FILEPATH);
	//シールド回復のエフェクトを初期化
	m_shieldRepairEffect.Init(GUARDEFFECT_REPAIR_FILEPATH);
	//ガードヒットエフェクトを初期化
	m_shieldHitEffect.Init(GUARDEFFECT_HIT_FILEPATH);
	//行動不能エフェクトを初期化
	m_knockOutEffect.Init(KNOCKOUTEFFECT_FILEPATH);

	

	m_moveVelocity = 0.9f;
	m_kickPower = 5.0f;
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
	m_lig = FindGO<Lighting>(LIGHTING_NAME);
	m_ball = FindGO<Ball>(BALL_NAME);

	m_animationClips[enAnimation_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimation_Walk].Load("Assets/animData/walk.tka");

	m_animationClips[enAnimation_Idle].SetLoopFlag(true);
	m_animationClips[enAnimation_Walk].SetLoopFlag(true);

	m_skinModelRender = NewGO<SkinModelRender>(PRIORITY);

	m_skinModelRender->InitA(UNITYCHAN_MODEL,"Assets/modelData/unityChan.tks",m_animationClips,enAnimation_Num);
	m_skinModelRender->PlayAnimation(enAnimation_Idle, 1.0f);

	
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
		
	}break;
	case 1: {
		m_playerColor = BLUE;
		m_startPos = PLAYER2_STARTPOS;
	}break;
	case 2: {
		m_playerColor = YELLOW;
		m_startPos = PLAYER3_STARTPOS;
	}break;
	case 3: {
		m_playerColor = GREEN;
		m_startPos = PLAYER4_STARTPOS;
	}break;
	}
	m_position = m_startPos;
	m_charaCon.SetPosition(m_position);
	
	m_lig->SetSpotLightColor(m_myNumber, m_playerColor);
	
}

void Player::Move()
{
	/// @brief スティック入力でカメラ方向に移動
	m_moveSpeed += g_camera3D->GetRight()* m_Lstickx;
	m_moveSpeed += g_camera3D->GetForward()* m_Lsticky;
	
	/// @brief 重力を加える
	m_moveSpeed.y -= m_gravity;
	
	
	/// @brief ダメージ中かどうかで摩擦力を変える
	if (m_damage == false) {
		m_friction = NORMAL_FRICTION;
	}
	else {
		m_friction = DAMAGE_FRICYION;
	}
	/// @brief 移動速度に摩擦力を加える
	m_moveSpeed -= m_moveSpeed * m_friction;

	if (m_damage == false && m_guard == false && m_moveSpeed.x != FLOAT_0 || m_moveSpeed.z != FLOAT_0) {
		m_direction = m_moveSpeed;
	}
	
	m_moveSpeed *= m_moveVelocity;

	Vector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	if (moveSpeedXZ.LengthSq() < 0.1f) {
		m_moveSpeed.x = FLOAT_0;
		m_moveSpeed.z = FLOAT_0;
 	}

	/// @brief プレイヤーが落下したらリスポーンする
	if (m_position.y < FALLING_HEIGHT) {
		/// @brief リスポーン時にスコアの減算
		m_ui->AddScore(m_myNumber, SCORE_PULL);
		/// @brief 敵を倒したときにボールを蹴ったプレイヤーにスコアの加算
		m_ui->AddScore(GetKillerPlayerNumber(),SCORE_ADD);
		ReSpawn();
	}
	
	
}

void Player::Rotation()
{
	/// @brief ダメージ中、ガード中、動いていないときは回転しない
	if (m_damage == true || m_guard == true || m_moveSpeed.x == FLOAT_0 && m_moveSpeed.z == FLOAT_0) {
		m_anim = enAnimation_Idle;
		return;
	}
	m_qRot.SetRotation(Vector3::AxisY, atan2(m_moveSpeed.x, m_moveSpeed.z));
	m_anim = enAnimation_Walk;
}

void Player::IsKick()
{
	/// @brief ボールとの距離が一定以下の時のみ判定
	if (m_ballDistance < KICK_POSSIBLE_DISTANCE) {
		m_direction.Normalize();
		float matchRate = Dot(m_direction, m_toBallVec);
		if (matchRate > 0.7f) {
			m_kickFlag = true;
		}
		else {
			m_kickFlag = false;
		}
	}
	else {
		m_kickFlag = false;
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


}

void Player::BallCollide()
{
	/// @brief ボールと自分の位置から吹き飛ばされる方向を決める
	Vector3 repulsiveForce = m_position - m_ball->GetPosition();
	repulsiveForce.y = FLOAT_0;
	repulsiveForce.Normalize();
	if (m_ball->IsMove() == true) {
		repulsiveForce *= m_ball->GetVelocity() * FLOAT_2;
		repulsiveForce.y = m_ball->GetVelocity() * FLOAT_1;
		m_moveSpeed = repulsiveForce * FLOAT_2;
		m_ball->SetMoveDirection(repulsiveForce * FLOAT_MINUS_1);
		m_damage = true;
		/// @brief 蹴ったプレイヤー以外に当たり、リスポーン時じゃない時にスコアの加算
		if (m_myNumber != m_ball->GetPlayerInformation() && m_dieFlag == false) {
			m_ui->AddScore(m_ball->GetPlayerInformation(), SCORE_ADD);
			SetKillerPlayerNumber(m_myNumber);
		}
	}
	
}

void Player::Guard()
{
	/// @brief ガード中は移動速度を下げる
	m_moveSpeed.x /= FLOAT_2;
	m_moveSpeed.z /= FLOAT_2;
	
	if (m_ballDistance < GUARD_DISTANCE) {

		/// @brief ボールの勢いに応じて耐久値を減らす
		float shieldDamage = 10.0f * (m_ball->GetVelocity() / 1);
		m_guardDurability -= shieldDamage;
		if (m_guardDurability <= 0.0f)
		{
			m_guardDurability = 0.0f;
			m_breakGuard = true;
			return;
		}

		Vector3 repulsiveForce = m_position - m_ball->GetPosition();
		repulsiveForce.Normalize();
		repulsiveForce *= m_ball->GetVelocity();
		repulsiveForce.y = m_ball->GetVelocity() * FLOAT_01;
		m_moveSpeed += repulsiveForce;
		m_ball->SetVelocity(m_ball->GetVelocity() / FLOAT_2);
		m_ball->SetMoveDirection(repulsiveForce * FLOAT_MINUS_1);
		
		
	}
	/// @brief ガード中は耐久値(guardDurability)が減り続ける
	m_guardDurability -= 0.555f;
	if (m_guardDurability <= 0.0f) {
		m_guardDurability = 0.0f;
		m_breakGuard = true;
	}

	if (m_ballDistance < GUARDEFFECT_HIT_DISTANCE && m_ball->IsMove() == true) {
		//ガードヒットエフェクトの発生
		m_shieldHitEffectCounter++;
		if (m_shieldHitEffectCounter % 30 == 1) {

			//エフェクト発生位置を決めるためのベクトル
			Vector3 shieldHitPos = Vector3::Zero;

			float shieldHitAngle = 0.0f;

			//自身からボールへのベクトル
			Vector3 toBallDirection = m_ball->GetPosition() - m_position;
			//y成分を0にする
			toBallDirection.y = 0.0f;
			//正規化
			toBallDirection.Normalize();

			//エフェクトの向きを決めるためのクォータニオン
			Quaternion shieldHitRot = Quaternion::Identity;

			//自身からボールへのベクトルのx,z成分から角度を出す
			shieldHitAngle = atan2f(toBallDirection.x, toBallDirection.z);

			shieldHitRot.SetRotation(Vector3::AxisY, shieldHitAngle);

			//自身とボールの間にエフェクトを発生させる
			shieldHitPos.Lerp(0.5f, m_position, m_ball->GetPosition());
			//プレイヤーのy座標ちょっと上に発生
			shieldHitPos.y += 80.0f;

			m_shieldHitEffect.Play();
			m_shieldHitEffect.SetPosition(shieldHitPos);
			m_shieldHitEffect.SetRotation(shieldHitRot);
			m_shieldHitEffect.SetScale(GUARDEFFECT_HIT_SCALE);
			m_shieldHitEffect.Update();
		}
	}

}

void Player::ReSpawn() {
	/// @brief スタート位置にリスポーンさせる
	m_position = m_startPos;
	m_charaCon.SetPosition(m_position);
	
	
	m_dieFlag = true;
	

}

void Player::Muteki()
{
	m_mutekiTime++;
	/// @brief リスポーン時に少しの間ボールに当たらなくなる
	if (m_mutekiTime == MUTEKI_TIME) {
		m_dieFlag = false;
		m_mutekiTime = TIME_ZERO;
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
	default:
		break;
	}
}

void Player::Update()
{

	/// @brief スティック入力を受け取る
	m_Lstickx = g_pad[m_myNumber]->GetLStickXF();
	m_Lsticky = g_pad[m_myNumber]->GetLStickYF();

	/// @brief ダメージ中はスティック入力を受け付けない
	if (m_damage == true) {
		m_Lstickx = FLOAT_0;
		m_Lsticky = FLOAT_0;
		m_damageTime += FLOAT_1;
	}
	if (m_damageTime > DAMAGE_RETURN_TIME) {
		m_damageTime = FLOAT_1;
		m_damage = false;
	}
	if (m_breakGuard == true)
	{
		m_Lstickx = FLOAT_0;
		m_Lsticky = FLOAT_0;
		m_damageTime += FLOAT_1;
	}

	BallDistanceCalculation();
	Move();
	Rotation();
	IsKick();
	
	if (m_kickFlag == true) {
		if (g_pad[m_myNumber]->IsTrigger(enButtonA)) {

			//キックエフェクト再生処理//
			
			//エフェクト発生位置を決めるためのベクトル
			Vector3 efcPos = Vector3::Zero;
			//ボールへの方向
			Vector3 toBallDir = m_ball->GetPosition() - m_position;
			toBallDir.y = 0.0f;
			//正規化
			toBallDir.Normalize();
			//回転方向を決めるためのクォータニオン
			Quaternion efcRot = Quaternion::Identity;
			//角度
			float efcAngle = 0.0f;
			//ボールへのベクトルから発生させる角度を計算
			efcAngle = atan2(toBallDir.x, toBallDir.z);

			efcRot.SetRotation(Vector3::AxisY, efcAngle);
			
			//プレイヤー座標とボール座標を線形補完し、発生位置を決定
			//補間率が0に近ければプレイヤー側、1に近ければボール側に発生する
			efcPos.Lerp(KICKEFFECT_POSITION_RATE, m_position, m_ball->GetPosition());
			efcPos.y += 80.0f;

			m_kickEffect.Play();
			m_kickEffect.SetPosition(efcPos);
			m_kickEffect.SetRotation(efcRot);
			m_kickEffect.SetScale(KICKEFFECT_SCALE);
			//キックした時の座標を保持したいのでここで更新
			m_kickEffect.Update();

			KickBall();
		}
	}

	/// @brief 非ガード時、ガード耐久値を回復
	if (m_guard == false) {
		m_guardDurability += 0.555f;
	}
	/// @brief 再展開可能まで
	if (m_guardDurability >= 100.0f && m_breakGuard == true)
	{
		m_breakGuard = false;
		
	}
	/// @brief ガード耐久値を100より上にならないようにする奴
	if (m_guardDurability >= 100.0f)
	{
		m_guardDurability = 100.0f;
	}
	
	/// @brief ボールとの距離が一定以下で吹き飛ぶ
	if (m_breakGuard == true) {
		if (m_ballDistance < GUARD_DISTANCE && m_dieFlag == false) {
			BallCollide();
		}
	}
	else {
		if (m_ballDistance < COLLIDE_DISTANCE && m_dieFlag == false) {
			BallCollide();
		}
	}
	/// @brief LB1を押している間ガード
	if (g_pad[m_myNumber]->IsPress(enButtonLB1) && m_breakGuard == false) {
		m_guard = true;
	}
	else {
		m_guard = false;
		m_guardEffectCouter = 0;
		m_shieldHitEffectCounter = 0;
	}

	/// @brief ガード可能ならガードの処理
	if (m_guard == true && m_breakGuard == false) {
		Guard();
		
		//シールドエフェクト発生処理//
		//カウンターに値を加算
		m_guardEffectCouter += 1;
		//規定フレーム毎にエフェクトを発生
		if (m_guardEffectCouter % 20 == 1) {
			m_guardEffect.Play();
		}
	}

	//ガードブレイクエフェクト発生処理//
	
	//前フレームにガードブレイクしておらず...
	if (m_breakGuardPrevFrame == false) {
		//現フレームでガードブレイクしていたらガードブレイクエフェクトを再生
		if (m_breakGuard == true) {
			//ガードエフェクトの再生を停止
			m_guardEffect.Stop();
			//ガードブレイクエフェクトを再生
			m_guardBreakEffect.Play();
			////行動不能エフェクトを再生
			//m_knockOutEffect.Play();
			
			Vector3 breakPos = m_position;
			breakPos.y += 80.0f;

			m_guardBreakEffect.SetPosition(breakPos);
			m_guardBreakEffect.SetScale(GUARDEFFECT_BREAK_SCALE);
			m_guardBreakEffect.Update();
		}
	}

	//シールド回復エフェクト発生処理//
	
	//前フレームにガードブレイクしており...
	if (m_breakGuardPrevFrame == true) {
		//現フレームでガードブレイクしていなければ(シールドが回復していたら)回復エフェクトを再生
		if (m_breakGuard == false) {
			m_shieldRepairEffect.Play();
			//行動不能エフェクトの再生を停止
			m_knockOutEffect.Stop();
		}
	}


	//ガード開始時のエフェクト発生処理//
	
	//ボタン押下時かつガードブレイクしていないときに実行
	if (g_pad[m_myNumber]->IsTrigger(enButtonLB1) && m_breakGuard == false) {
		m_guardBeginEffect.Play();
	}

	//行動不能エフェクトの発生,停止処理//
	//行動不能エフェクトはガードブレイク時とダメージ時に発生する
	
	//前フレームでガードブレイクしてない時
	if (m_breakGuardPrevFrame == false) {
		//前フレームでダメージ状態でなく、現フレームでダメージ時
		if (m_breakGuard == false && m_damagePrevFrame == false && m_damage == true) {
			//再生
			m_knockOutEffect.Play();
		}
		//前フレームでダメージ状態で、現フレームで非ダメージ時(=回復時)
		else if (m_breakGuard == false && m_damagePrevFrame == true && m_damage == false) {
			//再生を停止
			m_knockOutEffect.Stop();
		}
		//現フレームでガードブレイクした時
		else if (m_breakGuard == true) {
			//再生
			m_knockOutEffect.Play();
		}
		//吹っ飛ばされて死んだとき
		else if (m_dieFlag == true) {
			m_knockOutEffect.Stop();
		}
	}
	//前フレームでガードブレイクしているとき
	else {
		//現フレームでガードブレイク状態でないとき(=回復時)
		if (m_breakGuard == false) {
			//再生を停止
			m_knockOutEffect.Stop();
		}
		//吹っ飛ばされて死んだとき
		else if (m_dieFlag == true) {
			m_knockOutEffect.Stop();
		}
	}
	


	if (m_dieFlag == true) {
		Muteki();
	}

	/// @brief 自分に当たるスポットライトの位置と方向を設定
	Vector3 pos = m_position;
	pos.y = SPOT_LIGHT_HEIGHT;
	m_lig->SetSpotLightPos(m_myNumber, pos);

	Vector3 dir = m_position - m_lig->GetSpotLightPos(m_myNumber);
	m_lig->SetSpotLightDirection(m_myNumber,dir);

	/// @brief キャラクターコントローラーで座標を決める
	m_position = m_charaCon.Execute(m_moveSpeed, FLOAT_1);
	

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_qRot);

	//エフェクト関係の更新処理//

	//ガードエフェクトの更新
	Vector3 efcGuardPos = m_position;
	//プレイヤー座標よりちょっと上にする
	efcGuardPos.y += GUARDEFFECT_POS_Y;
	m_guardEffect.SetPosition(efcGuardPos);
	m_guardEffect.SetScale(GUARDEFFECT_SCALE);
	m_guardEffect.Update();
	
	//ガード予兆エフェクトの更新
	m_guardBeginEffect.SetPosition(efcGuardPos);
	m_guardBeginEffect.SetScale(GUARDEFFECT_BEGIN_SCALE);
	m_guardBeginEffect.Update();
	
	//シールド回復エフェクトの更新
	m_shieldRepairEffect.SetPosition(efcGuardPos);
	m_shieldRepairEffect.SetScale(GUARDEFFECT_REPAIR_SCALE);
	m_shieldRepairEffect.Update();

	//行動不能エフェクトの更新
	m_knockOutEffect.SetPosition(efcGuardPos);
	m_knockOutEffect.SetScale(KNOCKOUTEFFECT_SCALE);
	m_knockOutEffect.Update();

	//現フレームのガード状態を記録
	m_breakGuardPrevFrame = m_breakGuard;
	//現フレームのダメージフラグ状態を記録
	m_damagePrevFrame = m_damage;

	/// @brief アニメーション
	Animation();

	if (g_pad[m_myNumber]->IsTrigger(enButtonStart)) {
		ReSpawn();
	}
}

void Player::BallDistanceCalculation()
{
	m_toBallVec = m_ball->GetPosition() - m_position;
	m_ballDistance = m_toBallVec.Length();
}