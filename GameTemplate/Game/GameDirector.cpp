#include "stdafx.h"
#include "GameDirector.h"

GameDirector::GameDirector()
{

}

GameDirector::~GameDirector()
{

}

bool GameDirector::Start()
{

	return true;
}

void GameDirector::Title()
{
	if (g_pad[0]->IsTrigger(enButtonB)) {
		m_playerNum = 1;
	}
	if (g_pad[0]->IsTrigger(enButtonX)) {
		m_playerNum = 2;
	}
	if (g_pad[0]->IsTrigger(enButtonY)) {
		m_playerNum = 3;
	}
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_playerNum = 4;
	}
}

void GameDirector::Result()
{
	
}

void GameDirector::Update()
{
	switch (m_gameState)
	{
	case enTitle: {
		Title();
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