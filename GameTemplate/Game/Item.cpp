#include "stdafx.h"
#include "Item.h"

namespace {
	const float MAX_HEIGHT = 50.0f;
	const float MIN_HEIGHT = 0.0f;
	const float ITEM_GET_DISTANCE = 50.0f;
	const float ITEM_VELOCITY = 50.0f;
}

Item::Item()
{
	m_angle = FLOAT_0;
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
		if (m_distance[plNum] < ITEM_GET_DISTANCE) {
			m_objects->SetItemDelFlag(m_myNo);
			switch (m_itemState)
			{
			case enAttackUp: {
				m_player[plNum]->KickPowerUp();
			}break;
			case enGuardUp: {
				m_player[plNum]->GuardPowerUp();
			}break;
			case enSpeedUp: {
				m_player[plNum]->SpeedPowerUp();
			}break;
			default:
				break;
			}
			DeleteGO(this);
			break;
		}
	}

	if (m_objects->IsBoxOpen(m_myNo) == true) {
		if (m_moveChange == false) {
			m_posHeight += g_gameTime->GetFrameDeltaTime() * ITEM_VELOCITY;
		}
		else {
			m_posHeight -= g_gameTime->GetFrameDeltaTime() * ITEM_VELOCITY;
		}
		if (m_posHeight > MAX_HEIGHT) {
			m_moveChange = true;
		}

		if (m_posHeight < MIN_HEIGHT) {
			m_moveChange = false;
		}
	}

	Vector3 modelPos = m_position;
	modelPos.y += m_posHeight;

	m_angle += g_gameTime->GetFrameDeltaTime();
	m_qRot.SetRotationY(m_angle);

	if (m_newGoFlag == true) {
		m_skinModelRender->SetPosition(modelPos);
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