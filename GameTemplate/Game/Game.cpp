#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	m_lighting = NewGO<Lighting>(0,"Lighting");
	m_player = NewGO<Player>(0, "Player");
	m_gameCamera = NewGO<GameCamera>(0,"GameCamera");
	m_backGround = NewGO<BackGround>(0, "BackGround");
	m_ball = NewGO<Ball>(0, "Ball");

	/*m_skinModelRender2 = NewGO<SkinModelRender>(0);
	m_skinModelRender2->Init("Assets/modelData/sphere/sphere.tkm", m_lighting->GetLightAddress());
	m_skinModelRender2->SetScale({ 0.3f,0.3f,0.3f });*/

	m_skinModelRender3 = NewGO<SkinModelRender>(0);
	m_skinModelRender3->Init("Assets/modelData/unityChan.tkm", m_lighting->GetLightAddress());
	m_skinModelRender3->SetScale({ 0.3f,0.3f,0.3f });

	/*m_bg = NewGO<SkinModelRender>(0);
	m_bg->Init("Assets/modelData/bg/testmap_s.tkm", m_lighting->GetLightAddress());*/
}

Game::~Game()
{
	DeleteGO(m_skinModelRender);
}

bool Game::Start()
{
	
	
	return true;
}

void Game::Update()
{
	//m_skinModelRender2->SetPosition(m_lighting->GetPointLightPos());
	m_skinModelRender3->SetPosition(m_lighting->GetSpotLightPos());
}