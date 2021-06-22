#include "stdafx.h"
#include "GameUI.h"

namespace {
	const int PL1 = 0;
	const int PL2 = 1;
	const int PL3 = 2;
	const int PL4 = 3;

	const Vector2 PL1_FONT_POS = { -600.0f,300.0f };
	const Vector2 PL2_FONT_POS = { 450.0f,300.0f };
	const Vector2 PL3_FONT_POS = { -600.0f,-200.0f };
	const Vector2 PL4_FONT_POS = { 450.0f,-200.0f };

	const Vector2 PL1_NUMFONT_POS = { -550.0f,250.0f };
	const Vector2 PL2_NUMFONT_POS = { 500.0f,250.0f };
	const Vector2 PL3_NUMFONT_POS = { -550.0f,-250.0f };
	const Vector2 PL4_NUMFONT_POS = { 500.0f,-250.0f };

	const Vector4 PL1_COLOR = { 1.0f, 0.0f, 0.0f, 0.5f };
	const Vector4 PL2_COLOR = { 0.0f, 0.0f, 1.0f, 0.5f };
	const Vector4 PL3_COLOR = { 1.0f, 1.0f, 0.0f, 0.5f };
	const Vector4 PL4_COLOR = { 0.0f, 1.0f, 0.0f, 0.5f };

	const float SCALE = 1.0f;
}

GameUI::GameUI()
{
	/// @brief テスト用フォント表示
	//m_testFont = NewGO<FontRender>(2);
	//m_testFont->SetText(L"test");
	//m_testFont->SetScale(1.5f);
	//m_testFont->SetRotation(0.5f);
	//m_testFont->SetPosition({ 500.0f,0.0f });
	//Vector4 color = { 1.0f,0.0f,0.0f,0.5f };
	//m_testFont->SetColor(color);

	/// @brief PL1のフォント表示
	m_playerFont = NewGO<FontRender>(2);
	m_playerFont->SetText(L"PLAYER1");
	m_playerFont->SetScale(SCALE);
	m_playerFont->SetPosition(PL1_FONT_POS);
	Vector4 PlColor1 = PL1_COLOR;
	m_playerFont->SetColor(PlColor1);

	/// @brief PL2のフォント表示
	m_playerFont = NewGO<FontRender>(2);
	m_playerFont->SetText(L"PLAYER2");
	m_playerFont->SetScale(SCALE);
	m_playerFont->SetPosition(PL2_FONT_POS);
	Vector4 PlColor2 = PL2_COLOR;
	m_playerFont->SetColor(PlColor2);

	/// @brief PL3のフォント表示
	m_playerFont = NewGO<FontRender>(2);
	m_playerFont->SetText(L"PLAYER3");
	m_playerFont->SetScale(SCALE);
	m_playerFont->SetPosition(PL3_FONT_POS);
	Vector4 PlColor3 = PL3_COLOR;
	m_playerFont->SetColor(PlColor3);

	/// @brief PL4のフォント表示
	m_playerFont = NewGO<FontRender>(2);
	m_playerFont->SetText(L"PLAYER4");
	m_playerFont->SetScale(SCALE);
	m_playerFont->SetPosition(PL4_FONT_POS);
	Vector4 PlColor4 = PL4_COLOR;
	m_playerFont->SetColor(PlColor4);



	/// @brief テスト用数値のフォント
	//m_testNumFont = NewGO<FontRender>(2);
	//m_testNumFont->SetPosition({ 500.0f,100.0f, });

	/// @brief PL1の数値のフォント表示
	m_playerNumFont[PL1] = NewGO<FontRender>(2);
	m_playerNumFont[PL1]->SetPosition(PL1_NUMFONT_POS);

	/// @brief PL2の数値のフォント表示
	m_playerNumFont[PL2] = NewGO<FontRender>(2);
	m_playerNumFont[PL2]->SetPosition(PL2_NUMFONT_POS);

	/// @brief PL3の数値のフォント表示
	m_playerNumFont[PL3] = NewGO<FontRender>(2);
	m_playerNumFont[PL3]->SetPosition(PL3_NUMFONT_POS);

	/// @brief PL4の数値のフォント表示
	m_playerNumFont[PL4] = NewGO<FontRender>(2);
	m_playerNumFont[PL4]->SetPosition(PL4_NUMFONT_POS);

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
	//std::wstring conversion;
	//conversion = std::to_wstring(m_testNum);
	//m_testNumFont->SetText(conversion.c_str());

	/// @brief int型の数値を文字列に変換して出力
	std::wstring conversion1;
	/// @brief PL1のスコアの数値を入力
	conversion1 = std::to_wstring(m_plNum[PL1]);
	m_playerNumFont[PL1]->SetText(conversion1.c_str());

	/// @brief int型の数値を文字列に変換して出力
	std::wstring conversion2;
	/// @brief PL2のスコアの数値を入力
	conversion2 = std::to_wstring(m_plNum[PL2]);
	m_playerNumFont[PL2]->SetText(conversion2.c_str());

	/// @brief int型の数値を文字列に変換して出力
	std::wstring conversion3;
	/// @brief PL3のスコアの数値を入力
	conversion3 = std::to_wstring(m_plNum[PL3]);
	m_playerNumFont[PL3]->SetText(conversion3.c_str());

	/// @brief int型の数値を文字列に変換して出力
	std::wstring conversion4;
	/// @brief PL4のスコアの数値を入力
	conversion4 = std::to_wstring(m_plNum[PL4]);
	m_playerNumFont[PL4]->SetText(conversion4.c_str());

}
void GameUI::AddScore(int num, int score) {
	/// @brief PLのスコアを加算する
	m_plNum[num] += score;
}