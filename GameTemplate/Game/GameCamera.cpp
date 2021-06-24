#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
	
}

GameCamera::~GameCamera()
{
	m_angleX = 0.4f;
	m_qRotX.SetRotation(g_camera3D->GetRight(), m_angleX);
	m_qRotX.Apply(m_toPosition);
}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("Player");
	m_backGround = FindGO<BackGround>("BackGround");
	m_toPosition = { 0.0f,1400.0f,-800.0f };
	g_camera3D->SetFar(10000000.0f);
	return true;
}

void GameCamera::Move()
{
	m_targetPos = m_backGround->GetPosition();
	m_position = m_targetPos + m_toPosition;
	m_targetPos.y += 50.0f;
}

void GameCamera::Rotation()
{
	m_qRotY.SetRotation(Vector3::AxisY,g_pad[0]->GetRStickXF()* 0.01f);
	m_qRotY.Apply(m_toPosition);
	
}

void GameCamera::Update()
{
	
	Move();
	Rotation();

	g_camera3D->SetPosition(m_position);
	g_camera3D->SetTarget(m_targetPos);

}