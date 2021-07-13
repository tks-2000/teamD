#include "stdafx.h"
#include "GameDirector.h"

namespace {

}

GameDirector::GameDirector()
{
	m_bgm = NewGO<Bgm>(PRIORITY_VERYLOW, BGM_NAME);
	m_se = NewGO<Se>(PRIORITY_VERYLOW, SE_NAME);
	m_lighting = NewGO<Lighting>(PRIORITY_VERYLOW, LIGHTING_NAME);
	m_sceneChange = NewGO<SceneChange>(PRIORITY_VERYLOW, SCENE_CHANGE_NAME);
	m_playerNum = MIN_PLAYER_NUM;
	m_gameState = enTitle;
}

GameDirector::~GameDirector()
{
	DeleteGO(m_bgm);
	DeleteGO(m_se);
	DeleteGO(m_lighting);
}

bool GameDirector::Start()
{
	m_sceneChange->TransparencyChange(true);
	return true;
}

void GameDirector::Update()
{
	switch (m_gameState)
	{
	case enTitle: {
		if (m_title == nullptr) {
			m_title = NewGO<Title>(PRIORITY_VERYLOW, TITLE_NAME);
			m_bgm->ChangeTitleBgm();
		}
		else {
			if (g_pad[0]->IsTrigger(enButtonStart) && m_sceneChange->TransparencyChangeStart() == true) {
				m_sceneChange->TransparencyChange(false);
				m_se->PlayPressKeySe();
			}
			if (m_sceneChange->TransparencyChangeEnd() == true) {
				m_gameState = enMenu;
				DeleteGO(m_title);
				m_title = nullptr;
				m_sceneChange->TransparencyChange(true);
			}
		}
	}break;
	case enMenu: {
		if (m_menu == nullptr) {
			m_menu = NewGO<Menu>(PRIORITY_VERYLOW, MENU_NAME);
			m_bgm->ChangeMenuBgm();
			m_lighting->InitHemiSphereLight();
		}
		else {
			if (g_pad[0]->IsTrigger(enButtonStart) && m_playerNum > 0 && m_sceneChange->TransparencyChangeStart() == true) {
				m_sceneChange->TransparencyChange(false);
				m_se->PlayPressKeySe();
				m_menu->End();
			}
			if (m_sceneChange->TransparencyChangeEnd() == true) {
				m_gameState = enMainGame;
				DeleteGO(m_menu);
				m_menu = nullptr;
				m_sceneChange->TransparencyChange(true);
				m_lighting->ResetSpotLight();
				m_lighting->InitDirectionLight();
			}
		}
	}break;
	case enMainGame: {
		if (m_game == nullptr && m_timer == nullptr) {
			m_game = NewGO<Game>(PRIORITY_VERYLOW, GAME_NAME);
			m_timer = NewGO<Timer>(PRIORITY_VERYLOW, TIMER_NAME);
		}
		else {
			float changeRate = (TIME_LIMIT - m_timer->GetTimer()) / TIME_LIMIT;

			if (changeRate > FLOAT_1) {
				changeRate = FLOAT_1;
			}

			changeRate *= changeRate;

			Vector3 hemLigSkyColor = Vector3::Zero;
			hemLigSkyColor.Lerp(changeRate,HEMISPHERE_LIGHT_SKYCOLOR_START, HEMISPHERE_LIGHT_SKYCOLOR_END);
			m_lighting->SetHemiSphereLifhtSkyColor(hemLigSkyColor);

			if (m_timer->IsTimerEnd() == true) {
				m_gameState = enResult;
			}
		}
	}break;
	case enResult: {
		if (m_result == nullptr) {
			m_result = NewGO<Result>(PRIORITY_VERYLOW, RESULT_NAME);
			m_bgm->ChangeResultBgm();
		}
		else {
			if (m_result->IsMoveEnd() == true) {
				if (g_pad[0]->IsTrigger(enButtonA) && m_sceneChange->TransparencyChangeStart() == true) {
					m_sceneChange->TransparencyChange(false);
					m_se->PlayPressKeySe();
				}
			}
			if (m_sceneChange->TransparencyChangeEnd() == true) {
				m_gameState = enEnd;
			}
		}
	}break;
	case enEnd: {
		switch (m_result->GetSelectCommand())
		{
		case 0: {
			m_gameState = enMainGame;
		}break;
		case 1: {
			m_gameState = enMenu;
		}break;
		case 2: {
			m_gameState = enTitle;
		}break;
		default:
			break;
		}
		DeleteGO(m_game);
		m_game = nullptr;
		DeleteGO(m_result);
		m_result = nullptr;
		DeleteGO(m_timer);
		m_timer = nullptr;
		m_lighting->ResetPointLight();
		m_sceneChange->TransparencyChange(true);
	}break;
	}
}

bool GameDirector::IsMainGame()
{
	if (m_gameState == enMainGame) {
		return true;
	}
	else {
		return false;
	}
}

bool GameDirector::IsResult()
{
	if (m_gameState == enResult) {
		return true;
	}
	else {
		return false;
	}
}