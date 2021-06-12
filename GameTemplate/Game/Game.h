#pragma once

class Lighting;
class SkinModelRender;
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
	Lighting* m_lighting = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	BackGround* m_backGround = nullptr;
	Ball* m_ball = nullptr;

	SkinModelRender* m_skinModelRender = nullptr;
	SkinModelRender* m_skinModelRender2 = nullptr;
	SkinModelRender* m_skinModelRender3 = nullptr;
	SkinModelRender* m_bg = nullptr;
};

