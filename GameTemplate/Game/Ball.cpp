#include "stdafx.h"
#include "Ball.h"

Ball::Ball()
{

}

Ball::~Ball()
{

}

bool Ball::Start()
{
	m_lig = FindGO<Lighting>("Lighting");
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/sphere/sphere.tkm", m_lig->GetLightAddress());
	m_position.y += 40.0f;
	
	return true;
}

void Ball::Move()
{
	m_moveSpeed = m_moveDirection * m_moveVelocity;

	m_position += m_moveSpeed;

	if (m_position.x > 650.0f) {
		m_position.x = 650.0f;
		m_moveDirection.x *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}
	if (m_position.x < -650.0f) {
		m_position.x = -650.0f;
		m_moveDirection.x *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}
	if (m_position.z > 650.0f) {
		m_position.z = 650.0f;
		m_moveDirection.z *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}
	if (m_position.z < -650.0f) {
		m_position.z = -650.0f;
		m_moveDirection.z *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}

	m_moveVelocity -= m_moveVelocity * 0.001f;

	if (m_moveVelocity < 0.0f)
	{
		m_moveSpeed = Vector3::Zero;
		m_moveFlag = false;
	}

	
}

void Ball::Update()
{
	if (m_moveFlag == true) {
		Move();
	}
	
	m_skinModelRender->SetPosition(m_position);

	m_lig->SetPointLighitPos(m_position);
}