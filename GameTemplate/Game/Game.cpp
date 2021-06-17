#include "stdafx.h"
#include "Game.h"
#include "Title.h"

Game::Game()
{
	m_playerNum = 4;
	m_lighting = NewGO<Lighting>(0,"Lighting");
	for (int i = 0; i < m_playerNum; i++) {
		m_player[i] = NewGO<Player>(0);
	}
	m_gameCamera = NewGO<GameCamera>(0,"GameCamera");
	m_backGround = NewGO<BackGround>(0, "BackGround");
	m_ball = NewGO<Ball>(0, "Ball");

	m_skinModelRender3 = NewGO<SkinModelRender>(0);
	m_skinModelRender3->Init("Assets/modelData/unityChan.tkm", m_lighting->GetLightAddress());
	m_skinModelRender3->SetScale({ 0.3f,0.3f,0.3f });

	
}

Game::~Game()
{
	
	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);
	DeleteGO(m_ball);
	DeleteGO(m_skinModelRender3);
	for (int i = 0; i < m_playerNum; i++) {
		DeleteGO(m_player[i]);
	}
	DeleteGO(m_lighting);
	NewGO<Title>(0, "Title");
}

bool Game::Start()
{
	for (int i = 0; i < m_playerNum; i++) {
		m_player[i]->SetPlayerNumber(i);
	}
	return true;
}

void Game::Update()
{
	if (g_pad[0]->IsTrigger(enButtonSelect)) {
		DeleteGO(this);
	}
	m_skinModelRender3->SetPosition(m_lighting->GetSpotLightPos());
}