#include "stdafx.h"
#include "Objects.h"

namespace {
	const Vector3 SCALE = { 1.0f,1.0f,1.0f };
	const float BALL_DISTANCE = 120.0f;
}
Objects::Objects() {

	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_playerNum = m_gameDirector->GetPlayerNum();

	m_fall = 2;
}
Objects::~Objects() {
	for (int del = 0; del < SetNum; del++) {
		if (m_delFlag[del] == true) {
			DeleteGO(m_skinModelRender[del]);
		}
	}
}
bool Objects::Start() {
	m_ball = FindGO<Ball>(BALL_NAME);
	m_ui = FindGO<GameUI>(GAME_UI_NAME);
	for (int plNum = 0; plNum < m_playerNum; plNum++) {
		m_player[plNum] = FindGO<Player>(PLAYER_NAME[plNum]);
	}


	return true;
}
void Objects::SetObjects(int num) {
	for (SetNum; SetNum < num; SetNum++) {
		m_skinModelRender[SetNum] = NewGO<SkinModelRender>(0);
		m_skinModelRender[SetNum]->Init("Assets/modelData/object/box.tkm");
		m_skinModelRender[SetNum]->SetScale(SCALE);
		m_colliderPos[SetNum] = { 0.0f,800.0f,0.0f };

		SetDelNum++;
		m_delFlag[SetNum] = true;

		switch (SetNum)
		{
		case 0:
			m_position[SetNum] = { 200.0f,400.0f,-400.0f };
			m_charaCon[SetNum].Init(40.0f, 40.0f, m_position[SetNum]);
			break;
		case 1:
			m_position[SetNum] = { 100.0f,400.0f,-400.0f };
			m_charaCon[SetNum].Init(40.0f, 40.0f, m_position[SetNum]);
			break;
		case 2:
			m_position[SetNum] = { -300.0f,400.0f,400.0f };
			m_charaCon[SetNum].Init(40.0f, 40.0f, m_position[SetNum]);
			break;
		case 3:
			m_position[SetNum] = { -150.0f,400.0f,400.0f };
			m_charaCon[SetNum].Init(40.0f, 40.0f, m_position[SetNum]);
			break;
		}

	}
}
void Objects::Update() {

	DistanceCalculation();

	for (int setPosNum = 0; setPosNum < SetDelNum; setPosNum++) {
		if (m_delFlag[setPosNum] == true) {
			if (m_position[setPosNum].y > 50) {
				m_fallSpeed[setPosNum].y -= m_fall;
			}
			if (m_ballDistance[setPosNum] < BALL_DISTANCE) {
				ballCollider(setPosNum);
			}
			m_position[setPosNum] = m_charaCon[setPosNum].Execute(m_fallSpeed[setPosNum], 1.0f);
			m_charaCon[setPosNum].SetPosition(m_position[setPosNum]);
			//m_setPos[setPosNum] = m_position[setPosNum];
			m_skinModelRender[setPosNum]->SetPosition(m_position[setPosNum]);
		}
	}



}
void Objects::ballCollider(int num) {
	m_charaCon[num].SetPosition(m_colliderPos[num]);
	DeleteGO(m_skinModelRender[num]);
	m_delFlag[num] = false;
}
void Objects::DistanceCalculation() {
	for (int setPosNum = 0; setPosNum < SetDelNum; setPosNum++) {
		m_toBallVec[setPosNum] = m_ball->GetPosition() - m_position[setPosNum];
		m_ballDistance[setPosNum] = m_toBallVec[setPosNum].Length();
		m_toBallVec[setPosNum].y = FLOAT_0;
		m_toBallVec[setPosNum].Normalize();
	}
}
