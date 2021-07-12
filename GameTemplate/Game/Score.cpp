#include "stdafx.h"
#include "Score.h"

namespace {
	const int SCORE_ZERO = 0;
	const int SCORE_ADD_POINTS = 100;
	const int SCORE_DEBUCTION_RATE = 2;
	//const Vector2 RANKING_FONT_POS[MAX_PLAYER_NUM] = { { -600.0f,150.0f },{ 600.0f,150.0f },{ -600.0f,-150.0f },{ 600.0f,-150.0f } };
}

Score::Score()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_score[plNum] = SCORE_ZERO;
		//m_rankingFont[plNum] = NewGO<FontRender>(4);
		//m_rankingFont[plNum]->SetPosition(RANKING_FONT_POS[plNum]);
	}
}

Score::~Score()
{
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		DeleteGO(m_rankingFont[plNum]);
	}
}

bool Score::Start()
{

	return true;
}

void Score::AddScore(int plNum)
{
	m_score[plNum] += SCORE_ADD_POINTS;
}

void Score::DebuctionScore(int plNum)
{
	m_score[plNum] /= SCORE_DEBUCTION_RATE;
}

void Score::RankingSurvey()
{
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		int rank = 1;
		for (int plNum2 = 0; plNum2 <m_gameDirector->GetPlayerNum(); plNum2++) {
			if (plNum == plNum2) {
				continue;
			}
			if (m_score[plNum] < m_score[plNum2]) {
				rank++;
			}
		}
		m_ranking[plNum] = rank;
		//std::wstring conv = std::to_wstring(m_ranking[plNum]);
		//m_rankingFont[plNum]->SetText(conv.c_str());
	}
}

void Score::Update()
{
	RankingSurvey();
}