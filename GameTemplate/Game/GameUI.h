#pragma once

class FontRender;
class GameDirector;
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
	/// @brief テスト用の数値
	//int m_testNum = 0;
	int m_playerNum = 0;

	int m_plNum[PLAYER_NUMBER] = {};

	/// @brief テスト用のフォント
	//FontRender* m_testFont;
	FontRender* m_playerFont[PLAYER_NUMBER] = { nullptr };

	/// @brief テスト用の数値表示フォント
	//FontRender* m_testNumFont;
	FontRender* m_playerNumFont[PLAYER_NUMBER] = { nullptr };

	GameDirector* m_gameDirector = nullptr;

	/// @brief ボールの速度表示用のフォント
	FontRender* m_ballSpeed = nullptr;

	/// @brief ボールの速度
	float m_ballVelocity = 0.0f;

	wchar_t* m_text;

	Ball* m_ball = nullptr;
};

