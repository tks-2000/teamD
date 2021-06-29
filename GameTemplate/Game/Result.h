#pragma once

class FontRender;
class GameDirector;
class Score;

class Result : public IGameObject
{
private:
	FontRender* m_rankingFont[PLAYER_NUMBER] = { nullptr };
	FontRender* m_playerNameFont[PLAYER_NUMBER] = { nullptr };

	GameDirector* m_gameDirector = nullptr;
	Score* m_score = nullptr;

public:
	Result();
	~Result();
	bool Start();
	void Update();
};

