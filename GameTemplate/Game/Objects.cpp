#include "stdafx.h"
#include "Objects.h"

namespace {
	const Vector3 SCALE = { 1.0f,1.0f,1.0f };
	const int MAX_OBJECTS_NUM = 4;
	const Vector3 OBJECTS_POS[MAX_OBJECTS_NUM] = { {0.0f,1000.0f,400.0f},{0.0f,1000.0f,-400.0f},{400.0f,1000.0f,0.0f},{-400.0f,1000.0f,0.0f} };
	const float BALL_DISTANCE = 120.0f;
	const float RESPAWN_TIME = 600.0f;
}
Objects::Objects() {
	m_setUp = false;
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

	m_se = FindGO<Se>(SE_NAME);
	return true;
}
void Objects::SetObjects(int num) {
	for (int setNum = 0; setNum < num; setNum++) {
		//m_colliderPos[setNum] = { 0.0f,800.0f,0.0f };
		m_setNum++;
		m_box[setNum] = NewGO<Box>(0, BOX_NAME);
		m_box[setNum]->SetBoxPos(OBJECTS_POS[setNum], setNum);
		
		m_boxOpenFlag[setNum] = false;
		m_delFlag[setNum] = false;
		m_itemCanSpawnFlag[setNum] = true;
		m_itemDelFlag[setNum] = true;
		/*m_item[setNum] = NewGO<Item>(PRIORITY_VERYLOW, ITEM_NAME);
		m_item[setNum]->SetNumber(setNum);
		m_item[setNum]->SetPosition(m_box[setNum]->GetBoxPos());
		int itemNo = rand() % enItemNum;
		switch (itemNo)
		{
		case 0: {
			m_item[setNum]->SetItem(enAttackUp);
		}break;
		case 1: {
			m_item[setNum]->SetItem(enGuardUp);
		}break;
		case 2: {
			m_item[setNum]->SetItem(enVelocityUp);
		}break;
		default:{
		}break;
		}*/
	}
	m_setUp = true;
}

void Objects::Update()
{
	if (m_setUp == false) {
		return;
	}

	for (int Num = 0; Num < m_setNum; Num++) {

		//箱が開いていてアイテムが出せる場合…
		if (m_boxOpenFlag[Num] == true && m_itemCanSpawnFlag[Num] == true) {
			//アイテムを出現させる
			m_item[Num] = NewGO<Item>(PRIORITY_VERYLOW, ITEM_NAME);
			m_item[Num]->SetNumber(Num);
			m_item[Num]->SetPosition(m_box[Num]->GetBoxPos());
			int itemNo = rand() % enItemNum;
			switch (itemNo)
			{
			case 1: {
				m_item[Num]->SetItem(enVelocityUp);
			}break;
			case 2: {
				m_item[Num]->SetItem(enGuardUp);
			}break;
			default: {
				m_item[Num]->SetItem(enAttackUp);
			}break;
			}

			m_itemCanSpawnFlag[Num] = false;
			m_itemDelFlag[Num] = false;
		}

		//箱が消えてアイテムも消えたとき…
		if (m_delFlag[Num] == true && m_itemDelFlag[Num] == true) {
			
			m_reSpawnTime[Num] += 1.0f;
			if (m_reSpawnTime[Num] >= RESPAWN_TIME && m_gameDirector->IsMainGame() == true) {
				m_box[Num] = NewGO<Box>(0, BOX_NAME);
				m_box[Num]->SetBoxPos(OBJECTS_POS[Num], Num);
				
				m_itemSpownPos[Num] = m_box[Num]->GetBoxPos();
				m_delFlag[Num] = false;
				m_reSpawnTime[Num] = 0.0f;
				m_boxOpenFlag[Num] = false;
				m_itemCanSpawnFlag[Num] = true;
				m_se->PlayFallSe();
			}
		}
		
	}
}
