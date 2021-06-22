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
	/// @brief テスト用の数値
	//int m_testNum = 0;
	int m_plNum[PLAYER_NUMBER] = {};

	/// @brief テスト用のフォント
	//FontRender* m_testFont;
	FontRender* m_playerFont;

	/// @brief テスト用の数値表示フォント
	//FontRender* m_testNumFont;
	FontRender* m_playerNumFont[PLAYER_NUMBER];
};

