#pragma once

class GameDirector;
class Timer;
class Lighting;
class GameUI;
class Player;
class PlayerEffect;
class GameCamera;
class BackGround;
class Ball;
class Objects;
class Sky;


const int PLAYER_NUMBER = 4;
const float ZeroF = 0.0f;
static const int OBJECTS_NUMBER = 10;

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
	/// @brief �^�C�}�[
	Timer* m_timer = nullptr;
	/// @brief ���C�e�B���O
	Lighting* m_lighting = nullptr;

	GameUI* m_ui = nullptr;
	/// @brief �v���C���[
	Player* m_player[PLAYER_NUMBER] = { nullptr };
	/// @brief �v���C���[�̃G�t�F�N�g
	PlayerEffect* m_playerEffect = nullptr;
	/// @brief �Q�[���J����
	GameCamera* m_gameCamera = nullptr;
	/// @brief �w�i
	BackGround* m_backGround = nullptr;
	/// @brief �{�[��
	Ball* m_ball = nullptr;
	/// @brief �{�[��
	Objects* m_objects = nullptr;
	/// @brief �w�i�̋�
	Sky* m_sky = nullptr;

};

