#include "stdafx.h"
#include "GameUI.h"

namespace {

	const int PL1 = 0;
	const int PL2 = 1;
	const int PL3 = 2;
	const int PL4 = 3;

	const Vector2 PL1_FONT_POS = { -600.0f,300.0f };
	const Vector2 PL2_FONT_POS = { 400.0f,300.0f };
	const Vector2 PL3_FONT_POS = { -600.0f,-200.0f };
	const Vector2 PL4_FONT_POS = { 400.0f,-200.0f };

	const Vector2 PL1_NUMFONT_POS = { -550.0f,255.0f};
	const Vector2 PL2_NUMFONT_POS = { 500.0f,255.0f };
	const Vector2 PL3_NUMFONT_POS = { -550.0f,-245.0f };
	const Vector2 PL4_NUMFONT_POS = { 500.0f,-245.0f };

	const Vector2 BALL_SPEED_POS = { 500.0f, -300.0f };

	const Vector4 PL1_COLOR = { 1.0f, 0.0f, 0.0f, 0.5f };
	const Vector4 PL2_COLOR = { 0.0f, 0.0f, 1.0f, 0.5f };
	const Vector4 PL3_COLOR = { 1.0f, 1.0f, 0.0f, 0.5f };
	const Vector4 PL4_COLOR = { 0.0f, 1.0f, 0.0f, 0.5f };

	const Vector2 GUARD_DURABILIYY[MAX_PLAYER_NUM] = { {-600.0f,200.0f},{400.0f,200.0f},{-600.0f,-300.0f},{400.0f,-300.0f} };
	const float SCALE = 0.9f;

	const Vector2 TIME_FONT_POS = { 80.0f, 280.0f };
	const float TIME_FONT_SCALE = 1.0f;
	const Vector2 FINISH_FONT_POS = { -200.0f,100.0f };
	const float FINISH_FONT_SCALE = 3.0f;

	//�t�B�j�b�V���X�v���C�g�\���֘A
	const char* FINISHSPRITE_FILEPATH = "Assets/sprite/finish.DDS";
	const Vector3 FINISHSPRITE_INITSCALE = { 3.0f, 3.0f, 1.0f };
	const int FINISHSPRITE_HEIGHT = 512;
	const int FINISHSPRITE_WIDTH = 512;
	
	/// @brief �J�E���g�_�E��DDS�̑���
	const int COUNT_DOWN_DDS_NUM = 3;
}

