#include "stdafx.h"
#include "Game.h"
#include "SkinModelRender.h"

Game::Game()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/unityChan.tkm");
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
	
}