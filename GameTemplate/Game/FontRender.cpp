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

void FontRender::Update()
{

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