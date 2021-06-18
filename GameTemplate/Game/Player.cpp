#include "stdafx.h"
#include "Player.h"

namespace {
	float KICK_POSSIBLE_DISTANCE = 200.0f;
	float GUARD_DISTANCE = 120.0f;
	float COLLIDE_DISTANCE = 80.0f;
	float FALLING_HEIGHT = -1000.0f;
	Vector3 PLAYER1_STARTPOS = { -600.0f,200.0f,600.0f };
	Vector3 PLAYER2_STARTPOS = { 600.0f,200.0f,600.0f };
	Vector3 PLAYER3_STARTPOS = { -600.0f,200.0f,-600.0f };
	Vector3 PLAYER4_STARTPOS = { 600.0f,200.0f,-600.0f };
	
	//キック時のエフェクト用定数
	const char16_t* KICKEFFECT_FILEPATH = u"Assets/effect/kick.efk";				//キックエフェクトのファイルパス
	//ガード時のエフェクト
	const char16_t* GUARDEFFECT_FILEPATH = u"Assets/effect/shield.efk";				//ガード時のエフェクトファイルパス

}

Player::Player()
{
	//キック時のエフェクトを初期化
	m_kickEffect.Init(KICKEFFECT_FILEPATH);
	//ガード時のエフェクトを初期化
	m_guardEffect.Init(GUARDEFFECT_FILEPATH);

	m_kickPower = 10.0f;
	m_gravity = 5.0f;
	m_charaCon.Init(20.0f, 50.0f, m_position);
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
}

bool Player::Start()
{
	m_lig = FindGO<Lighting>("Lighting");
	m_ball = FindGO<Ball>("Ball");
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/unityChan.tkm", m_lig->GetLightAddress());
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
	
}

void Player::Move()
{
	Vector3 m_returnPos = m_position;
	//スティック入力でカメラ方向に移動
	m_moveSpeed += g_camera3D->GetRight()* m_Lstickx;
	m_moveSpeed += g_camera3D->GetForward()* m_Lsticky;
	
	m_moveSpeed.y -= m_gravity;

	if (m_damage == false) {
		m_friction = 0.01f;
	}
	else {
		m_friction = 0.001f;
	}
	m_moveSpeed -= m_moveSpeed * m_friction;

	if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f) {
		m_direction = m_moveSpeed;
	}
	
	m_moveSpeed *= 0.9f;

	if (m_position.y < FALLING_HEIGHT) {
		ReSpawn();
	}
	
	
}

void Player::Rotation()
{
	if (m_damage == true || m_guard == true || m_moveSpeed.x == 0.0f && m_moveSpeed.z == 0.0f) {
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
	repulsiveForce.y = 0.0f;
	repulsiveForce.Normalize();
	if (m_ball->IsMove() == true) {
		repulsiveForce *= m_ball->GetVelocity() * 2.0f;
		repulsiveForce.y = m_ball->GetVelocity() * 1.0f;
		m_moveSpeed = repulsiveForce * 2.0f;
		m_ball->BounceX();
		m_ball->BounceZ();
		m_damage = true;
	}
	
}

void Player::Guard()
{
	m_moveSpeed.x /= 2.0f;
	m_moveSpeed.z /= 2.0f;
	if (m_ballDistance < GUARD_DISTANCE) {
		Vector3 repulsiveForce = m_position - m_ball->GetPosition();
		repulsiveForce.Normalize();
		repulsiveForce *= m_ball->GetVelocity();
		m_moveSpeed += repulsiveForce;
		float downVelocity = m_ball->GetVelocity();
		m_ball->SetVelocity(m_ball->GetVelocity() / 2.0f);
		m_ball->BounceX();
		m_ball->BounceZ();
	}
}

void Player::Update()
{
	m_Lstickx = g_pad[m_myNumber]->GetLStickXF();
	m_Lsticky = g_pad[m_myNumber]->GetLStickYF();

	if (m_damage == true) {
		m_Lstickx = 0.0f;
		m_Lsticky = 0.0f;
		m_damageTime += 1.0f;
	}
	if (m_damageTime > 100.0f) {
		m_damageTime = 0.0f;
		m_damage = false;
	}

	BallDistanceCalculation();
	Move();
	Rotation();
	
	if (m_ballDistance < KICK_POSSIBLE_DISTANCE) {
		m_lig->SetPointLightColor(m_playerColor * 2.0f);
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

	Vector3 vec = m_position - m_lig->GetSpotLightPos();
	m_lig->SetSpotLightDirection(vec);

	m_position = m_charaCon.Execute(m_moveSpeed, 1.0f);
	

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