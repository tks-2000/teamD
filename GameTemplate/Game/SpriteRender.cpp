#include "stdafx.h"
#include "SpriteRender.h"

namespace {
	const float STOP_DISTANCE_LENGTH = 1.0f;
}

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

bool SpriteRender::IsOpacity()
{
	if (m_color.w >= FLOAT_1) {
		return true;
	}
	else {
		return false;
	}
}

bool SpriteRender::IsTransparent()
{
	if (m_color.w <= FLOAT_0) {
		return true;
	}
	else {
		return false;
	}
}

void SpriteRender::Fade()
{
	if (m_fadeInFlag == true) {
		m_color.w += m_fadeRate;
	}
	if (m_fadeOutFlag == true) {
		m_color.w -= m_fadeRate;
	}
	if (m_color.w > FLOAT_1) {
		m_color.w = FLOAT_1;
		m_fadeInFlag = false;
	}
	if (m_color.w < FLOAT_0) {
		m_color.w = FLOAT_0;
		m_fadeOutFlag = false;
	}
}

void SpriteRender::MoveStart(Vector3 targetPos, float velocity)
{
	m_targetPos = targetPos;
	m_moveSpeed = m_targetPos - m_position;
	m_moveSpeed.Normalize();
	m_moveSpeed *= velocity;
	m_moveFlag = true;
}

void SpriteRender::Move()
{
	/// @brief 移動する前の自分の座標を記憶する
	m_previousPos = m_position;

	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();

	/// @brief 目標地点を通り過ぎたら目標地点に合わせる
	if (m_previousPos.x < m_targetPos.x) {
		if (m_targetPos.x <= m_position.x) {
			m_position.x = m_targetPos.x;
		}
	}
	if (m_previousPos.x > m_targetPos.x) {
		if (m_targetPos.x >= m_position.x) {
			m_position.x = m_targetPos.x;
		}
	}

	if (m_previousPos.y < m_targetPos.y) {
		if (m_targetPos.y <= m_position.y) {
			m_position.y = m_targetPos.y;
		}
	}
	if (m_previousPos.y > m_targetPos.y) {
		if (m_targetPos.y >= m_position.y) {
			m_position.y = m_targetPos.y;
		}
	}

	if (m_previousPos.z < m_targetPos.z) {
		if (m_targetPos.z <= m_position.z) {
			m_position.z = m_targetPos.z;
		}
	}
	if (m_previousPos.z > m_targetPos.z) {
		if (m_targetPos.z >= m_position.z) {
			m_position.z = m_targetPos.z;
		}
	}
	
	/// @brief 目標地点に着いたら移動を終わる
	if (m_position.x == m_targetPos.x && m_position.y == m_targetPos.y && m_position.z == m_targetPos.z) {
		m_moveFlag = false;
	}
}

void SpriteRender::Update()
{
	Fade();

	if (m_moveFlag == true) {
		Move();
	}

	m_sprite.ColorUpdate(m_color);
	m_sprite.Update(m_position, m_qRot, m_scale, m_pivot);
}