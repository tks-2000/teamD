#include "stdafx.h"
#include "GameUI.h"

GameUI::GameUI()
{
	/// @brief テスト用フォント表示
	m_testFont = NewGO<FontRender>(2);
	m_testFont->SetText(L"test");
	m_testFont->SetScale(1.5f);
	m_testFont->SetRotation(0.5f);
	m_testFont->SetPosition({ 500.0f,0.0f });
	Vector4 color = { 1.0f,0.0f,0.0f,0.5f };
	m_testFont->SetColor(color);

	/// @brief テスト用数値のフォント
	m_testNumFont = NewGO<FontRender>(2);
	m_testNumFont->SetPosition({ 500.0f,100.0f, });
}

GameUI::~GameUI()
{

}

bool GameUI::Start()
{

	return true;
}

void GameUI::Update()
{
	/// @brief int型の数値を文字列に変換して出力
	std::wstring conversion;
	conversion = std::to_wstring(m_testNum);
	m_testNumFont->SetText(conversion.c_str());
}