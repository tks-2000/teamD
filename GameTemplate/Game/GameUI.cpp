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

	const Vector2 BALL_SPEED_POS = { 500.0f,0.0f };

	const Vector4 PL1_COLOR = { 1.0f, 0.0f, 0.0f, 0.5f };
	const Vector4 PL2_COLOR = { 0.0f, 0.0f, 1.0f, 0.5f };
	const Vector4 PL3_COLOR = { 1.0f, 1.0f, 0.0f, 0.5f };
	const Vector4 PL4_COLOR = { 0.0f, 1.0f, 0.0f, 0.5f };

	const float SCALE = 1.0f;
}

GameUI::GameUI()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_playerNum = m_gameDirector->GetPlayerNum();


	/// @brief テスト用フォント表示
	//m_testFont = NewGO<FontRender>(2);
	//m_testFont->SetText(L"test");
	//m_testFont->SetScale(1.5f);
	//m_testFont->SetRotation(0.5f);
	//m_testFont->SetPosition({ 500.0f,0.0f });
	//Vector4 color = { 1.0f,0.0f,0.0f,0.5f };
	//m_testFont->SetColor(color);
	for (int plFontNum = 0; plFontNum < m_playerNum; plFontNum++) {
		m_playerFont[plFontNum] = NewGO<FontRender>(2);
		m_playerNumFont[plFontNum] = NewGO<FontRender>(2);
		switch (plFontNum)
		{
		case 0:
			/// @brief PL1のフォント表示
			//m_playerFont[PL1] = NewGO<FontRender>(2);
			m_playerFont[plFontNum]->SetText(L"PLAYER1");
			m_playerFont[plFontNum]->SetScale(SCALE);
			m_playerFont[plFontNum]->SetPosition(PL1_FONT_POS);
			m_playerFont[plFontNum]->SetColor(PL1_COLOR);

			/// @brief PL1の数値のフォント表示
			//m_playerNumFont[PL1] = NewGO<FontRender>(2);
			m_playerNumFont[plFontNum]->SetPosition(PL1_NUMFONT_POS);
			break;

		case 1:
			/// @brief PL2のフォント表示
			//m_playerFont[PL2] = NewGO<FontRender>(2);
			m_playerFont[plFontNum]->SetText(L"PLAYER2");
			m_playerFont[plFontNum]->SetScale(SCALE);
			m_playerFont[plFontNum]->SetPosition(PL2_FONT_POS);
			m_playerFont[plFontNum]->SetColor(PL2_COLOR);

			/// @brief PL2の数値のフォント表示
			//m_playerNumFont[PL2] = NewGO<FontRender>(2);
			m_playerNumFont[plFontNum]->SetPosition(PL2_NUMFONT_POS);
			break;

		case 2:
			/// @brief PL3のフォント表示
			//m_playerFont[PL3] = NewGO<FontRender>(2);
			m_playerFont[plFontNum]->SetText(L"PLAYER3");
			m_playerFont[plFontNum]->SetScale(SCALE);
			m_playerFont[plFontNum]->SetPosition(PL3_FONT_POS);
			m_playerFont[plFontNum]->SetColor(PL3_COLOR);

			/// @brief PL3の数値のフォント表示
			//m_playerNumFont[PL3] = NewGO<FontRender>(2);
			m_playerNumFont[plFontNum]->SetPosition(PL3_NUMFONT_POS);
			break;

		case 3:
			/// @brief PL4のフォント表示
			//m_playerFont[PL4] = NewGO<FontRender>(2);
			m_playerFont[plFontNum]->SetText(L"PLAYER4");
			m_playerFont[plFontNum]->SetScale(SCALE);
			m_playerFont[plFontNum]->SetPosition(PL4_FONT_POS);
			m_playerFont[plFontNum]->SetColor(PL4_COLOR);

			/// @brief PL4の数値のフォント表示
			//m_playerNumFont[PL4] = NewGO<FontRender>(2);
			m_playerNumFont[plFontNum]->SetPosition(PL4_NUMFONT_POS);
			break;
		}
	}
	/// @brief テスト用数値のフォント
	//m_testNumFont = NewGO<FontRender>(2);
	//m_testNumFont->SetPosition({ 500.0f,100.0f, });

	m_ballSpeed = NewGO<FontRender>(2);
	m_ballSpeed->SetPosition(BALL_SPEED_POS);
}

GameUI::~GameUI()
{
	for (int playerNum = 0; playerNum < m_playerNum; playerNum++) {
		DeleteGO(m_playerNumFont[playerNum]);
		DeleteGO(m_playerFont[playerNum]);

	}
	DeleteGO(m_ballSpeed);
}

bool GameUI::Start()
{
	m_ball = FindGO<Ball>(BALL_NAME);
	return true;
}

void GameUI::Update()
{
	/// @brief int型の数値を文字列に変換して出力
	//std::wstring conversion;
	//conversion = std::to_wstring(m_testNum);
	//m_testNumFont->SetText(conversion.c_str());
	for (int plFontNum = 0; plFontNum < m_playerNum; plFontNum++) {
			/// @brief int型の数値を文字列に変換して出力
			std::wstring conversion;
			/// @brief PLのスコアの数値を入力
			conversion = std::to_wstring(m_plNum[plFontNum]);
			m_playerNumFont[plFontNum]->SetText(conversion.c_str());
	}


	/// @brief ボールの速度を入手
	m_ballVelocity = m_ball->GetVelocity();
	/// @brief 文字列に変換して出力
	std::wstring conv = std::to_wstring(m_ballVelocity);
	const wchar_t* speed = conv.c_str();
	//swprintf(m_text, L"%2.1f", speed);
	m_ballSpeed->SetText(speed);
}
void GameUI::AddScore(int num, int score) {
	/// @brief PLのスコアを加算する
	m_plNum[num] += score;
}