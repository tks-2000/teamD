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
	SpriteRender* m_titleSprite = nullptr;

};

