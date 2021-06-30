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
	/// @brief �^�C�g���̈ꖇ�摜
	SpriteRender* m_titleSprite = nullptr;
	/// @brief �l���I���̃{�^���������悤�ɑ����t�H���g
	FontRender* m_font = nullptr;
	/// @brief �X�^�[�g�������悤�ɑ����t�H���g
	FontRender* m_pushStart = nullptr;
	/// @brief	�v���C���[�̐l���I���̃t�H���g
	FontRender* m_playerNumSelect[4] = { nullptr };
	/// @brief �v���C���[�̐l��
	int m_playerNum = 0;

	GameDirector* m_gameDirector = nullptr;
};

