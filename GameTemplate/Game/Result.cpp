#include "stdafx.h"
#include "Result.h"

namespace{
	const wchar_t* PLAYER[MAX_PLAYER_NUM] = { L"Player1",L"Player2" ,L"Player3" ,L"Player4" };
	const Vector2 PLAYER_FONT_POS[MAX_PLAYER_NUM] = { {-100.0f,200.0f},{-100.0f,100.0f},{-100.0f,0.0f},{-100.0f,-100.0f} };
	const Vector2 RANKING_FONT_POS[MAX_PLAYER_NUM] = { {-150.0f,200.0f},{-150.0f,100.0f},{-150.0f,0.0f},{-150.0f,-100.0f} };
}

Result::Result()
{
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
}

Result::~Result()
{
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		DeleteGO(m_rankingFont[plNum]);
		DeleteGO(m_playerNameFont[plNum]);
	}
}

bool Result::Start()
{

	return true;
}

void Result::Update()
{

}