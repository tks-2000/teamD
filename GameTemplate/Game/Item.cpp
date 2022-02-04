#include "stdafx.h"
#include "Item.h"

namespace {
	const float MAX_HEIGHT = 50.0f;
	const float MIN_HEIGHT = 0.0f;
	const float ITEM_GET_DISTANCE = 70.0f;
	const float ITEM_VELOCITY = 20.0f;

	//�G�t�F�N�g�̃t�@�C���p�X
	const char16_t* ITEMEFFECT_FILEPATH[PLAYER_NUM] = { 
		{u"Assets/effect/itemAura_red.efk"},
		{u"Assets/effect/itemAura_blue.efk"},
		{u"Assets/effect/itemAura_yellow.efk"}
	};
	const Vector3 ITEMEFFECT_SCALE = { 8.0f,8.0f,8.0f };
	//�G�t�F�N�g�������x�̃I�t�Z�b�g�l
	const float ITEMEFFECT_OFFSET_Y = 20.0f;
	//�G�t�F�N�g�Đ��\�t���O�𗧂Ă邽�߂̍��x
	const float ITEMEFFECT_PLAYHEIGHT = 10.0f;
	//�G�t�F�N�g�Đ�����(�Ⴂ�قǑ�������)
	const int ITEMEFFECT_PLAYCYCLE = 6;
}

Item::Item()
{
	m_angle = 0.0f;
	m_newGoFlag = false;
	m_setUp = false;
	m_getData = false;
	m_posHeight = 0.0f;
}

Item::~Item()
{
	DeleteGO(m_skinModelRender);
}

bool Item::Start()
{
	//���݃G�t�F�N�g�̏�����
	m_itemBeingEffect.Init(ITEMEFFECT_FILEPATH[m_itemState]);

	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_se = FindGO<Se>(SE_NAME);
	m_objects = FindGO<Objects>(OBJECTS_NAME);
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_player[plNum] = FindGO<Player>(PLAYER_NAME[plNum]);
	}

	m_setUp = true;
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
	m_skinModelRender->SetPosition(m_position);
}

void Item::PlayBeingEffect()
{
	Vector3 efcPos = Vector3::Zero;
	efcPos = m_position;
	efcPos.y = m_posHeight;
	//efcPos.y += ITEMEFFECT_OFFSET_Y;

	m_itemBeingEffect.Play();
	m_itemBeingEffect.SetPosition(efcPos);
	m_itemBeingEffect.SetScale(ITEMEFFECT_SCALE);
	m_itemBeingEffect.Update();

}

void Item::Update()
{
	

	if (m_setUp == false) {
		return;
	}

	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		if (m_player[plNum]->IsSetUp() == false) {
			return;
		}
	}
	if (m_getData == false) {
		for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
			m_plReinforcement[plNum] = FindGO<PlayerReinforcement>(PLAYER_REINFORCEMENT_NAME[plNum]);
		}
		m_getData = true;
		return;
	}

	PlayerDistanceCalculation();
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
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

			if (m_distance[plNum] < ITEM_GET_DISTANCE) {
				m_objects->SetItemDelFlag(m_myNo);
				m_se->PlayItemGetSe();
				switch (m_itemState)
				{
				case enAttackUp: {
					//m_player[plNum]->KickPowerUp();
					m_plReinforcement[plNum]->ChangeKickPowerUp();
				}break;
				case enGuardUp: {
					//m_player[plNum]->GuardPowerUp();
					m_plReinforcement[plNum]->ChangeDefenseUp();
				}break;
				case enVelocityUp: {
					//m_player[plNum]->SpeedPowerUp();
					m_plReinforcement[plNum]->ChangeSpeedUp();
				}break;
				default:
					break;
				}
				DeleteGO(this);
				break;
			}
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

	if (m_position.y < ITEMEFFECT_PLAYHEIGHT) {
		m_isValidEffectPlay = true;
	}

	//���݃G�t�F�N�g�Đ�����
	m_itemBeingCounter += 1;
	if (m_itemBeingCounter > 60) {
		m_itemBeingCounter = 0;
	}
	//�Đ��\�ɂȂ�����Đ�
	//if (m_isValidEffectPlay == true) {
		if (m_itemBeingCounter % ITEMEFFECT_PLAYCYCLE == 1) {
			PlayBeingEffect();
		}
	//}
}

void Item::PlayerDistanceCalculation()
{
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_toPos[plNum] = m_player[plNum]->GetPosition() - m_position;
		m_distance[plNum] = m_toPos[plNum].Length();
	}
}