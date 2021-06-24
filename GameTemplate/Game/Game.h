#pragma once

class GameDirector;
class Lighting;
class GameUI;
class Player;
class GameCamera;
class BackGround;
class Ball;
class Sky;

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
	/// @brief ライティング
	Lighting* m_lighting = nullptr;

	GameUI* m_ui = nullptr;
	/// @brief プレイヤー
	Player* m_player[4] = { nullptr };
	/// @brief ゲームカメラ
	GameCamera* m_gameCamera = nullptr;
	/// @brief 背景
	BackGround* m_backGround = nullptr;
	/// @brief ボール
	Ball* m_ball = nullptr;
	/// @brief 背景の空
	Sky* m_sky = nullptr;

};

