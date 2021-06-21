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
	/// @brief ƒ^ƒCƒgƒ‹‚Ìˆê–‡‰æ‘œ
	SpriteRender* m_titleSprite = nullptr;

};

