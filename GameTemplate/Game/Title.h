#pragma once

class SpriteRender;
class FontRender;
class GameDirector;

class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();

private:
	/// @brief タイトルの一枚画像
	SpriteRender* m_titleSprite = nullptr;
	/// @brief 人数選択のボタンを押すように促すフォント
	FontRender* m_font = nullptr;
	/// @brief スタートを押すように促すフォント
	FontRender* m_pushStart = nullptr;
	/// @brief	プレイヤーの人数選択のフォント
	FontRender* m_playerNumSelect[4] = { nullptr };
	/// @brief プレイヤーの人数
	int m_playerNum = 0;

	GameDirector* m_gameDirector = nullptr;

};

