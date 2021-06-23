#pragma once

class FontRender;
class Ball;

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

	/// @brief �{�[���̑��x�\���p�̃t�H���g
	FontRender* m_ballSpeed = nullptr;

	/// @brief �{�[���̑��x
	float m_ballVelocity = 0.0f;

	wchar_t* m_text;

	Ball* m_ball = nullptr;
};

