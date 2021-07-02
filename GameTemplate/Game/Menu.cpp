#include "stdafx.h"
#include "Menu.h"

namespace {
	/// @brief Playerのフォント位置
	const Vector2 PLAYER_FONT_POS = { 100.0f,0.0f };
	/// @brief 人数のフォント位置
	const Vector2 PLAYER_NUM_FONT_POS = { 0.0f,0.0f };
}

Menu::Menu()
{
	m_plNumFont = NewGO<FontRender>(2);
	m_plNumFont->SetPosition(PLAYER_NUM_FONT_POS);
	m_plFont = NewGO<FontRender>(2);
	m_plFont->SetPosition(PLAYER_FONT_POS);
	m_plFont->SetText(L"Player");
}

Menu::~Menu()
{
	DeleteGO(m_plNumFont);
	DeleteGO(m_plFont);
}

bool Menu::Start()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	return true;
}

void Menu::Update()
{
	/// @brief ボタン上下で人数選択
	if (g_pad[0]->IsTrigger(enButtonDown)) {
		m_playerNum++;
		if (m_playerNum > MAX_PLAYER_NUM) {
			m_playerNum = MIN_PLAYER_NUM;
		}
	}
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		m_playerNum--;
		if (m_playerNum < MIN_PLAYER_NUM) {
			m_playerNum = MAX_PLAYER_NUM;
		}
	}

	/// @brief スタートでゲーム開始
	if (g_pad[0]->IsTrigger(enButtonStart)) {
		m_gameDirector->SetPlayerNum(m_playerNum);
		m_gameDirector->SetGameStart();
		m_gameDirector->MenuEnd();
	}

	std::wstring plNum;
	plNum = std::to_wstring(m_playerNum);
	m_plNumFont->SetText(plNum.c_str());
}