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
	/// @brief フォント
	FontRender* m_font = nullptr;

	GameDirector* m_gameDirector = nullptr;

};

