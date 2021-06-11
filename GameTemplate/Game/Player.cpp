#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_position.y = 50.0f;
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
}

bool Player::Start()
{
	m_lig = FindGO<Lighting>("Lighting");
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/unityChan.tkm", m_lig->GetLightAddress());
	return true;
}

void Player::Move()
{
	
	m_moveSpeed = g_camera3D->GetRight()* m_Lstickx;
	m_moveSpeed += g_camera3D->GetForward()* m_Lsticky;
	
	m_moveSpeed.y = 0.0f;

	m_position += m_moveSpeed * 2.0f;
	
}

void Player::Rotation()
{
	if (m_moveSpeed.x == 0.0f && m_moveSpeed.z == 0.0f) {
		return;
	}
	m_qRot.SetRotation(Vector3::AxisY, atan2(m_moveSpeed.x, m_moveSpeed.z));
}

void Player::Update()
{
	m_Lstickx = g_pad[0]->GetLStickXF();
	m_Lsticky = g_pad[0]->GetLStickYF();

	Move();
	Rotation();

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_qRot);
}