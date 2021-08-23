#pragma once

class FontRender;
class GameDirector;
class Result;

class Score : public IGameObject
{
private:
	/// @brief プレイヤーのスコア
	int m_score[PLAYER_NUMBER] = { 0 };
	/// @brief プレイヤーの順位
	int m_ranking[PLAYER_NUMBER] = { 0 };

	FontRender* m_rankingFont[PLAYER_NUMBER] = { nullptr };
	GameDirector* m_gameDirector = nullptr;
	bool m_scoreCountStop = false;

public:
	Score();
	~Score();
	bool Start();
	void Update();

	void AddScore(int plNum);
	void AddScore200(int plNum);
	void AddScore500(int plNum);
	void DeclineScore(int plNum);
	void HalfScore(int plNum);
	void RankingSurvey();
	void ScoreCountStop() { m_scoreCountStop = true; }

	int GetScore(int plNum) { return m_score[plNum]; }
	int GetRanking(int plNum) { return m_ranking[plNum]; }
};

