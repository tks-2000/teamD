#include "stdafx.h"
#include "Title.h"

Title::Title()
{
	m_titleSprite = NewGO<SpriteRender>(0);
	m_titleSprite->Init("Assets/sprite/title.dds", 1280, 720);
	m_font = NewGO<FontRender>(1);
	m_font->SetText(L"PUSH A BUTTON");
	m_font->SetPivot({ 0.5f,0.5f });
	m_font->SetPosition({ -125.0f,-250.0f });
	m_font->SetColor({ 0.0f,0.0f,0.0f,1.0f });
}

Title::~Title()
{
	DeleteGO(m_titleSprite);
	DeleteGO(m_font);
}

bool Title::Start()
{
	return true;
}

void Title::Update()
{
	if (m_font->IsTransparent() == true) {
		m_font->FadeIn(0.01f);
	}
	if (m_font->IsOpacity() == true) {
		m_font->FadeOut(0.01f);
	}

	/// @brief Aボタンでゲームスタート
	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(this);
		NewGO<Game>(0, "Game");
	}
}