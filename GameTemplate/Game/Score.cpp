#include "stdafx.h"
#include "Score.h"

namespace {
	const int SCORE_ZERO = 0;
	const int SCORE_ADD_POINTS = 100;
	const int SCORE_DEBUCTION_RATE = 2;
}

Score::Score()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_score[plNum] = SCORE_ZERO;
	}
}

Score::~Score()
{

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

void Score::Update()
{

}