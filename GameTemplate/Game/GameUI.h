#pragma once

class FontRender;

class GameUI : public IGameObject
{
public:
	GameUI();
	~GameUI();
	bool Start();
	void Update();

private:
	/// @brief �e�X�g�p�̐��l
	int m_testNum = 0;
	/// @brief �e�X�g�p�̃t�H���g
	FontRender* m_testFont;
	/// @brief �e�X�g�p�̐��l�\���t�H���g
	FontRender* m_testNumFont;
};

