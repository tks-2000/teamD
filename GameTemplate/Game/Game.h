#pragma once

class GameDirector;
class Lighting;
class GameUI;
class Player;
class GameCamera;
class BackGround;
class Ball;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();

private:

	GameDirector* m_gameDirector = nullptr;
	/// @brief �v���C���[�̐l��
	int m_playerNum = 0;
	/// @brief ���C�e�B���O
	Lighting* m_lighting = nullptr;

	GameUI* m_ui = nullptr;
	/// @brief �v���C���[
	Player* m_player[4] = { nullptr };
	/// @brief �Q�[���J����
	GameCamera* m_gameCamera = nullptr;
	/// @brief �w�i
	BackGround* m_backGround = nullptr;
	/// @brief �{�[��
	Ball* m_ball = nullptr;

};

