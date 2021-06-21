#pragma once

class SpriteRender;

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

};

