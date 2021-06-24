#include "stdafx.h"
#include "Game.h"
#include "Title.h"

Game::Game()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_playerNum = m_gameDirector->GetPlayerNum();
	//m_playerNum = 4;
	m_lighting = NewGO<Lighting>(0,LIGHTING_NAME);
	for (int i = 0; i < m_playerNum; i++) {
		m_player[i] = NewGO<Player>(0,PLAYER_NAME[i]);
	}
	m_gameCamera = NewGO<GameCamera>(0,GAME_CAMERA_NAME);
	m_backGround = NewGO<BackGround>(0,BACK_GROUND_NAME);
	m_ball = NewGO<Ball>(0, BALL_NAME);
	
	m_ui = NewGO<GameUI>(0,GAME_UI_NAME);
	m_sky = NewGO<Sky>(0, "Sky");
}

Game::~Game()
{
	//�Q�[���V�[�����ɔ������Ă���S�ẴG�t�F�N�g���~
	EffectEngine::GetInstance()->AllStop();
	
	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);
	DeleteGO(m_ball);
	DeleteGO(m_ui);
	DeleteGO(m_sky);
	
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
		m_gameDirector->GameEnd();
	}
}