GameUI::GameUI()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_playerNum = m_gameDirector->GetPlayerNum();


	/// @brief �e�X�g�p�t�H���g�\��
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
		/*m_GuardDurability[plFontNum] = NewGO<FontRender>(2);
		m_GuardDurability[plFontNum]->SetPosition(GUARD_DURABILIYY[plFontNum]);*/
		switch (plFontNum)
		{
		case 0:
			/// @brief PL1�̃t�H���g�\��
			//m_playerFont[PL1] = NewGO<FontRender>(2);
			m_playerFont[plFontNum]->SetText(L"PLAYER1");
			m_playerFont[plFontNum]->SetScale(SCALE);
			m_playerFont[plFontNum]->SetPosition(PL1_FONT_POS);
			m_playerFont[plFontNum]->SetColor(PL1_COLOR);

			/// @brief PL1�̐��l�̃t�H���g�\��
			//m_playerNumFont[PL1] = NewGO<FontRender>(2);
			m_playerNumFont[plFontNum]->SetPosition(PL1_NUMFONT_POS);
			break;

		case 1:
			/// @brief PL2�̃t�H���g�\��
			//m_playerFont[PL2] = NewGO<FontRender>(2);
			m_playerFont[plFontNum]->SetText(L"PLAYER2");
			m_playerFont[plFontNum]->SetScale(SCALE);
			m_playerFont[plFontNum]->SetPosition(PL2_FONT_POS);
			m_playerFont[plFontNum]->SetColor(PL2_COLOR);

			/// @brief PL2�̐��l�̃t�H���g�\��
			//m_playerNumFont[PL2] = NewGO<FontRender>(2);
			m_playerNumFont[plFontNum]->SetPosition(PL2_NUMFONT_POS);
			break;

		case 2:
			/// @brief PL3�̃t�H���g�\��
			//m_playerFont[PL3] = NewGO<FontRender>(2);
			m_playerFont[plFontNum]->SetText(L"PLAYER3");
			m_playerFont[plFontNum]->SetScale(SCALE);
			m_playerFont[plFontNum]->SetPosition(PL3_FONT_POS);
			m_playerFont[plFontNum]->SetColor(PL3_COLOR);

			/// @brief PL3�̐��l�̃t�H���g�\��
			//m_playerNumFont[PL3] = NewGO<FontRender>(2);
			m_playerNumFont[plFontNum]->SetPosition(PL3_NUMFONT_POS);
			break;

		case 3:
			/// @brief PL4�̃t�H���g�\��
			//m_playerFont[PL4] = NewGO<FontRender>(2);
			m_playerFont[plFontNum]->SetText(L"PLAYER4");
			m_playerFont[plFontNum]->SetScale(SCALE);
			m_playerFont[plFontNum]->SetPosition(PL4_FONT_POS);
			m_playerFont[plFontNum]->SetColor(PL4_COLOR);

			/// @brief PL4�̐��l�̃t�H���g�\��
			//m_playerNumFont[PL4] = NewGO<FontRender>(2);
			m_playerNumFont[plFontNum]->SetPosition(PL4_NUMFONT_POS);
			break;
		}
	}
	/// @brief �e�X�g�p���l�̃t�H���g
	//m_testNumFont = NewGO<FontRender>(2);
	//m_testNumFont->SetPosition({ 500.0f,100.0f, });

	for (int alpha = 0; alpha < m_playerNum; alpha++) {
		m_shieldGage[alpha] = NewGO<SpriteRender>(3);
		m_shieldGage[alpha]->Init("Assets/sprite/UI_Gage.DDS", m_ShGageSize[Width], m_ShGageSize[Height]);
		m_shieldGage[alpha]->SetColor(m_ShGageColor);
		m_shieldGage[alpha]->SetPosition(m_ShGagePos[alpha]);
		m_breakAlertMassege[alpha] = NewGO<FontRender>(3);
		m_breakAlertMassege[alpha]->SetText(L"SHIELD OFFLINE");
		m_breakAlertMassege[alpha]->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
		m_breakAlertMassege[alpha]->SetScale(0.39f);
		m_breakAlertMassege[alpha]->SetPosition(m_ShAlertMassegePos[alpha]);
		m_ShGageIcon[alpha] = NewGO<SpriteRender>(5);
		m_ShGageIcon[alpha]->Init("Assets/sprite/Shield_Icon.DDS", m_IconSize, m_IconSize);
		m_ShGageIcon[alpha]->SetColor(m_ShGageColor);
		m_ShGageIcon[alpha]->SetPosition(m_ShIconPos[alpha]);
		m_ShGageBase[alpha] = NewGO<SpriteRender>(2);
		m_ShGageBase[alpha]->Init("Assets/sprite/UI_Gage.DDS", m_gageBaseSize[Width], m_gageBaseSize[Height]);
		m_ShGageBase[alpha]->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_ShGageBase[alpha]->SetPosition(m_ShGagePos[alpha]);
		m_staminaGage[alpha] = NewGO<SpriteRender>(3);
		m_staminaGage[alpha]->Init("Assets/sprite/UI_Gage.DDS", m_StGageSize[Width], m_StGageSize[Height]);
		m_staminaGage[alpha]->SetColor(m_StGageColor);
		m_staminaGage[alpha]->SetPosition(m_StGagePos[alpha]);
		m_tiredAlertMassege[alpha] = NewGO<FontRender>(3);
		m_tiredAlertMassege[alpha]->SetText(L"STAMINA IS LOW");
		m_tiredAlertMassege[alpha]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
		m_tiredAlertMassege[alpha]->SetScale(0.39f);
		m_tiredAlertMassege[alpha]->SetPosition(m_StAlertMassegePos[alpha]);
		m_StGageBase[alpha] = NewGO<SpriteRender>(1);
		m_StGageBase[alpha]->Init("Assets/sprite/UI_Gage.DDS", m_gageBaseSize[Width], m_gageBaseSize[Height]);
		m_StGageBase[alpha]->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_StGageBase[alpha]->SetPosition(m_StGagePos[alpha]);
		m_StGageIcon[alpha] = NewGO<SpriteRender>(5);
		m_StGageIcon[alpha]->Init("Assets/sprite/Sprint_Icon.DDS", m_IconSize, m_IconSize);
		m_StGageIcon[alpha]->SetColor(m_StGageColor);
		m_StGageIcon[alpha]->SetPosition(m_StIconPos[alpha]);

		//�K�[�h�Q�[�W���������ɂ���z��
		m_ShGageBegin[alpha] = NewGO<SpriteRender>(4);
		m_ShGageBegin[alpha]->Init("Assets/sprite/GageStart.DDS", 50, 24);
		m_ShGageBegin[alpha]->SetPosition(m_ShGageBeginPos[alpha]);
		//m_ShGageBegin[alpha]->SetColor({ 0.6f, 0.6f, 1.0f, 1.0f });
		m_ShGageBody[alpha] = NewGO<SpriteRender>(4);
		m_ShGageBody[alpha]->Init("Assets/sprite/GageBody.DDS", 180, 24);
		m_ShGageBody[alpha]->SetPosition(m_ShGageBodyPos[alpha]);
		//m_ShGageBody[alpha]->SetColor({ 0.6f, 0.6f, 1.0f, 1.0f });
		m_ShGageFinal[alpha] = NewGO<SpriteRender>(4);
		m_ShGageFinal[alpha]->Init("Assets/sprite/GageFinal.DDS", 20, 24);
		m_ShGageFinal[alpha]->SetPosition(m_ShGageFinalPos[alpha]);
		//m_ShGageFinal[alpha]->SetColor({ 0.6f, 0.6f, 1.0f, 1.0f });

		//�X�^�~�i�Q�[�W���������ɂ���z��
		m_StGageBegin[alpha] = NewGO<SpriteRender>(4);
		m_StGageBegin[alpha]->Init("Assets/sprite/GageStart.DDS", 50, 24);
		m_StGageBegin[alpha]->SetPosition(m_StGageBeginPos[alpha]);
		//m_StGageBegin[alpha]->SetColor({ 0.8f, 0.8f, 0.4f, 1.0f });
		m_StGageBody[alpha] = NewGO<SpriteRender>(4);
		m_StGageBody[alpha]->Init("Assets/sprite/GageBody.DDS", 180, 24);
		m_StGageBody[alpha]->SetPosition(m_StGageBodyPos[alpha]);
		//m_StGageBody[alpha]->SetColor({ 0.8f, 0.8f, 0.4f, 1.0f });
		m_StGageFinal[alpha] = NewGO<SpriteRender>(4);
		m_StGageFinal[alpha]->Init("Assets/sprite/GageFinal.DDS", 20, 24);
		m_StGageFinal[alpha]->SetPosition(m_StGageFinalPos[alpha]);
		//m_StGageFinal[alpha]->SetColor({ 0.8f, 0.8f, 0.4f, 1.0f });
		if (alpha == 1 || alpha == 3) {	//3p��4p�̔��]����
			m_ShGageBegin[alpha]->SetScale({ -1.0f,1.0f,-1.0f });
			m_ShGageFinal[alpha]->SetScale({ -1.0f,1.0f,-1.0f });
			m_StGageBegin[alpha]->SetScale({ -1.0f,1.0f,-1.0f });
			m_StGageFinal[alpha]->SetScale({ -1.0f,1.0f,-1.0f });
		}
		/// @brief ������Ƃ����������
		m_LBbuttonIcon[alpha] = NewGO<SpriteRender>(4);
		m_LBbuttonIcon[alpha]->Init("Assets/sprite/LB_ButtonIcon.DDS", 40, 40);
		m_LBbuttonIcon[alpha]->SetPosition(m_LBbuttonIPos[alpha]);
		m_LBbuttonIcon[alpha]->SetPivot({ 1 - (256.0 / 512.0f), 1 - (152.0f / 512.0f) });
		m_RBbuttonIcon[alpha] = NewGO<SpriteRender>(4);
		m_RBbuttonIcon[alpha]->Init("Assets/sprite/RB_ButtonIcon.DDS", 40, 40);
		m_RBbuttonIcon[alpha]->SetPosition(m_RBbuttonIPos[alpha]);
		m_RBbuttonIcon[alpha]->SetPivot({ 1 - (256.0 / 512.0f), 1 - (152.0f / 512.0f) });

		m_fluctiationIndicater[alpha] = NewGO<FontRender>(2);
		m_fluctiationIndicater[alpha]->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
		m_fluctiationIndicater[alpha]->SetPosition(m_IndicaterPos[alpha]);
		m_fluctiationIndicater[alpha]->SetScale(0.6f);
	}
	for (int foxT = 0; foxT < COUNT_DOWN_DDS_NUM; foxT++)
	{
		switch (foxT)
		{
		case 0:
			m_countDDS[foxT] = NewGO<SpriteRender>(6);
			m_countDDS[foxT]->Init("Assets/sprite/1.DDS", 256 * 1.5f, 256 * 1.5f);
			m_countDDS[foxT]->SetColor({0.0f,0.0f,0.0f,0.0f});
			m_countDDS[foxT]->SetPosition({ 0.0f,0.0f,0.0f });
			break;
		case 1:
			m_countDDS[foxT] = NewGO<SpriteRender>(6);
			m_countDDS[foxT]->Init("Assets/sprite/2.DDS", 256 * 1.2, 256 * 1.2);
			m_countDDS[foxT]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_countDDS[foxT]->SetPosition({ 0.0f,0.0f,0.0f });
			break;
		case 2:
			m_countDDS[foxT] = NewGO<SpriteRender>(6);
			m_countDDS[foxT]->Init("Assets/sprite/3.DDS", 256, 256 );
			m_countDDS[foxT]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_countDDS[foxT]->SetPosition({ 0.0f,0.0f,0.0f });
			break;
		}
	}
	m_ballSpeedMeter = NewGO<SpriteRender>(4);
	m_ballSpeedMeter->Init("Assets/sprite/SpeedMeter.DDS", 220, 220);
	m_ballSpeedMeter->SetPosition({ -100.0f, 280.0f, 0.0f});
	m_ballSpeedMeter->SetScale({ 0.60f,0.60f,1.0f });

	m_ballSpeedMeterPin = NewGO<SpriteRender>(5);
	m_ballSpeedMeterPin->Init("Assets/sprite/SpeedMeterPin.DDS", 144, 144);
	m_ballSpeedMeterPin->SetPosition({ -100.0f, 280.0f, 0.0f });
	m_ballSpeedMeterPin->SetPivot({1.0f - (256.0f / 512.0f), 1.0f - (156.0f / 512.0f)});
	m_ballSpeedMeterPin->SetScale({ 0.60f,0.60f,1.0f });

	/*m_ballSpeed = NewGO<FontRender>(2);
	m_ballSpeed->SetPosition(BALL_SPEED_POS);*/

	m_timeFont = NewGO<FontRender>(3);
	m_timeFont->SetPosition(TIME_FONT_POS);
	m_timerFrame = NewGO<SpriteRender>(2);
	m_timerFrame->Init("Assets/sprite/TimerFrame.DDS", 150, 150);
	m_timerFrame->SetPosition({ 100.0f,260.0f , 0.0f });
	m_timerHedder = NewGO<FontRender>(2);
	m_timerHedder->SetPosition({ 55.0f,330.0f });
	m_timerHedder->SetText(L"Time");
	m_timerHedder->SetScale(0.6f);


	m_finishSprite = NewGO<SpriteRender>(3);
	//�t�B�j�b�V���X�v���C�g�̏�����
	m_finishSprite->Init(FINISHSPRITE_FILEPATH, FINISHSPRITE_WIDTH, FINISHSPRITE_HEIGHT);
	//�s�{�b�g��ݒ�
	m_finishSprite->SetPivot({ 0.5f,0.5f });

	m_finishSpriteScale = FINISHSPRITE_INITSCALE;

	m_finishSprite->SetScale(m_finishSpriteScale);

	m_finishSprite->SetColor({ 1.0f,1.0f,1.0f,0.0f });

}

