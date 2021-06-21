#include "stdafx.h"
#include "Title.h"

Title::Title()
{
	m_titleSprite = NewGO<SpriteRender>(1);
	m_titleSprite->Init("Assets/sprite/title.dds", 1280, 720);
}

Title::~Title()
{
	DeleteGO(m_titleSprite);
}

bool Title::Start()
{
	
	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(this);
		NewGO<Game>(0, "Game");
	}
}