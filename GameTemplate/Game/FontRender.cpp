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

void FontRender::Update()
{
	Fade();
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