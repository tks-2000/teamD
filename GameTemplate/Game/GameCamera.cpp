#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
	m_toPosition = { 0.0f,200.0f,-500.0f };
}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("Player");
	return true;
}

void GameCamera::Move()
{
	m_targetPos = m_player->GetPosition();

	m_position = m_targetPos + m_toPosition;
	m_targetPos.y += 50.0f;
}

void GameCamera::Rotation()
{
	m_qRot.SetRotationDegY(g_pad[0]->GetRStickXF());
	m_qRot.Apply(m_toPosition);
	m_qRot.SetRotationDegX(g_pad[0]->GetRStickYF());
	m_qRot.Apply(m_toPosition);
}

void GameCamera::Update()
{
	
	Move();
	Rotation();

	g_camera3D->SetPosition(m_position);
	g_camera3D->SetTarget(m_targetPos);

}