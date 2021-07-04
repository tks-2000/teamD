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
	/// @brief �^�C�g���̈ꖇ�摜
	SpriteRender* m_titleSprite = nullptr;
	/// @brief �X�^�[�g�������悤�ɑ����t�H���g
	FontRender* m_pushStart = nullptr;

	GameDirector* m_gameDirector = nullptr;

	Se* m_se = nullptr;
};

