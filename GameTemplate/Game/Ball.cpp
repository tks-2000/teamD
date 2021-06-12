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
	
	return true;
}

void Ball::Move()
{
	m_moveSpeed = m_moveDirection * 10.0f;

	m_moveSpeed.y = 0.0f;

	m_position += m_moveSpeed;
}

void Ball::Update()
{
	if (m_moveFlag == true) {
		Move();
	}
	m_skinModelRender->SetPosition(m_position);
}