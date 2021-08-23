#include "stdafx.h"
#include "PlayerReinforcement.h"


namespace {

}

PlayerReinforcement::PlayerReinforcement()
{

}

PlayerReinforcement::~PlayerReinforcement()
{

}

bool PlayerReinforcement::Start()
{

	return true;
}

void PlayerReinforcement::SetPlayerNumber(const int num) {
	m_playerNumber = num;

	m_player = FindGO<Player>(PLAYER_NAME[m_playerNumber]);
}

void PlayerReinforcement::Update()
{

}

bool PlayerReinforcement::IsKickUp() const
{
	if (m_itemPowerUpState == enKickUp) {
		return true;
	}
	else {
		return false;
	}
}

bool PlayerReinforcement::IsDefenseUp() const
{
	if (m_itemPowerUpState == enDefenseUp) {
		return true;
	}
	else {
		return false;
	}
}

bool PlayerReinforcement::IsSpeedUp() const
{
	if (m_itemPowerUpState == enSpeedUp) {
		return true;
	}
	else {
		return false;
	}
}