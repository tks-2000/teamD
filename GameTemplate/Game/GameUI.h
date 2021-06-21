#pragma once

class FontRender;

class GameUI : public IGameObject
{
public:
	GameUI();
	~GameUI();
	bool Start();
	void Update();

private:
	/// @brief テスト用の数値
	int m_testNum = 0;
	/// @brief テスト用のフォント
	FontRender* m_testFont;
	/// @brief テスト用の数値表示フォント
	FontRender* m_testNumFont;
};

