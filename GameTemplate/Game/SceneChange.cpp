#include "stdafx.h"
#include "SceneChange.h"

namespace {
	const char* BLACKSPRITE_FILEPATH = "Assets/sprite/BLACK.dds";
	const float FADE_RATE = 1.0f;
}

SceneChange::SceneChange()
{
	m_transparencySprite = NewGO<SpriteRender>(10);
	m_transparencySprite->Init(BLACKSPRITE_FILEPATH, 1280, 720);
	m_fadeRate = FADE_RATE;
}

SceneChange::~SceneChange()
{

}

bool SceneChange::Start()
{

	return true;
}

void SceneChange::TransparencyChange(bool TorF) 
{
	if (TorF == true) {
		m_transparencySprite->FadeOut(m_fadeRate);
	}
	else {
		m_transparencySprite->FadeIn(m_fadeRate);
	}

}

void SceneChange::Update()
{

}