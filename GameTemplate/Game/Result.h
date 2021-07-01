#pragma once

class FontRender;
class GameDirector;
class Score;

const int SELECT_COMMAND_NUM = 3;

class Result : public IGameObject
{
private:
	int m_selectNum = 0;
	FontRender* m_arrowFont = nullptr;
	Vector2 m_arrowFontPos = Vector2::Zero;
	FontRender* m_selectFont[SELECT_COMMAND_NUM] = { nullptr };
	FontRender* m_rankingFont[PLAYER_NUMBER] = { nullptr };
	FontRender* m_playerNameFont[PLAYER_NUMBER] = { nullptr };

	GameDirector* m_gameDirector = nullptr;
	Score* m_score = nullptr;

public:
	Result();
	~Result();
	bool Start();
	void Update();

	int GetSelectCommand() { return m_selectNum; }
};

