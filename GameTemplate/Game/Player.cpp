#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	
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
	m_moveSpeed.x = m_Lstickx;
	m_moveSpeed.z = m_Lsticky;


	m_position += m_moveSpeed;
}

void Player::Update()
{
	m_Lstickx = g_pad[0]->GetLStickXF();
	m_Lsticky = g_pad[0]->GetLStickYF();

	Move();

	m_skinModelRender->SetPosition(m_position);
}