GameUI::~GameUI()
{
	for (int playerNum = 0; playerNum < m_playerNum; playerNum++) {
		DeleteGO(m_playerNumFont[playerNum]);
		DeleteGO(m_playerFont[playerNum]);
	//	DeleteGO(m_GuardDurability[playerNum]);
	}
	for (int bravo = 0; bravo < m_playerNum; bravo++) {
		DeleteGO(m_shieldGage[bravo]);
		DeleteGO(m_staminaGage[bravo]);
		DeleteGO(m_breakAlertMassege[bravo]);
		DeleteGO(m_tiredAlertMassege[bravo]);
		DeleteGO(m_ShGageBase[bravo]);
		DeleteGO(m_ShGageIcon[bravo]);
		DeleteGO(m_ShGageBegin[bravo]);
		DeleteGO(m_ShGageBody[bravo]);
		DeleteGO(m_ShGageFinal[bravo]);
		DeleteGO(m_StGageBase[bravo]);
		DeleteGO(m_StGageIcon[bravo]);
		DeleteGO(m_StGageBegin[bravo]);
		DeleteGO(m_StGageBody[bravo]);
		DeleteGO(m_StGageFinal[bravo]);
		DeleteGO(m_LBbuttonIcon[bravo]);
		DeleteGO(m_RBbuttonIcon[bravo]);
		DeleteGO(m_fluctiationIndicater[bravo]);
	}
	for (int golf = 0; golf < COUNT_DOWN_DDS_NUM; golf++)
	{
		DeleteGO(m_countDDS[golf]);
	}
	//DeleteGO(m_ballSpeed);
	DeleteGO(m_ballSpeedMeter);
	DeleteGO(m_ballSpeedMeterPin);
	DeleteGO(m_timeFont);
	DeleteGO(m_timerFrame);
	DeleteGO(m_timerHedder);
	DeleteGO(m_finishSprite);
}

