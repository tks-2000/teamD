#include "stdafx.h"
#include "Result.h"

namespace{
	const wchar_t* PLAYER[MAX_PLAYER_NUM] = { L"Player1",L"Player2" ,L"Player3" ,L"Player4" };
	const wchar_t* SELECT_COMMAND_FONT[SELECT_COMMAND_NUM] = { L"Retry",L"PlayerSelect",L"Title" };
	const Vector2 PLAYER_FONT_START_POS[MAX_PLAYER_NUM] = { {700.0f,200.0f},{700.0f,100.0f},{700.0f,0.0f},{700.0f,-100.0f} };
	const Vector2 PLAYER_FONT_POS[MAX_PLAYER_NUM] = { {-200.0f,200.0f},{-200.0f,100.0f},{-200.0f,0.0f},{-200.0f,-100.0f} };
	const Vector2 RANKING_FONT_POS[MAX_PLAYER_NUM] = { {-250.0f,200.0f},{-250.0f,100.0f},{-250.0f,0.0f},{-250.0f,-100.0f} };
	const Vector2 SELECT_FONT_POS[SELECT_COMMAND_NUM] = { {200.0f,0.0f},{200.0f,-100.0f} ,{200.0f,-200.0f} };
	const int MAX_SELECT_NUM = 2;
	const int MIN_SELECT_NUM = 0;
	const Vector4 PLAYER_FONT_COLOR[MAX_PLAYER_NUM] = { {1.0f,0.0f,0.0f,1.0f},{0.0f,0.0f,1.0f,1.0f},{1.0f,1.0f,0.0f,1.0f},{0.0f,1.0f,0.0f,1.0f} };
}

Result::Result()
{
	m_selectNum = 0;
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_score = FindGO<Score>(SCORE_NAME);
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_playerFontSet[plNum] = false;
		m_moveFlag[plNum] = false;
	}
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_rankingFont[plNum] = NewGO<FontRender>(3);
		std::wstring rankingNum;
		rankingNum = std::to_wstring(m_score->GetRanking(plNum));

		m_rankingFont[plNum]->SetText(rankingNum.c_str());
		m_playerNameFont[plNum] = NewGO<FontRender>(PRIORITY_VERYHIGH);

		int incremental = -1;
		while (m_playerFontSet[m_score->GetRanking(plNum) + incremental] == true)
		{
			incremental++;
		}
		m_plFontPos[plNum] = PLAYER_FONT_START_POS[m_score->GetRanking(plNum) + incremental];
		m_playerNameFont[plNum]->SetPosition(m_plFontPos[plNum]);
		m_rankingFont[plNum]->SetPosition(RANKING_FONT_POS[m_score->GetRanking(plNum) + incremental]);
		m_movePos[plNum].x = PLAYER_FONT_POS[m_score->GetRanking(plNum) + incremental].x;
		m_movePos[plNum].y = PLAYER_FONT_POS[m_score->GetRanking(plNum) + incremental].y;
		m_playerFontSet[m_score->GetRanking(plNum) + incremental] = true;
		m_moveOrder[plNum] = m_score->GetRanking(plNum) + incremental;

		//m_playerNameFont[plNum]->SetPosition(PLAYER_FONT_POS[plNum]);
		m_playerNameFont[plNum]->SetText(PLAYER[plNum]);
		m_playerNameFont[plNum]->SetColor(PLAYER_FONT_COLOR[plNum]);
	}
	
	m_moveEndFlag = false;
	m_decrease = 1;
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		if (m_moveOrder[plNum] == m_gameDirector->GetPlayerNum() - m_decrease) {
			m_moveFlag[plNum] = true;
			
			break;
		}
	}
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

void Result::PlayerFontMove(int num)
{
	if (m_plFontPos[num].x > m_movePos[num].x) {
		m_plFontPos[num].x -= 10.0f;
	}
	else {
		if (m_moveOrder[num] != MIN_PLAYER_NUM - m_decrease) {
			for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
				if (m_moveOrder[plNum] == m_moveOrder[num] - m_decrease) {
					m_moveFlag[plNum] = true;
					break;
				}
			}
		}
		else {
			SelectCommandNewGO();
			m_moveEndFlag = true;
		}
	}
}

void Result::SelectCommandNewGO()
{
	for (int selectNum = 0; selectNum < SELECT_COMMAND_NUM; selectNum++) {
		m_selectFont[selectNum] = NewGO<FontRender>(5);
		m_selectFont[selectNum]->SetPosition(SELECT_FONT_POS[selectNum]);
		m_selectFont[selectNum]->SetText(SELECT_COMMAND_FONT[selectNum]);
	}
	m_arrowFont = NewGO<FontRender>(5);
	m_arrowFont->SetText(L"->");
	m_arrowFont->SetColor({ 0.0f,1.0f,1.0f,1.0f });
}

void Result::Update()
{
	if (m_moveEndFlag == false) {
		for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
			if (m_moveFlag[plNum] == true) {
				PlayerFontMove(plNum);
			}
			m_playerNameFont[plNum]->SetPosition(m_plFontPos[plNum]);
		}
	}
	else {
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
		for (int selectNum = 0; selectNum < SELECT_COMMAND_NUM; selectNum++) {
			if (selectNum == m_selectNum) {
				m_selectFont[selectNum]->SetColor({ 0.0f,1.0f,1.0f,1.0f });
			}
			else {
				m_selectFont[selectNum]->SetColor({ 0.0f,0.0f,0.0f,1.0f });
			}
		}
		m_arrowFont->SetPosition(m_arrowFontPos);
	}
}