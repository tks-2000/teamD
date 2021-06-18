#include "stdafx.h"
#include "Game.h"
#include "Title.h"

Game::Game()
{
	m_playerNum = 4;
	m_lighting = NewGO<Lighting>(0,LIGHTING_NAME);
	for (int i = 0; i < m_playerNum; i++) {
		m_player[i] = NewGO<Player>(0,PLAYER_NAME[i]);
	}
	m_gameCamera = NewGO<GameCamera>(0,GAME_CAMERA_NAME);
	m_backGround = NewGO<BackGround>(0,BACK_GROUND_NAME);
	m_ball = NewGO<Ball>(0, BALL_NAME);
}

Game::~Game()
{
	//ゲームシーン中に発生している全てのエフェクトを停止
	EffectEngine::GetInstance()->AllStop();
	
	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);
	DeleteGO(m_ball);
	
	for (int i = 0; i < m_playerNum; i++) {
		DeleteGO(m_player[i]);
	}
	DeleteGO(m_lighting);
	NewGO<Title>(0, TITLE_NAME);
}

bool Game::Start()
{
	m_lighting->GetLight();
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
}