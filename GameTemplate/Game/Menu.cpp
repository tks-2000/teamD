#include "stdafx.h"
#include "Menu.h"

namespace {
	/// @brief Playerのフォント位置
	const Vector2 PLAYER_FONT_POS = { 100.0f,-200.0f };
	/// @brief 人数のフォント位置
	const Vector2 PLAYER_NUM_FONT_POS = { 0.0f,-200.0f };

	const Vector3 PLAYER_MODEL_POS[MAX_PLAYER_NUM] = { {-200.0f,0.0f,200.0f},{200.0f,0.0f,200.0f},{-200.0f,0.0f,-200.0f},{200.0f,0.0f,-200.0f} };

	const Vector3 CAMERA_POS = { 0.0f,300.0f,-600.0f };

	const float SPOT_LIGHT_HEIGHT = 500.0f;

	const float ROTATIONAL_SPEED = 3.0f;
}

Menu::Menu()
{
	m_plNumFont = NewGO<FontRender>(2);
	m_plNumFont->SetPosition(PLAYER_NUM_FONT_POS);
	m_plFont = NewGO<FontRender>(2);
	m_plFont->SetPosition(PLAYER_FONT_POS);
	m_plFont->SetText(L"Player");
	m_animationClips[enAnimation_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimation_clear].Load("Assets/animData/unitychan/clear.tka");
	m_animationClips[enAnimation_jump].Load("Assets/animData/unitychan/jump.tka");

	m_animationClips[enAnimation_Idle].SetLoopFlag(true);

	for (int plNum = 0; plNum < MAX_PLAYER_NUM; plNum++) {
		m_pos[plNum] = PLAYER_MODEL_POS[plNum];
		m_plModel[plNum] = NewGO<SkinModelRender>(PRIORITY_VERYLOW);
		m_plModel[plNum]->InitA(UNITYCHAN_MODEL, "Assets/modelData/unityChan.tks", m_animationClips, enAnimation_Num);
		m_plModel[plNum]->PlayAnimation(enAnimation_Idle, FLOAT_1);
		m_riseSpeed[plNum] = FLOAT_0;
		m_spLigPos[plNum] = m_pos[plNum];
		m_spLigPos[plNum].y += SPOT_LIGHT_HEIGHT;
	}
	g_camera3D->SetPosition(CAMERA_POS);
	m_endFlag = false;
}

Menu::~Menu()
{
	DeleteGO(m_plNumFont);
	DeleteGO(m_plFont);
	for (int plNum = 0; plNum < MAX_PLAYER_NUM; plNum++) {
		DeleteGO(m_plModel[plNum]);
	}
}

bool Menu::Start()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_lig = FindGO<Lighting>(LIGHTING_NAME);
	return true;
}

void Menu::Update()
{
	if (m_endFlag == false) {
		/// @brief ボタン上下で人数選択
		if (g_pad[0]->IsTrigger(enButtonDown)) {
			m_playerNum++;
			if (m_playerNum > MAX_PLAYER_NUM) {
				m_playerNum = 0;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonUp)) {
			m_playerNum--;
			if (m_playerNum < 0) {
				m_playerNum = MAX_PLAYER_NUM;
			}
		}

		m_gameDirector->SetPlayerNum(m_playerNum);
		std::wstring plNum;
		plNum = std::to_wstring(m_playerNum);
		m_plNumFont->SetText(plNum.c_str());
	}
	for (int plNum = 0; plNum < MAX_PLAYER_NUM; plNum++) {
		if (m_playerNum > plNum) {
			if (m_endFlag == false) {
				m_plModel[plNum]->PlayAnimation(enAnimation_clear, FLOAT_1);
			}
			if (m_angle[plNum] < 180.0f) {
				m_angle[plNum] += ROTATIONAL_SPEED;
			}
			if (m_angle[plNum] > 180.0f) {
				m_angle[plNum] -= ROTATIONAL_SPEED;
			}
			m_lig->SetSpotLightColor(plNum, WHITE);
		}
		else {
			m_plModel[plNum]->PlayAnimation(enAnimation_Idle, FLOAT_1);
			if (m_angle[plNum] < 360.0f && m_angle[plNum] != 0.0f) {
				m_angle[plNum] += ROTATIONAL_SPEED;
			}
			m_lig->SetSpotLightColor(plNum, COLORLESS);
		}
		if (m_angle[plNum] >= 360.0f) {
			m_angle[plNum] = 0.0f;
		}
		m_qRot[plNum].SetRotationDeg(Vector3::AxisY, m_angle[plNum]);
		m_plModel[plNum]->SetRotation(m_qRot[plNum]);
		m_pos[plNum].y += m_riseSpeed[plNum];
		m_plModel[plNum]->SetPosition(m_pos[plNum]);
		m_lig->SetSpotLightPos(plNum, m_spLigPos[plNum]);
		m_lig->SetSpotLightDirection(plNum, m_pos[plNum] - m_spLigPos[plNum]);

	}

	if (m_endFlag == true) {
		for (int plNum = 0; plNum < MAX_PLAYER_NUM; plNum++) {
			if (m_playerNum > plNum) {
				m_riseSpeed[plNum] += 0.2f;
				m_plModel[plNum]->PlayAnimation(enAnimation_jump, FLOAT_1);
			}
		}
	}
}