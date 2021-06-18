#include "stdafx.h"
#include "Player.h"

namespace {
	//キック時のエフェクト用定数
	const char16_t* KICKEFFECT_FILEPATH = u"Assets/effect/kick.efk";				//キックエフェクトのファイルパス
	//ガード時のエフェクト
	const char16_t* GUARDEFFECT_FILEPATH = u"Assets/effect/shield.efk";				//ガード時のエフェクトファイルパス

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
}

Player::Player()
{
	//キック時のエフェクトを初期化
	m_kickEffect.Init(KICKEFFECT_FILEPATH);
	//ガード時のエフェクトを初期化
	m_guardEffect.Init(GUARDEFFECT_FILEPATH);
	
	m_moveVelocity = 0.9f;
	m_kickPower = 10.0f;
	m_gravity = 5.0f;
	m_charaCon.Init(PLAYER_RADIUS, PLAYER_HEIGHT, m_position);
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
}

bool Player::Start()
{
	m_lig = FindGO<Lighting>(LIGHTING_NAME);
	m_ball = FindGO<Ball>(BALL_NAME);
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init(UNITYCHAN_MODEL);
	return true;
}

void Player::SetPlayerNumber(int num)
{
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
	Vector3 m_returnPos = m_position;
	//スティック入力でカメラ方向に移動
	m_moveSpeed += g_camera3D->GetRight()* m_Lstickx;
	m_moveSpeed += g_camera3D->GetForward()* m_Lsticky;
	
	m_moveSpeed.y -= m_gravity;

	if (m_damage == false) {
		m_friction = NORMAL_FRICTION;
	}
	else {
		m_friction = DAMAGE_FRICYION;
	}
	m_moveSpeed -= m_moveSpeed * m_friction;

	if (m_damage == false && m_guard == false && m_moveSpeed.x != FLOAT_0 || m_moveSpeed.z != FLOAT_0) {
		m_direction = m_moveSpeed;
	}
	
	m_moveSpeed *= m_moveVelocity;

	if (m_position.y < FALLING_HEIGHT) {
		ReSpawn();
	}
	
	
}

void Player::Rotation()
{
	if (m_damage == true || m_guard == true || m_moveSpeed.x == FLOAT_0 && m_moveSpeed.z == FLOAT_0) {
		return;
	}
	m_qRot.SetRotation(Vector3::AxisY, atan2(m_moveSpeed.x, m_moveSpeed.z));
}

void Player::KickBall()
{

	m_ball->SetMoveDirection(m_direction);
	m_ball->Acceleration(m_kickPower);
	m_ball->SetBallLightColor(m_playerColor);
	m_ball->MoveStart();


}

void Player::BallCollide()
{
	Vector3 repulsiveForce = m_position - m_ball->GetPosition();
	repulsiveForce.y = FLOAT_0;
	repulsiveForce.Normalize();
	if (m_ball->IsMove() == true) {
		repulsiveForce *= m_ball->GetVelocity() * FLOAT_2;
		repulsiveForce.y = m_ball->GetVelocity() * FLOAT_1;
		m_moveSpeed = repulsiveForce * FLOAT_2;
		m_ball->BounceX();
		m_ball->BounceZ();
		m_damage = true;
	}
	
}

void Player::Guard()
{
	m_moveSpeed.x /= FLOAT_2;
	m_moveSpeed.z /= FLOAT_2;
	if (m_ballDistance < GUARD_DISTANCE) {
		Vector3 repulsiveForce = m_position - m_ball->GetPosition();
		repulsiveForce.Normalize();
		repulsiveForce *= m_ball->GetVelocity();
		m_moveSpeed += repulsiveForce;
		float downVelocity = m_ball->GetVelocity();
		m_ball->SetVelocity(m_ball->GetVelocity() / FLOAT_2);
		m_ball->BounceX();
		m_ball->BounceZ();
	}
}

void Player::Update()
{
	m_Lstickx = g_pad[m_myNumber]->GetLStickXF();
	m_Lsticky = g_pad[m_myNumber]->GetLStickYF();

	if (m_damage == true) {
		m_Lstickx = FLOAT_0;
		m_Lsticky = FLOAT_0;
		m_damageTime += FLOAT_1;
	}
	if (m_damageTime > DAMAGE_RETURN_TIME) {
		m_damageTime = FLOAT_1;
		m_damage = false;
	}

	BallDistanceCalculation();
	Move();
	Rotation();
	
	if (m_ballDistance < KICK_POSSIBLE_DISTANCE) {
		if (g_pad[m_myNumber]->IsTrigger(enButtonA)) {
			
			//キックエフェクト再生処理//
			
			//キックエフェクト拡大率の設定
			Vector3 efcScale = { 25.0f,25.0f,1.0f };
			m_kickEffect.Play();
			m_kickEffect.SetPosition(m_position);
			m_kickEffect.SetRotation(m_qRot);
			m_kickEffect.SetScale(efcScale);

			m_kickEffect.Update();

			KickBall();
		}
	}
	else {
	}
	if (m_ballDistance < COLLIDE_DISTANCE) {
		BallCollide();
	}
	if (g_pad[m_myNumber]->IsPress(enButtonLB1)) {
		m_guard = true;
	}
	else {
		m_guard = false;
		m_guardEffectCouter = 0;
	}

	if (m_guard == true) {
		Guard();
		
		//シールドエフェクト発生処理//
		//カウンターに値を加算
		m_guardEffectCouter += 1;
		//規定フレーム毎にエフェクトを発生
		if (m_guardEffectCouter == 1) {
			m_guardEffect.Play();
		}
		if (m_guardEffectCouter % 20 == 19) {
			m_guardEffect.Play();
		}

	}

	Vector3 pos = m_startPos;
	pos.y = SPOT_LIGHT_HEIGHT;
	m_lig->SetSpotLightPos(m_myNumber, pos);

	Vector3 dir = m_position - m_lig->GetSpotLightPos(m_myNumber);
	m_lig->SetSpotLightDirection(m_myNumber,dir);

	m_position = m_charaCon.Execute(m_moveSpeed, FLOAT_1);
	

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_qRot);


	//ガード時のエフェクトの座標などを反映
	Vector3 efcGuardPos = m_position;
	efcGuardPos.y += 80.0f;
	m_guardEffect.SetPosition(efcGuardPos);
	m_guardEffect.SetScale({ 60.0f,60.0f,60.0f });
	m_guardEffect.Update();

}

void Player::BallDistanceCalculation()
{
	Vector3 vec = m_ball->GetPosition() - m_position;
	m_ballDistance = vec.Length();
}