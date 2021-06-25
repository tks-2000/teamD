#pragma once

class FontRender;
class GameDirector;
class Player;
class Ball;


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
	int m_playerNum = 0;

	int m_plNum[PLAYER_NUMBER] = {};

	/// @brief �e�X�g�p�̃t�H���g
	//FontRender* m_testFont;
	FontRender* m_playerFont[PLAYER_NUMBER] = { nullptr };

	/// @brief �e�X�g�p�̐��l�\���t�H���g
	//FontRender* m_testNumFont;
	FontRender* m_playerNumFont[PLAYER_NUMBER] = { nullptr };

	GameDirector* m_gameDirector = nullptr;

	/// @brief �{�[���̑��x�\���p�̃t�H���g
	FontRender* m_ballSpeed = nullptr;

	/// @brief �{�[���̑��x
	float m_ballVelocity = 0.0f;

	wchar_t* m_text;

	FontRender* m_GuardDurability[PLAYER_NUMBER] = { nullptr };

	float m_playerGuardDurability[PLAYER_NUMBER] = { 0.0f };

	Player* m_player[PLAYER_NUMBER] = { nullptr };
	Ball* m_ball = nullptr;
};