bool GameUI::Start()
{
	m_timer = FindGO<Timer>(TIMER_NAME);
	m_score = FindGO<Score>(SCORE_NAME);
	m_ball = FindGO<Ball>(BALL_NAME);
	for (int plFontNum = 0; plFontNum < m_playerNum; plFontNum++) {
		m_player[plFontNum] = FindGO<Player>(PLAYER_NAME[plFontNum]);
		m_plAction[plFontNum] = FindGO<PlayerAction>(PLAYER_ACTION_NAME[plFontNum]);
		m_plMove[plFontNum] = FindGO<PlayerMove>(PLAYER_MOVE_NAME[plFontNum]);
	}
	return true;
}

void GameUI::TimerFont()
{
	float time = FLOAT_0;
	/*if (m_timer->IsCountDown() == true) {
		time = m_timer->GetCountDownNum() + 1.0f;
		if ((int)time == 4) {
			m_timeFont->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
		}
		else
		{
			m_timeFont->SetColor({1.0f,1.0f,1.0f,1.0f});
		}
		std::wstring conversion;
		int integerTime = time;
		conversion = std::to_wstring(integerTime);
		m_timeFont->SetText(conversion.c_str());
		m_timeFont->SetScale(3.0f);
		m_timeFont->SetPosition({ 0.0f,0.0f });


	}*/
	if (m_timer->IsCountDown() == false && m_GoisGone == false)
	{
		if (m_Gone == false) {
			m_Gone = true;
			m_goSign = NewGO<SpriteRender>(6);
		}
		m_goSign->SetPosition({ 0.0f, 0.0f, 0.0f });
		m_goSign->Init("Assets/sprite/Go.DDS",512, 512);
		m_goSign->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		m_goSign->SetScale({ m_GOScale,m_GOScale ,0.0f });
		m_GOScale -= 1.2f;
		if (m_GOScale <= 1.0f) {
			m_GOScale = 1.0f;
		}
		
		//m_goSign->SetScale({ 2.0f, 2.0f, 0.0f });
		if (goGoneWaiter >= 50) 
		{
			DeleteGO(m_goSign);
			m_GoisGone = true;
		}
		goGoneWaiter++;
	}
	if (m_timer->IsTimerExecution() == true) {
		time = m_timer->GetTimer();
		int integerTime = time;
		std::wstring conversion;
		conversion = std::to_wstring(integerTime);
		m_timeFont->SetScale(1.0f);
		m_timeFont->SetPosition(TIME_FONT_POS);
		m_timeFont->SetText(conversion.c_str());
	}
	if (m_timer->IsFinish() == true) {
		/*m_timeFont->SetText(L"Finish");
		m_timeFont->SetPosition(FINISH_FONT_POS);
		m_timeFont->SetScale(FINISH_FONT_SCALE);*/
		//�t�F�[�h�C��
		m_finishSprite->FadeIn(2.0f);
		//�k�����鏈��
		m_finishSpriteScale.x -= 0.1f;
		m_finishSpriteScale.y -= 0.1f;
		//�����ɂȂ����炻�̑傫���ŌŒ肷��
		if (m_finishSpriteScale.x < 1.0f) {
			m_finishSpriteScale.x = 1.0f;
		}
		if (m_finishSpriteScale.y < 1.0f) {
			m_finishSpriteScale.y = 1.0f;
		}

		m_finishSprite->SetPosition(m_finishSpritePos);
		m_finishSprite->SetScale(m_finishSpriteScale);

	}
	if (m_timer->IsTimerEnd() == true) {
		m_timeFont->SetText(L"PUSH A BUTTON");
		m_timeFont->SetPosition({-100.0f, -275.0f});
		m_timeFont->SetScale(TIME_FONT_SCALE);

		m_finishSprite->FadeOut(1.0f);
	}
	
	
}

