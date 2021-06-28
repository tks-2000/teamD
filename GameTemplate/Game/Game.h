#pragma once

class GameDirector;
class Timer;
class Lighting;
class GameUI;
class Score;
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
	/// @brief プレイヤーの人数
	int m_playerNum = 0;
	/// @brief タイマー
	Timer* m_timer = nullptr;
	/// @brief ライティング
	Lighting* m_lighting = nullptr;
	/// @brief スコア
	Score* m_score = nullptr;

	GameUI* m_ui = nullptr;
	/// @brief プレイヤー
	Player* m_player[PLAYER_NUMBER] = { nullptr };
	/// @brief プレイヤーのエフェクト
	PlayerEffect* m_playerEffect = nullptr;
	/// @brief ゲームカメラ
	GameCamera* m_gameCamera = nullptr;
	/// @brief 背景
	BackGround* m_backGround = nullptr;
	/// @brief ボール
	Ball* m_ball = nullptr;
	/// @brief ボール
	Objects* m_objects = nullptr;
	/// @brief 背景の空
	Sky* m_sky = nullptr;

};

