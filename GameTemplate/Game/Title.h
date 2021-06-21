#pragma once

class SpriteRender;
class FontRender;

class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();

private:
	/// @brief �^�C�g���̈ꖇ�摜
	SpriteRender* m_titleSprite = nullptr;
	/// @brief �t�H���g
	FontRender* m_font = nullptr;

};

