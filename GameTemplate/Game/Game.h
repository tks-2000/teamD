#pragma once

class SkinModelRender;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();

private:
	SkinModelRender* m_skinModelRender = nullptr;
	
};