void GameUI::ScoreHider()
{
	if (m_timer->GetTimer() <= 30.0f && m_timer->GetTimer() != 0.0f) {
		const wchar_t hidenScore[] = { L"****" };
		for (int hide = 0; hide < m_playerNum; hide++)
		{
			m_playerNumFont[hide]->SetText(hidenScore);
		}
	}
	if (m_timer->GetTimer() == 0.0f) {
		for (int invScore = 0; invScore < m_playerNum; invScore++) {
			m_playerNumFont[invScore]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_fluctiationIndicater[invScore]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
		}
	}
}

void GameUI::Playerhider()
{
	if (m_timer->IsFinish() == true)
	{
		for (int PHide = 0; PHide < m_playerNum; PHide++)
		{
			m_playerFont[PHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f, });
		}
	}
}

void GameUI::GageHider()
{
	if (m_timer->GetTimer() == 0.0f)
	{
		for (int GHide = 0; GHide < m_playerNum; GHide++)
		{
			m_shieldGage[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_staminaGage[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_ShGageBase[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_StGageBase[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_ShGageBegin[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_StGageBegin[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_ShGageBody[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_StGageBody[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_ShGageFinal[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_StGageFinal[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_ShGageIcon[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_StGageIcon[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_LBbuttonIcon[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_RBbuttonIcon[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_breakAlertMassege[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_tiredAlertMassege[GHide]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
		}
	}
}

void GameUI::CountDown(int count)
{
	if (count >= 3 || count <= -1)
	{
		return;
	}
	if (m_countDDS[count + 1] != nullptr)
	{
		m_countDDS[count + 1]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
	}
	if (count > 3 || count < 0) {
		return;
	}
	m_countDDS[count]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	if (m_Gone == true)
	{
		m_countDDS[count]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
	}
}

void GameUI::Update()
{
	/// @brief int�^�̐��l�𕶎���ɕϊ����ďo��
	//std::wstring conversion;
	//conversion = std::to_wstring(m_testNum);
	//m_testNumFont->SetText(conversion.c_str());
	for (int plFontNum = 0; plFontNum < m_playerNum; plFontNum++) {
			/// @brief int�^�̐��l�𕶎���ɕϊ����ďo��
			NowScore[plFontNum] = m_score->GetScore(plFontNum);
			/// @brief �\���X�R�A�ƌ��݃X�R�A�̍��̐�Βl��ϓ��l�Ƃ���

			if (NowScore[plFontNum] > viewScore[plFontNum]) {
				if ((NowScore[plFontNum] - viewScore[plFontNum]) <= 3.0f) {
					viewScore[plFontNum] = NowScore[plFontNum];
				}
				viewScore[plFontNum] += 3;
			}
			else if(NowScore[plFontNum] < viewScore[plFontNum])
			{
				if ((NowScore[plFontNum] - viewScore[plFontNum]) >= 3.0f) {
					viewScore[plFontNum] = NowScore[plFontNum];
				}
				viewScore[plFontNum] -= 3;
			}
			else
			{
				viewScore[plFontNum] = NowScore[plFontNum];
			}
		
			std::wstring conversion;
			/// @brief PL�̃X�R�A�̐��l�����
			conversion = std::to_wstring((int)viewScore[plFontNum]);
			m_playerNumFont[plFontNum]->SetText(conversion.c_str());
			float fluctiationVal[4];
			fluctiationVal[plFontNum] = NowScore[plFontNum] - oldScore[plFontNum];
			std::wstring conversion2 = std::to_wstring((int)fluctiationVal[plFontNum]);

			if (m_fluctiationIndicater[plFontNum]->GetOpacity() == 0.0f) {
				m_fluctiationIndicater[plFontNum]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			}

			if (fluctiationVal[plFontNum] > 0)
			{
				//m_fluctiationScore[plFontNum] += fluctiationVal[plFontNum];
				m_indicaterWaiter = 0;
				std::wstring convIndi = std::to_wstring((int)fluctiationVal[plFontNum]);
				convIndi += ('+');
				m_fluctiationIndicater[plFontNum]->SetText(convIndi.c_str());
				m_fluctiationIndicater[plFontNum]->FadeIn(2.0f);
				m_fluctiationIndicater[plFontNum]->SetColor({ 1.0f, 0.0f, 0.0f, 0.0f });
			}
			else if (fluctiationVal[plFontNum] < 0)
			{
				//m_fluctiationScore[plFontNum] += fluctiationVal[plFontNum];
				m_indicaterWaiter = 0;
				std::wstring convIndi = std::to_wstring((int)fluctiationVal[plFontNum] * -1);
				convIndi += ('-');

				m_fluctiationIndicater[plFontNum]->SetText(convIndi.c_str());
				m_fluctiationIndicater[plFontNum]->FadeIn(2.0f);
				m_fluctiationIndicater[plFontNum]->SetColor({ 0.0f, 0.0f, 1.0f, 0.0f });
				if (m_timer->GetTimer() <= 30.0f) {
					m_fluctiationIndicater[plFontNum]->SetText(L"***-");
				}
			}
			else
			{
				m_indicaterWaiter++;
				if (m_indicaterWaiter >= 120) {
					m_fluctiationIndicater[plFontNum]->FadeOut(2.0f);
					//m_fluctiationIndicater[plFontNum]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
					m_fluctiationScore[plFontNum] = 0.0f;
				}
			}

			oldScore[plFontNum] = NowScore[plFontNum];
			GameUI::ScoreHider();
	}


	/// @brief �{�[���̑��x�����
	m_ballVelocity = m_ball->GetVelocity();
	/// @brief ������ɕϊ����ďo��
	//std::wstring conv = std::to_wstring(m_ballVelocity);
	//const wchar_t* speed = conv.c_str();
	//swprintf(m_text, L"%2.1f", speed);
	//m_ballSpeed->SetText(speed);

	for (int charley = 0; charley < m_playerNum; charley++)
	{
		/// @brief �V�[���h�Q�[�W�̌�������
		float DurbilityBat = m_player[charley]->GetGuardDurability() / 100;
		m_shieldGage[charley]->SetScale({ DurbilityBat, 1.0f, 1.0f });
		m_shieldGage[charley]->SetPosition(m_ShGagePos[charley]);
		float ShGageDownVa = (m_ShGageSize[Width] * (1.0f - DurbilityBat)) / 2;	//Sh�Q�[�W������
		//m_shieldGage[charley]->SetColor({ DurbilityBat, m_ShGageColor.y, m_ShGageColor.z - DurbilityBat, 0.8f });
		if (charley % 2 == 1) {
			m_shieldGage[charley]->SetPosition({ m_ShGagePos[charley].x + ShGageDownVa, m_ShGagePos[charley].y, 0.0f });

				
		}
		else {
			m_shieldGage[charley]->SetPosition({m_ShGagePos[charley].x - ShGageDownVa, m_ShGagePos[charley].y, 0.0f });
		}
		/// @brief �X�^�~�i�Q�[�W�̌�������
		float StaminaBat = (m_player[charley]->GetStamina() * m_staminaComplement) / 100;
		m_staminaGage[charley]->SetScale({ StaminaBat, 1.0f, 1.0f });
		m_staminaGage[charley]->SetPosition(m_StGagePos[charley]);
		float stGageDownVa = (m_StGageSize[Width] * (1.0f - StaminaBat)) / 2;
		if (charley % 2 == 1) {
			m_staminaGage[charley]->SetPosition({ m_StGagePos[charley].x + stGageDownVa, m_StGagePos[charley].y, 0.0f });
		}
		else {
			m_staminaGage[charley]->SetPosition({ m_StGagePos[charley].x - stGageDownVa, m_StGagePos[charley].y, 0.0f });

		}
	}
	for (int delta = 0; delta < m_playerNum; delta++)
	{
		//�V�[���h�A���[�g��\�����邩���Ȃ����̕���
		if (m_player[delta]->GetGuardBreak()) {
			m_shieldGage[delta]->SetColor(m_ShAlertColor);
			m_breakAlertMassege[delta]->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		}
		else {
			m_shieldGage[delta]->SetColor(m_ShGageColor); 
			m_breakAlertMassege[delta]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
		}
		//�X�^�~�i�A���[�g��\�����邩���Ȃ����̕���
		if (m_player[delta]->GetDashFlg() == false) {
			m_staminaGage[delta]->SetColor(m_StAlertColor);
			m_tiredAlertMassege[delta]->SetColor( { 1.0f, 0.0f, 0.0f, 1.0f });
		}
		else {
			m_staminaGage[delta]->SetColor(m_StGageColor);
			m_tiredAlertMassege[delta]->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
		}
	}

	for (int echo = 0; echo < m_playerNum; echo++) {
		if (g_pad[echo]->IsPress(enButtonLB1)) 
		{
			//m_LBbuttonIcon[echo]->SetScale({ 1.0f, 0.8f, 0.0f });
			m_LBbuttonIcon[echo]->SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		}
		else
		{
			//m_LBbuttonIcon[echo]->SetScale({ 1.0f, 1.0f, 0.0f });
			m_LBbuttonIcon[echo]->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		}
		if (g_pad[echo]->IsPress(enButtonRB1)) 
		{
			//m_RBbuttonIcon[echo]->SetScale({ 1.0f, 0.8f, 0.0f });
			m_RBbuttonIcon[echo]->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
		}
		else
		{
			//m_RBbuttonIcon[echo]->SetScale({ 1.0f, 1.0f, 0.0f });
			m_RBbuttonIcon[echo]->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		}
	}
	
	PinAngArrival = (m_ballVelocity * -7.0f) - 60.0f;
	float PinSpeed = std::pow(PinAngArrival - PinRot, 2);
	PinSpeed = std::sqrt(PinSpeed) * 0.05;

	if (PinRot > PinAngArrival) {
		PinRot -= PinSpeed;
	}
	else { PinRot += PinSpeed; }

	if (PinRot < -300.0f) {
		PinRot = -300.0f;
	}
	if (PinRot < -237.0f)
	{
		m_ballSpeedMeterPin->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	}
	else { m_ballSpeedMeterPin->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f }); }

	//PinRot = PinAngArrival;
	Quaternion PinQuaternion;
	PinQuaternion.SetRotationDeg(Vector3::AxisZ, PinRot);
	

	m_ballSpeedMeterPin->SetRotation(PinQuaternion);


	//for (int plFontNum = 0; plFontNum < m_playerNum; plFontNum++) {
	//	std::wstring conv = std::to_wstring(m_player[plFontNum]->GetGuardDurability());
	//	m_GuardDurability[plFontNum]->SetText(conv.c_str());
	//}
	TimerFont();
	/*GameUI::*/Playerhider();
	/*GameUI::*/GageHider();
	CountDown((int)m_timer->GetCountDownNum());
}
void GameUI::AddScore(int num, int score) {
	/// @brief PL�̃X�R�A�����Z����
	m_plNum[num] += score;
}