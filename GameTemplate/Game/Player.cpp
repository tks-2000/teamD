#include "stdafx.h"
#include "Player.h"
//#include "effect/effect.h"

namespace {
	float KICK_POSSIBLE_DISTANCE = 150.0f;
	float GUARD_DISTANCE = 100.0f;
	float COLLIDE_DISTANCE = 50.0f;
}

Player::Player()
{
	m_position.y = 50.0f;
	m_kickPower = 10.0f;
}

Player::Player(int num)
{
	m_myNumber = num;
	m_position.y = 50.0f;
	m_kickPower = 10.0f;
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

void Player::Move()
{
	//�X�e�B�b�N���͂ŃJ���������Ɉړ�
	m_moveSpeed += g_camera3D->GetRight()* m_Lstickx;
	m_moveSpeed += g_camera3D->GetForward()* m_Lsticky;
	
	m_moveSpeed.y = 0.0f;

	m_moveSpeed -= m_moveSpeed * 0.05f;

	if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f) {
		m_direction = m_moveSpeed;
	}

	m_position += m_moveSpeed * 0.5f;


	//���W�ňړ�����
	if (m_position.x > 700.0f) {
		m_position.x = 700.0f;
	}
	if (m_position.x < -700.0f) {
		m_position.x = -700.0f;
	}
	if (m_position.z > 700.0f) {
		m_position.z = 700.0f;
	}
	if (m_position.z < -700.0f) {
		m_position.z = -700.0f;
	}
	
}

void Player::Rotation()
{
	if (m_moveSpeed.x == 0.0f && m_moveSpeed.z == 0.0f) {
		return;
	}
	m_qRot.SetRotation(Vector3::AxisY, atan2(m_moveSpeed.x, m_moveSpeed.z));
}

void Player::KickBall()
{

	m_ball->SetMoveDirection(m_direction);
	m_ball->Acceleration(m_kickPower);
	m_ball->MoveStart();


}

void Player::BallCollide()
{
	Vector3 repulsiveForce = m_position - m_ball->GetPosition();
	repulsiveForce.Normalize();
	repulsiveForce *= m_ball->GetVelocity();
	m_moveSpeed += repulsiveForce * 2.0f;
	m_ball->BounceX();
	m_ball->BounceZ();
}

void Player::Guard()
{
	m_moveSpeed /= 2.0f;
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

	Move();
	Rotation();
	BallDistanceCalculation();
	if (m_ballDistance < KICK_POSSIBLE_DISTANCE) {
		m_lig->SetPointLightColor({ 10.0f,0.0f,0.0f });
		if (g_pad[m_myNumber]->IsTrigger(enButtonA)) {
			KickBall();
		}
	}
	else {
		if (m_ball->IsMove() == true) {
			m_lig->SetPointLightColor({ 5.0f,0.0f,0.0f });
		}
		else {
			m_lig->SetPointLightColor({ 0.0f,0.0f,0.0f });
		}
	}
	if (m_ballDistance < COLLIDE_DISTANCE && m_ball->IsMove() == true) {
		BallCollide();
	}
	if (g_pad[m_myNumber]->IsPress(enButtonLB1)) {
		m_guard = true;
	}
	else {
		m_guard = false;
	}

	if (m_guard == true) {
		Guard();
	}

	Vector3 vec = m_position - m_lig->GetSpotLightPos();
	m_lig->SetSpotLightDirection(vec);

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_qRot);
}

void Player::BallDistanceCalculation()
{
	Vector3 vec = m_ball->GetPosition() - m_position;
	m_ballDistance = vec.Length();
}