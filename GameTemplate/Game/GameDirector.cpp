#include "stdafx.h"
#include "GameDirector.h"

namespace {
	const Vector3 NORMAL_MENU_COLOR = { 0.3f,0.3f,0.3f };
	const Vector3 SPECIAL_MENU_COLOR = { -0.3f,-0.7f,-0.3f };
	const Vector3 DIR_LIG_DIR = { 0.0f,1.0f,0.0f };
	const Vector3 DIR_LIG_START_COLOR = { 0.5f,0.5f,0.5f };
	const Vector3 DIR_LIG_END_COLOR = { 0.1f,0.1f,0.1f };
	const float DIR_LIG_FLICKERING_SPEED = 0.25f;
}

GameDirector::GameDirector()
{
	m_bgm = NewGO<Bgm>(PRIORITY_VERYLOW, BGM_NAME);
	m_se = NewGO<Se>(PRIORITY_VERYLOW, SE_NAME);
	m_lighting = NewGO<Lighting>(PRIORITY_VERYLOW, LIGHTING_NAME);
	m_sceneChange = NewGO<SceneChange>(PRIORITY_VERYLOW, SCENE_CHANGE_NAME);
	m_playerNum = MIN_PLAYER_NUM;
	m_gameState = enTitle;
	m_gameMode = enNormal;
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

void GameDirector::CangeHemLigt()
{
	if (m_timer->GetTimer() > m_timer->GetHalfLimit()) {
		float changeRate = (m_timer->GetHalfLimit() - (m_timer->GetTimer() - m_timer->GetHalfLimit())) / m_timer->GetHalfLimit();

		if (changeRate > FLOAT_1) {
			changeRate = FLOAT_1;
		}

		changeRate *= changeRate;

		Vector3 hemLigSkyColor = Vector3::Zero;
		hemLigSkyColor.Lerp(changeRate, m_hemLigSkyColorStart,m_hemLigSkyColorHalf);
		Vector3 hemLigGroundColor = Vector3::Zero;
		hemLigGroundColor.Lerp(changeRate, m_hemLigGroundColorStart, m_hemLigGroundColorHalf);
		m_lighting->SetHemiSphereLifhtSkyColor(hemLigSkyColor);
		m_lighting->SetHemiSphereLifhtGroundColor(hemLigGroundColor);
	}
	else {
		float changeRate = (m_timer->GetHalfLimit() - m_timer->GetTimer()) / m_timer->GetHalfLimit();
		
		if (changeRate > FLOAT_1) {
			changeRate = FLOAT_1;
		}

		changeRate *= changeRate;

		Vector3 hemLigSkyColor = Vector3::Zero;
		hemLigSkyColor.Lerp(changeRate, m_hemLigSkyColorHalf, m_hemLigSkyColorEnd);
		Vector3 hemLigGroundColor = Vector3::Zero;
		hemLigGroundColor.Lerp(changeRate, m_hemLigGroundColorHalf, m_hemLigGroundColorEnd);
		m_lighting->SetHemiSphereLifhtSkyColor(hemLigSkyColor);
		m_lighting->SetHemiSphereLifhtGroundColor(hemLigGroundColor);
	}
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
			switch (m_gameMode)
			{
			case enNormal: {
				m_hemLigSkyColorStart = HEMISPHERE_LIGHT_SKYCOLOR_START;
				m_hemLigSkyColorHalf = HEMISPHERE_LIGHT_SKYCOLOR_HALF;
				m_hemLigSkyColorEnd = HEMISPHERE_LIGHT_SKYCOLOR_END;
				m_hemLigGroundColorStart = HEMISPHERE_LIGHT_GROUNDCOLOR_START;
				m_hemLigGroundColorHalf = HEMISPHERE_LIGHT_GROUNDCOLOR_HALF;
				m_hemLigGroundColorEnd = HEMISPHERE_LIGHT_GROUNDCOLOR_END;
				m_lighting->SetHemiSphereLifhtSkyColor(NORMAL_MENU_COLOR);
				m_lighting->SetHemiSphereLifhtGroundColor(NORMAL_MENU_COLOR);
				m_bgm->ChangeNormalBgm();
			}break;
			case enSpecial: {
				m_hemLigSkyColorStart = HEMISPHERE_LIGHT_SKYCOLOR_SP_START;
				m_hemLigSkyColorHalf = HEMISPHERE_LIGHT_SKYCOLOR_SP_HALF;
				m_hemLigSkyColorEnd = HEMISPHERE_LIGHT_SKYCOLOR_SP_END;
				m_hemLigGroundColorStart = HEMISPHERE_LIGHT_GROUNDCOLOR_SP_START;
				m_hemLigGroundColorHalf = HEMISPHERE_LIGHT_GROUNDCOLOR_SP_HALF;
				m_hemLigGroundColorEnd = HEMISPHERE_LIGHT_GROUNDCOLOR_SP_END;
				m_lighting->SetHemiSphereLifhtSkyColor(SPECIAL_MENU_COLOR);
				m_lighting->SetHemiSphereLifhtGroundColor(SPECIAL_MENU_COLOR);
				m_bgm->ChangeSpecialBgm();
			}break;
			default:
				break;
			}
			if (g_pad[0]->IsTrigger(enButtonA) && m_playerNum > 0 && m_sceneChange->TransparencyChangeStart() == true) {
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
				switch (m_gameMode)
				{
				case enNormal: {
					m_lighting->InitDirectionLight();
				}break;
				case enSpecial: {
					m_lighting->RotationStopDirectionLight();
					m_lighting->SetDirectionLightDirection(g_camera3D->GetPosition());
					m_lighting->SetDirectionLightFlickering(DIR_LIG_START_COLOR, DIR_LIG_END_COLOR, DIR_LIG_FLICKERING_SPEED);
				}break;
				default:
					break;
				}
			}
		}
	}break;
	case enMainGame: {
		if (m_game == nullptr && m_timer == nullptr) {
			m_game = NewGO<Game>(PRIORITY_VERYLOW, GAME_NAME);
			m_timer = NewGO<Timer>(PRIORITY_VERYLOW, TIMER_NAME);
		}
		else {
			
			CangeHemLigt();
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
			//ゲームシーン中に発生している全てのエフェクトを停止
			EffectEngine::GetInstance()->AllStop();
		}break;
		case 1: {
			m_gameState = enMenu;
			EffectEngine::GetInstance()->AllStop();
		}break;
		case 2: {
			m_gameState = enTitle;
			EffectEngine::GetInstance()->AllStop();
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
		m_lighting->InitDirectionLight();
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