#include "stdafx.h"
#include "Title.h"

namespace {
	const wchar_t* PLAYER_SELECT_TEXT[MAX_PLAYER_NUM] = { L"1P PLAY" ,L"2P PLAY" ,L"3P PLAY" ,L"4P PLAY" };
	const wchar_t* PLAYER_START = L"PUSH START BUTTON";
	const Vector2 PLAYER_SELECT_POS[MAX_PLAYER_NUM] = { { 400.0f,0.0f },{400.0f,-100.0f},{400.0f,-200.0f},{400.0f,-300.0f} };
}

Title::Title()
{
	m_titleSprite = NewGO<SpriteRender>(0);
	m_titleSprite->Init("Assets/sprite/title.dds", 1280, 720);
	m_pushStart = NewGO<FontRender>(1);
	m_pushStart->SetText(PLAYER_START);
	m_pushStart->SetColor({ 0.0f,0.0f,0.0f,0.0f });
	m_pushStart->SetPosition({ -175.0f,-275.0f });
}

Title::~Title()
{
	DeleteGO(m_titleSprite);
	DeleteGO(m_pushStart);
}

bool Title::Start()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	return true;
}

void Title::Update()
{
	if (m_pushStart->IsTransparent() == true) {
		m_pushStart->FadeIn(0.01f);
	}
	if (m_pushStart->IsOpacity() == true) {
		m_pushStart->FadeOut(0.01f);
	}


	/// @brief スタートボタンでメニューに進む
	if (g_pad[0]->IsTrigger(enButtonStart)) {
		m_gameDirector->SetMenu();
		m_gameDirector->TitleEnd();
	}
}