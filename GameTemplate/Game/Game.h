#pragma once

class Lighting;
class SkinModelRender;
class Player;

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
	SkinModelRender* m_skinModelRender = nullptr;
	SkinModelRender* m_skinModelRender2 = nullptr;
	SkinModelRender* m_skinModelRender3 = nullptr;
	SkinModelRender* m_bg = nullptr;
};

