#include "stdafx.h"
#include "PlayerReinforcement.h"


namespace {
	/// @brief 自己強化の時間
	const float SELF_POWERUP_TIME = 10.0f;
	/// @brief アイテムによる強化時間
	const float ITEM_POWERUP_TIME = 10.0f;
}

PlayerReinforcement::PlayerReinforcement()
{
	//準備を開始する
	m_setUp = false;
	//自己強化していない状態で開始
	m_selfPowerUp = false;
	m_selfPowerUpCount = 0.0f;
	//アイテム強化していない状態で開始
	m_itemPowerUpState = enItemPowerUpNum;
	m_itemPowerUpCount = 0.0f;
}

PlayerReinforcement::~PlayerReinforcement()
{

}

bool PlayerReinforcement::Start()
{

	return true;
}

void PlayerReinforcement::Update()
{
	//準備完了していなかったら…
	if (m_setUp == false) {
		//処理を行わない
		return;
	}

	//自己強化フラグが立っていたら…
	if (m_selfPowerUp == true) {
		//自己強化中の処理を行う
		SelfPowerUp();
	}

	//アイテム強化フラグがどれか立っていたら…
	if (m_itemPowerUpState != enItemPowerUpNum) {
		//アイテム強化中の処理を行う
		ItemPowerUp();
	}
}

void PlayerReinforcement::SetPlayerNumber(const int num)
{
	//プレイヤーの番号を設定
	m_playerNumber = num;
	//設定された番号のデータを取得
	m_plEffect = FindGO<PlayerEffect>(PLAYER_EFFECT_NAME[m_playerNumber]);
	//準備完了
	m_setUp = true;
}

bool PlayerReinforcement::IsKickUp() const
{
	//キック強化中ならtrue
	if (m_itemPowerUpState == enKickUp) {
		return true;
	}
	//そうでないならfalse
	else {
		return false;
	}
}

bool PlayerReinforcement::IsDefenseUp() const
{
	//防御強化中ならtrue
	if (m_itemPowerUpState == enDefenseUp) {
		return true;
	}
	//そうでないならfalse
	else {
		return false;
	}
}

bool PlayerReinforcement::IsSpeedUp() const
{
	//速度強化中ならtrue
	if (m_itemPowerUpState == enSpeedUp) {
		return true;
	}
	//そうでないならfalse
	else {
		return false;
	}
}

void PlayerReinforcement::ChangeKickPowerUp()
{
	//アイテム強化状態をキック力強化に変更
	m_itemPowerUpState = enKickUp; 
	//アイテム強化カウントを0にする
	m_itemPowerUpCount = 0.0f;
	//アイテム強化エフェクトをキック力強化中の物に設定
	m_plEffect->ChangeItemBuffEffect(enItemBuff_Kick);
}

void PlayerReinforcement::ChangeDefenseUp()
{
	//アイテム強化状態を防御力強化に変更
	m_itemPowerUpState = enDefenseUp;
	//アイテム強化カウントを0にする
	m_itemPowerUpCount = 0.0f;
	//アイテム強化エフェクトを防御力強化中の物に設定
	m_plEffect->ChangeItemBuffEffect(enItemBuff_Guard);
}

void PlayerReinforcement::ChangeSpeedUp()
{
	//アイテム強化状態を速度強化に変更
	m_itemPowerUpState = enSpeedUp;
	//アイテム強化カウントを0にする
	m_itemPowerUpCount = 0.0f;
	//アイテム強化エフェクトを速度強化中の物に設定
	m_plEffect->ChangeItemBuffEffect(enItemBuff_Speed);
}

void PlayerReinforcement::ReinforcementRelease()
{
	//自己強化状態を解除
	m_selfPowerUp = false;
	//アイテム強化状態を解除
	m_itemPowerUpState = enItemPowerUpNum;
}

void PlayerReinforcement::SelfPowerUp()
{
	//自己強化中のエフェクトを再生
	m_plEffect->PlayKickBuffEffect();
	//自己強化カウントを進める
	m_selfPowerUpCount += g_gameTime->GetFrameDeltaTime();
	//自己強化カウントが時間を超えたら…
	if (m_selfPowerUpCount > SELF_POWERUP_TIME) {
		//自己強化フラグを元に戻す
		m_selfPowerUp = false;
		//自己強化カウントを0にする
		m_selfPowerUpCount = 0.0f;
	}
}

void PlayerReinforcement::ItemPowerUp()
{
	//アイテムによる強化エフェクトを再生
	m_plEffect->PlayItemBuffEffect();

	//アイテム強化カウントを進める
	m_itemPowerUpCount += g_gameTime->GetFrameDeltaTime();

	//アイテム強化カウントが時間を超えたら…
	if (m_itemPowerUpCount > ITEM_POWERUP_TIME) {
		//アイテム強化状態を解除する
		m_itemPowerUpState = enItemPowerUpNum;
		//アイテム強化カウントを0に戻す
		m_itemPowerUpCount = 0.0f;
	}
}