#include "stdafx.h"
#include "Objects.h"

namespace {
	const Vector3 SCALE = { 1.0f,1.0f,1.0f };
	const int MAX_OBJECTS_NUM = 4;
	const Vector3 OBJECTS_POS[MAX_OBJECTS_NUM] = { {350.0f,400.0f,350.0f},{350.0f,400.0f,-350.0f},{-350.0f,400.0f,350.0f},{-350.0f,400.0f,-350.0f} };
	const float BALL_DISTANCE = 120.0f;
	const float RESPAWN_TIME = 600.0f;
}
Objects::Objects() {

	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_ball = FindGO<Ball>(BALL_NAME);

}
Objects::~Objects() {
	for (int Num = 0; Num < m_setNum; Num++) {
		if (m_delFlag[Num] == false) {
			DeleteGO(m_box[Num]);
		}
		if (m_itemDelFlag[Num] == false) {
			DeleteGO(m_item[Num]);
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
		m_box[setNum] = NewGO<Box>(0, BOX_NAME);
		m_box[setNum]->SetBoxPos(OBJECTS_POS[setNum], setNum);
		m_item[setNum] = NewGO<Item>(PRIORITY_VERYLOW, ITEM_NAME);
		m_box[setNum]->SetBoxPos(OBJECTS_POS[setNum], setNum);
		m_item[setNum]->SetNumber(setNum);
		int itemNo = rand() % Item::enItemNum;
		switch (itemNo)
		{
		case 0: {
			m_item[setNum]->SetItem(Item::enAttackUp);
		}break;
		case 1: {
			m_item[setNum]->SetItem(Item::enGuardUp);
		}break;
		case 2: {
			m_item[setNum]->SetItem(Item::enSpeedUp);
		}break;
		default:{
		}break;
		}
	}
}
void Objects::Update() {
	for (int Num = 0; Num < m_setNum; Num++) {
		if (m_delFlag[Num] == true && m_itemDelFlag[Num] == true) {
			m_reSpawnTime[Num] += 1.0f;
			if (m_reSpawnTime[Num] >= RESPAWN_TIME && !m_gameDirector->IsResult()) {
				m_box[Num] = NewGO<Box>(0, BOX_NAME);
				m_box[Num]->SetBoxPos(OBJECTS_POS[Num], Num);
				m_item[Num] = NewGO<Item>(PRIORITY_VERYLOW, ITEM_NAME);
				m_item[Num]->SetNumber(Num);
				switch (Num)
				{
				case 1: {
					m_item[Num]->SetItem(Item::enAttackUp);
				}break;
				case 2: {
					m_item[Num]->SetItem(Item::enGuardUp);
				}break;
				default: {
					m_item[Num]->SetItem(Item::enSpeedUp);
				}break;
				}
				m_delFlag[Num] = false;
				m_reSpawnTime[Num] = ZeroF;
				m_itemDelFlag[Num] = false;
				m_boxOpenFlag[Num] = false;
			}
		}
		if (m_delFlag[Num] == false && m_itemDelFlag[Num] == false) {
			m_item[Num]->SetPosition(m_box[Num]->GetBoxPos());
		}
		
	}
}
