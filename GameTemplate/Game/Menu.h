#pragma once

class FontRender;
class GameDirector;

class Menu : public IGameObject
{
private:
	int m_playerNum = 1;
	/// @brief プレイヤーのフォント
	FontRender* m_plFont = nullptr;
	/// @brief プレイヤーの人数のフォント
	FontRender* m_plNumFont = nullptr;

	GameDirector* m_gameDirector = nullptr;

public:
	Menu();
	~Menu();
	bool Start();
	void Update();
};

