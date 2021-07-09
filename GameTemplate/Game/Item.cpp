#include "stdafx.h"
#include "Item.h"

Item::Item()
{
	
	m_newGoFlag = false;
}

Item::~Item()
{
	DeleteGO(m_skinModelRender);
}

bool Item::Start()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_objects = FindGO<Objects>(OBJECTS_NAME);
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_player[plNum] = FindGO<Player>(PLAYER_NAME[plNum]);
	}
	return true;
}

void Item::ItemModelNewGO()
{
	switch (m_itemState)
	{
	case enAttackUp: {
		m_skinModelRender = NewGO<SkinModelRender>(PRIORITY_VERYLOW);
		m_skinModelRender->Init("Assets/modelData/item/item_attackup.tkm");
	}break;
	case enGuardUp: {
		m_skinModelRender = NewGO<SkinModelRender>(PRIORITY_VERYLOW);
		m_skinModelRender->Init("Assets/modelData/item/item_guardup.tkm");
	}break;
	default: {
		m_skinModelRender = NewGO<SkinModelRender>(PRIORITY_VERYLOW);
		m_skinModelRender->Init("Assets/modelData/item/item_speedup.tkm");
	}break;
	}
	
}

void Item::Update()
{
	PlayerDistanceCalculation();
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		if (m_distance[plNum] < 50.0f) {
			m_objects->SetItemDelFlag(m_myNo);
			DeleteGO(this);
			break;
		}
	}

	if (m_newGoFlag == true) {
		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetRotation(m_qRot);
	}
}

void Item::PlayerDistanceCalculation()
{
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_toPos[plNum] = m_player[plNum]->GetPosition() - m_position;
		m_distance[plNum] = m_toPos[plNum].Length();
	}
}