#include "stdafx.h"
#include "GameDirector.h"

GameDirector::GameDirector()
{
	m_playerNum = MIN_PLAYER_NUM;
	m_gameState = enTitle;
}

GameDirector::~GameDirector()
{

}

bool GameDirector::Start()
{

	return true;
}



void GameDirector::Update()
{
	switch (m_gameState)
	{
	case enTitle: {
		if (m_title == nullptr) {
			m_title = NewGO<Title>(0, TITLE_NAME);
		}
	}break;
	case enMenu: {
		if (m_menu == nullptr) {
			m_menu = NewGO<Menu>(0, MENU_NAME);
		}
	}break;
	case enMainGame: {
		if (m_game == nullptr) {
			m_game = NewGO<Game>(0, GAME_NAME);
		}
	}break;
	case enResult: {
		if (m_result == nullptr) {
			m_result = NewGO<Result>(0, RESULT_NAME);
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