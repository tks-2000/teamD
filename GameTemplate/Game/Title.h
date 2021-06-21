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
	/// @brief �^�C�g���̈ꖇ�摜
	SpriteRender* m_titleSprite = nullptr;

};

