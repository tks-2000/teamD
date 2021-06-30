#include "stdafx.h"
#include "Game.h"
#include "Title.h"

Game::Game()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_playerNum = m_gameDirector->GetPlayerNum();
	//m_playerNum = 4;
	m_timer = NewGO<Timer>(0, TIMER_NAME);
	m_lighting = NewGO<Lighting>(0,LIGHTING_NAME);
	for (int i = 0; i < m_playerNum; i++) {
		m_player[i] = NewGO<Player>(0,PLAYER_NAME[i]);
	}
	m_playerEffect = NewGO<PlayerEffect>(0, PLAYER_EFFECT_NAME);
	m_gameCamera = NewGO<GameCamera>(0,GAME_CAMERA_NAME);
	m_backGround = NewGO<BackGround>(0,BACK_GROUND_NAME);
	m_ball = NewGO<Ball>(0, BALL_NAME);
	m_objects = NewGO<Objects>(0,OBJECTS_NAME);
	m_ui = NewGO<GameUI>(0,GAME_UI_NAME);
	m_score = NewGO<Score>(0, SCORE_NAME);
	m_sky = NewGO<Sky>(0, "Sky");
	//m_box = NewGO<Box>(0, BOX_NAME);
}

Game::~Game()
{
	//ゲームシーン中に発生している全てのエフェクトを停止
	EffectEngine::GetInstance()->AllStop();
	
	DeleteGO(m_timer);
	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);
	DeleteGO(m_ball);
	DeleteGO(m_ui);
	DeleteGO(m_score);
	DeleteGO(m_objects);
	DeleteGO(m_sky);
	
	for (int i = 0; i < m_playerNum; i++) {
		DeleteGO(m_player[i]);
	}
	DeleteGO(m_playerEffect);
	DeleteGO(m_lighting);
	if (m_gameDirector->IsMainGame() == false) {
		DeleteGO(m_result);
	}

	NewGO<Title>(0, TITLE_NAME);
}

bool Game::Start()
{
	m_lighting->GetLight();
	for (int i = 0; i < m_playerNum; i++) {
		m_player[i]->SetPlayerNumber(i);
	}
	m_objects->SetObjects(4);

	return true;

}

void Game::Update()
{
	if (g_pad[0]->IsTrigger(enButtonSelect)) {
		DeleteGO(this);
		m_gameDirector->SetTitle();
	}
	
	if (m_gameDirector->IsMainGame() == true && m_timer->IsTimerEnd() == true) {
		m_result = NewGO<Result>(0, RESULT_NAME);
		m_gameDirector->SetGameResult();
	}

	if (m_gameDirector->IsResult() == true) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			DeleteGO(this);
			m_gameDirector->SetTitle();
		}
	}
}