#pragma once
#include "Lighting.h"

class SkinModelRender;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	Light GetLighting(){ return *m_light; }

private:
	Lighting* m_lighting;
	Light* m_light;
	SkinModelRender* m_skinModelRender = nullptr;
	SkinModelRender* m_skinModelRender2 = nullptr;
	SkinModelRender* m_skinModelRender3 = nullptr;
	SkinModelRender* m_bg = nullptr;
};

