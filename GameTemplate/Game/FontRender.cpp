#include "stdafx.h"
#include "FontRender.h"

FontRender::FontRender()
{

}

FontRender::~FontRender()
{

}

bool FontRender::Start()
{

	return true;
}

void FontRender::SetText(const wchar_t* text)
{
	if (wcscmp(m_text.c_str(), text) != 0) {
		m_text = text;
	}
}

bool FontRender::IsOpacity()
{
	if (m_color.w >= FLOAT_1) {
		return true;
	}
	else {
		return false;
	}
}

bool FontRender::IsTransparent()
{
	if (m_color.w <= FLOAT_0) {
		return true;
	}
	else {
		return false;
	}
}

void FontRender::Fade()
{
	if (m_fadeInFlag == true) {
		m_color.w += m_fadeRate * g_gameTime->GetFrameDeltaTime();
	}
	if (m_fadeOutFlag == true) {
		m_color.w -= m_fadeRate * g_gameTime->GetFrameDeltaTime();
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

void FontRender::MoveStart(const Vector2& targetPos, float velocity)
{
	m_targetPos = targetPos;
	m_moveSpeed.x = m_targetPos.x - m_position.x;
	m_moveSpeed.y = m_targetPos.y - m_position.y;
	float Length = m_moveSpeed.x * m_moveSpeed.x;
	Length = m_moveSpeed.y * m_moveSpeed.y;
	Length = sqrtf(Length);
	m_moveSpeed.x /= Length;
	m_moveSpeed.y /= Length;

	m_moveSpeed.x *= velocity;
	m_moveSpeed.y *= velocity;

	m_moveFlag = true;

}

void FontRender::Move()
{
	/// @brief 移動する前の自分の座標を記憶する
	m_previousPos = m_position;

	m_position.x += m_moveSpeed.x * g_gameTime->GetFrameDeltaTime();
	m_position.y += m_moveSpeed.y * g_gameTime->GetFrameDeltaTime();

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

	/// @brief 目標地点に着いたら移動を終わる
	if (m_position.x == m_targetPos.x && m_position.y == m_targetPos.y) {
		m_moveFlag = false;
	}
}

void FontRender::Update()
{
	Fade();
	if (m_moveFlag == true) {
		Move();
	}
}

void FontRender::Render(RenderContext& rc)
{
	m_font.Begin(rc);
	const wchar_t* text = nullptr;
	if (m_text.c_str() != nullptr) {
		text = m_text.c_str();
	}
	m_font.Draw(
		text,
		m_position,
		m_color,
		m_rotation,
		m_scale,
		m_pivot
	);
	m_font.End(rc);

}