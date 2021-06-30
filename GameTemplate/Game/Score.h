#pragma once

class FontRender;
class GameDirector;

class Score : public IGameObject
{
private:
	/// @brief �v���C���[�̃X�R�A
	int m_score[PLAYER_NUMBER] = { 0 };
	/// @brief �v���C���[�̏���
	int m_ranking[PLAYER_NUMBER] = { 0 };

	FontRender* m_rankingFont[PLAYER_NUMBER] = { nullptr };
	GameDirector* m_gameDirector = nullptr;

public:
	Score();
	~Score();
	bool Start();
	void Update();

	void AddScore(int plNum);
	void DebuctionScore(int plNum);
	void RankingSurvey();

	int GetScore(int plNum) { return m_score[plNum]; }
	int GetRanking(int plNum) { return m_ranking[plNum]; }
};

