#include "stdafx.h"
#include "Game.h"
#include "Title.h"

Game::Game()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_playerNum = m_gameDirector->GetPlayerNum();
	//m_timer = NewGO<Timer>(0, TIMER_NAME);
	for (int i = 0; i < m_playerNum; i++) {
		m_player[i] = NewGO<Player>(0,PLAYER_NAME[i]);
	}
	//m_playerEffect = NewGO<PlayerEffect>(0, PLAYER_EFFECT_NAME);
	m_gameCamera = NewGO<GameCamera>(0,GAME_CAMERA_NAME);
	m_backGround = NewGO<BackGround>(0,BACK_GROUND_NAME);
	m_ball = NewGO<Ball>(0, BALL_NAME);
	switch (m_gameDirector->GetGameMode())
	{
	case GameDirector::enNormal: {
		m_objects = NewGO<Objects>(0, OBJECTS_NAME);
	}break;
	case GameDirector::enSpecial: {

	}break;
	default:
		break;
	}
	
	m_ui = NewGO<GameUI>(0,GAME_UI_NAME);
	m_score = NewGO<Score>(0, SCORE_NAME);
}

Game::~Game()
{
	//DeleteGO(m_timer);
	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);
	DeleteGO(m_ball);
	DeleteGO(m_ui);
	DeleteGO(m_score);
	switch (m_gameDirector->GetGameMode())
	{
	case GameDirector::enNormal: {
		DeleteGO(m_objects);
	}break;
	case GameDirector::enSpecial: {

	}break;
	default:
		break;
	}
	
	DeleteGO(m_sky);

	for (int i = 0; i < m_playerNum; i++) {
		DeleteGO(m_player[i]);
	}
	//DeleteGO(m_playerEffect);
}

bool Game::Start()
{
	m_lighting->GetLight();
	for (int i = 0; i < m_playerNum; i++) {
		m_player[i]->SetPlayerNumber(i);
	}
	switch (m_gameDirector->GetGameMode())
	{
	case GameDirector::enNormal: {
		m_objects->SetObjects(4);
	}break;
	case GameDirector::enSpecial: {

	}break;
	default:
		break;
	}
	
	m_sky = NewGO<Sky>(0, SKY_NAME);
	return true;

}

void Game::Update()
{
	/*if (m_gameDirector->IsMainGame() == true && m_timer->IsTimerEnd() == true) {
		m_gameDirector->SetGameResult();
	}*/
}