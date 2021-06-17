#include "stdafx.h"
#include "Ball.h"

Ball::Ball()
{
	m_moveFlag = true;
	m_position.y = 1000.0f;
	m_scale = { 0.5f,0.5f,0.5f };
	m_gravity = 5.0f;
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
	m_charaCon.Init(40.0f, 40.0f, m_position);
	return true;
}

void Ball::Move()
{
	m_moveSpeed = m_moveDirection * m_moveVelocity;
	m_moveSpeed.y -= m_gravity;

	m_position = m_charaCon.Execute(m_moveSpeed,1.0f);

	if (m_position.x > 650.0f) {
		m_position.x = 650.0f;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.x *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}
	if (m_position.x < -650.0f) {
		m_position.x = -650.0f;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.x *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}
	if (m_position.z > 650.0f) {
		m_position.z = 650.0f;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.z *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}
	if (m_position.z < -650.0f) {
		m_position.z = -650.0f;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.z *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}

	m_moveVelocity -= m_moveVelocity * 0.001f;

	if (m_moveSpeed.Length() < 1.0f)
	{
		m_moveDirection = Vector3::Zero;
		m_moveSpeed = Vector3::Zero;
		m_moveFlag = false;
	}

	
}

void Ball::Rotation()
{
	m_axisRotation = Cross(m_moveDirection, Vector3::AxisY);
	m_qRot.SetRotation(m_axisRotation, m_angle);
	m_angle -= 0.1f;
}

void Ball::Update()
{
	if (m_moveFlag == true) {
		m_lig->SetPointLightColor(m_pointLigColor);
		Move();
		Rotation();
	}
	else {
		m_lig->SetPointLightColor(COLORLESS);
	}

	Vector3 modelpos = m_position;
	modelpos.y += 60.0f;
	m_skinModelRender->SetPosition(modelpos);
	m_skinModelRender->SetRotation(m_qRot);
	m_skinModelRender->SetScale(m_scale);

	m_lig->SetPointLighitPos(modelpos);
}