#include "stdafx.h"
#include "SpriteRender.h"

SpriteRender::SpriteRender()
{

}

SpriteRender::~SpriteRender()
{

}

bool SpriteRender::Start()
{

	return true;
}

void SpriteRender::Init(const char* spriteFilePath, int width, int height)
{
	m_spriteInitData.m_ddsFilePath[0] = spriteFilePath;
	m_spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
	m_spriteInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	m_spriteInitData.m_width = width;
	m_spriteInitData.m_height = height;
	m_spriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	m_sprite.Init(m_spriteInitData);
	
}
void SpriteRender::Update()
{
	m_sprite.Update(m_position, m_qRot, m_scale, m_pivot);
}