#include "stdafx.h"
#include "Objects.h"

namespace {
	const Vector3 SCALE = { 1.0f,1.0f,1.0f };
	const int MAX_OBJECTS_NUM = 4;
	const Vector3 OBJECTS_POS[MAX_OBJECTS_NUM] = { {400.0f,400.0f,400.0f},{400.0f,400.0f,-400.0f},{-400.0f,400.0f,400.0f},{-400.0f,400.0f,-400.0f} };
	const float BALL_DISTANCE = 120.0f;
}
Objects::Objects() {

	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_ball = FindGO<Ball>(BALL_NAME);
	m_playerNum = m_gameDirector->GetPlayerNum();

}
Objects::~Objects() {
	for (int Num = 0; Num < m_setNum; Num++) {
		if (m_delFlag[Num] == false) {
			DeleteGO(m_box[Num]);
		}
		
	}
}
bool Objects::Start() {

	return true;
}
void Objects::SetObjects(int num) {
	for (int setNum = 0; setNum < num; setNum++) {
		//m_colliderPos[setNum] = { 0.0f,800.0f,0.0f };
		m_setNum++;
		m_box[setNum] = FindGO<Box>(BOX_NAME);
		m_box[setNum] = NewGO<Box>(0, BOX_NAME);
		m_box[setNum]->SetBoxPos(OBJECTS_POS[setNum], setNum);

	}
}
void Objects::Update() {
	for (int Num = 0; Num < m_setNum; Num++) {
		if (m_delFlag[Num] == true) {
			m_reSpawnTime[Num] += 1.0f;
			if (m_reSpawnTime[Num] >= 100.0f) {
				m_box[Num] = NewGO<Box>(0, BOX_NAME);
				m_box[Num]->SetBoxPos(OBJECTS_POS[Num], Num);
				m_delFlag[Num] = false;
				m_reSpawnTime[Num] = 0.0f;
			}
		}
	}
}
