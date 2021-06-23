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
	m_font = NewGO<FontRender>(1);
	m_font->SetText(L"PUSH A B X Y BUTTON");
	m_font->SetPivot({ 0.5f,0.5f });
	m_font->SetPosition({ -200.0f,-225.0f });
	m_font->SetColor({ 0.0f,0.0f,0.0f,1.0f });
	m_pushStart = NewGO<FontRender>(1);
	m_pushStart->SetText(PLAYER_START);
	m_pushStart->SetColor({ 0.0f,0.0f,0.0f,0.0f });
	m_pushStart->SetPosition({ -175.0f,-275.0f });

	for (int fontNum = 0; fontNum < MAX_PLAYER_NUM; fontNum++) {
		m_playerNumSelect[fontNum] = NewGO<FontRender>(1);
		m_playerNumSelect[fontNum]->SetText(PLAYER_SELECT_TEXT[fontNum]);
		m_playerNumSelect[fontNum]->SetPosition(PLAYER_SELECT_POS[fontNum]);
		m_playerNumSelect[fontNum]->SetColor({ 0.0f,0.0f,0.0f,0.1f });
	}
}

Title::~Title()
{
	DeleteGO(m_titleSprite);
	DeleteGO(m_font);
	for (int fontNum = 0; fontNum < MAX_PLAYER_NUM; fontNum++) {
		DeleteGO(m_playerNumSelect[fontNum]);
	}
	DeleteGO(m_pushStart);
}

bool Title::Start()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	return true;
}

void Title::Update()
{
	
	
	m_playerNum = m_gameDirector->GetPlayerNum();

	if (m_playerNum != 0) {
		if (m_pushStart->IsTransparent() == true) {
			m_pushStart->FadeIn(0.01f);
		}
		if (m_pushStart->IsOpacity() == true) {
			m_pushStart->FadeOut(0.01f);
		}
		for (int fontNum = 0; fontNum < MAX_PLAYER_NUM; fontNum++) {
			if (fontNum == m_playerNum - 1) {
				m_playerNumSelect[fontNum]->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
			}
			else {
				m_playerNumSelect[fontNum]->SetColor({ 0.0f, 0.0f, 0.0f, 0.1f });
			}
		}

		/// @brief スタートボタンでゲームスタート
		if (g_pad[0]->IsTrigger(enButtonStart)) {
			DeleteGO(this);
			NewGO<Game>(0, "Game");
			m_gameDirector->GameStart();
		}
	}
}