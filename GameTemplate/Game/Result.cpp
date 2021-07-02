#include "stdafx.h"
#include "Result.h"

namespace{
	const wchar_t* PLAYER[MAX_PLAYER_NUM] = { L"Player1",L"Player2" ,L"Player3" ,L"Player4" };
	const wchar_t* SELECT_COMMAND_FONT[SELECT_COMMAND_NUM] = { L"Retry",L"PlayerSelect",L"Title" };
	const Vector2 PLAYER_FONT_POS[MAX_PLAYER_NUM] = { {-100.0f,200.0f},{-100.0f,100.0f},{-100.0f,0.0f},{-100.0f,-100.0f} };
	const Vector2 RANKING_FONT_POS[MAX_PLAYER_NUM] = { {-150.0f,200.0f},{-150.0f,100.0f},{-150.0f,0.0f},{-150.0f,-100.0f} };
	const Vector2 SELECT_FONT_POS[SELECT_COMMAND_NUM] = { {300.0f,0.0f},{300.0f,-100.0f} ,{300.0f,-200.0f} };
	const int MAX_SELECT_NUM = 2;
	const int MIN_SELECT_NUM = 0;
}

Result::Result()
{
	m_selectNum = 0;
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_score = FindGO<Score>(SCORE_NAME);
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_rankingFont[plNum] = NewGO<FontRender>(3);
		std::wstring rankingNum;
		rankingNum = std::to_wstring(m_score->GetRanking(plNum));
		m_rankingFont[plNum]->SetPosition(RANKING_FONT_POS[plNum]);
		m_rankingFont[plNum]->SetText(rankingNum.c_str());
		m_playerNameFont[plNum] = NewGO<FontRender>(3);
		m_playerNameFont[plNum]->SetPosition(PLAYER_FONT_POS[plNum]);
		m_playerNameFont[plNum]->SetText(PLAYER[plNum]);
		
	}
	for (int selectNum = 0; selectNum < SELECT_COMMAND_NUM; selectNum++) {
		m_selectFont[selectNum] = NewGO<FontRender>(3);
		m_selectFont[selectNum]->SetPosition(SELECT_FONT_POS[selectNum]);
		m_selectFont[selectNum]->SetText(SELECT_COMMAND_FONT[selectNum]);
	}
	m_arrowFont = NewGO<FontRender>(3);
	m_arrowFont->SetText(L"@");
}

Result::~Result()
{
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		DeleteGO(m_rankingFont[plNum]);
		DeleteGO(m_playerNameFont[plNum]);
	}
	for (int selectNum = 0; selectNum < SELECT_COMMAND_NUM; selectNum++) {
		DeleteGO(m_selectFont[selectNum]);
	}
	DeleteGO(m_arrowFont);
}

bool Result::Start()
{
	return true;
}

void Result::Update()
{
	if (g_pad[0]->IsTrigger(enButtonDown)) {
		m_selectNum++;
		if (m_selectNum > MAX_SELECT_NUM) {
			m_selectNum = MIN_SELECT_NUM;
		}
	}
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		m_selectNum--;
		if (m_selectNum < MIN_SELECT_NUM) {
			m_selectNum = MAX_SELECT_NUM;
		}
	}
	Vector2 arrowPos = SELECT_FONT_POS[m_selectNum];
	arrowPos.x -= 100.0f;
	m_arrowFontPos = arrowPos;
	m_arrowFont->SetPosition(m_arrowFontPos);
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_gameDirector->SetEnd();
	}
}