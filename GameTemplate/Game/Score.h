#pragma once

class GameDirector;

class Score : public IGameObject
{
private:
	int m_score[PLAYER_NUMBER] = { 0 };

	GameDirector* m_gameDirector = nullptr;

public:
	Score();
	~Score();
	bool Start();
	void Update();

	void AddScore(int plNum);
	void DebuctionScore(int plNum);

	int GetScore(int plNum) { return m_score[plNum]; }
};

