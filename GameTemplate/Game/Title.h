#pragma once

class SpriteRender;
class FontRender;
class GameDirector;
class Se;

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
	/// @brief スタートを押すように促すフォント
	FontRender* m_pushStart = nullptr;

	GameDirector* m_gameDirector = nullptr;

	Se* m_se = nullptr;
};

