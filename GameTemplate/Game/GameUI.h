#pragma once

class FontRender;

const int PLAYER_NUMBER = 4;

class GameUI : public IGameObject
{
public:
	GameUI();
	~GameUI();
	bool Start();
	void Update();

	void AddScore(int num, int score);

private:
	/// @brief �e�X�g�p�̐��l
	//int m_testNum = 0;
	int m_plNum[PLAYER_NUMBER] = {};

	/// @brief �e�X�g�p�̃t�H���g
	//FontRender* m_testFont;
	FontRender* m_playerFont;

	/// @brief �e�X�g�p�̐��l�\���t�H���g
	//FontRender* m_testNumFont;
	FontRender* m_playerNumFont[PLAYER_NUMBER];
};

