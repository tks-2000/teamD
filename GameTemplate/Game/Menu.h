#pragma once

class FontRender;
class GameDirector;

class Menu : public IGameObject
{
private:
	int m_playerNum = 1;
	/// @brief �v���C���[�̃t�H���g
	FontRender* m_plFont = nullptr;
	/// @brief �v���C���[�̐l���̃t�H���g
	FontRender* m_plNumFont = nullptr;

	GameDirector* m_gameDirector = nullptr;

public:
	Menu();
	~Menu();
	bool Start();
	void Update();
};

