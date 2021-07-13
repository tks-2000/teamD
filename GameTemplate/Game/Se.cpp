#include "stdafx.h"
#include "Se.h"
#include "SoundSource.h"


namespace {
	//ファイルパス各種
	//選択
	const wchar_t* SELECT_KEY_SE_FILEPATH = L"Assets/sound/se/SelectKey.wav";
	//決定
	const wchar_t* PRESS_KEY_SE_FILEPATH = L"Assets/sound/se/press_key.wav";
	//試合開始
	const wchar_t* COUNT_DOWN_SE_FILEPATH = L"Assets/sound/se/CountDown.wav";
	//試合終了
	const wchar_t* END_SE_FILEPATH = L"Assets/sound/se/End.wav";
	//キック時
	const wchar_t* KICK_SE_FILEPATH = L"Assets/sound/se/kick_2.wav";
	//強化キック時
	const wchar_t* KICK_POWERED_SE_FILEPATH = L"Assets/sound/se/attack_hi.wav";
	//シールド展開
	const wchar_t* GUARD_START_SE_FILEPATH = L"Assets/sound/se/GuardStart.wav";
	//シールド解除
	const wchar_t* GUARD_END_SE_FILEPATH = L"Assets/sound/se/GuardEnd.wav";
	//ジャストガード
	const wchar_t* JUSTGUARD_SE_FILEPATH = L"Assets/sound/se/shield_just.wav";
	//シールド回復
	const wchar_t* SHIELDREPAIR_SE_FILEPATH = L"Assets/sound/se/charge_2.wav";
	//シールド時ヒット
	const wchar_t* SHIELDHIT_SE_FILEPATH = L"Assets/sound/se/shield_2.wav";
	//シールドブレイク
	const wchar_t* SHIELDBREAK_SE_FILEPATH = L"Assets/sound/se/shield_1.wav";
	//壁反射
	const wchar_t* REFLECT_SE_FILEPATH = L"Assets/sound/se/metal_2.wav";
	//衝突(弱)
	const wchar_t* WEAK_COLLIDE_SE_FILEPATH = L"Assets/sound/se/WeakCollide.wav";
	//衝突(強)
	const wchar_t* STRONG_COLLIDE_SE_FILEPATH = L"Assets/sound/se/StrongCollide.wav";
	//衝突(箱)
	const wchar_t* BOX_COLLIDE_SE_FILEPATH = L"Assets/sound/se/BoxCollide.wav";
	//箱が開く
	const wchar_t* BOX_OPEN_SE_FILEPATH = L"Assets/sound/se/BoxOpen.wav";
	//行動不能
	const wchar_t* STAN_SE_FILEPATH = L"Assets/sound/se/Stan.wav";
	//スタミナ切れ
	const wchar_t* STAMINA_OVER_SE_FILEPATH = L"Assets/sound/se/StaminaOver.wav";
	//スタミナ回復
	const wchar_t* STAMINA_RECOVERY_SE_FILEPATH = L"Assets/sound/se/StaminaRecovery.wav";
	//アイテム入手
	const wchar_t* ITEM_GET_SE_FILEPATH = L"Assets/sound/se/ItemGet.wav";
	//撃破
	const wchar_t* DEFEAT_SE_FILEPATH = L"Assets/sound/se/Defeat.wav";
	//リスポーン
	const wchar_t* RESPAWN_SE_FILEPATH = L"Assets/sound/se/ReSpawn.wav";
	//順位表示
	const wchar_t* RANKING_SE_FILEPATH = L"Assets/sound/se/Ranking.wav";
	//歓声
	const wchar_t* CHEER_SE_FILEPATH = L"Assets/sound/se/Cheer.wav";

}

Se::Se()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	for (int plNum = 0; plNum < MAX_PLAYER_NUM; plNum++) {
		m_stanSe[plNum] = NewGO<CSoundSource>(PRIORITY_VERYLOW);
		m_stanSe[plNum]->Init(STAN_SE_FILEPATH);
	}

}

Se::~Se()
{
	for (int plNum = 0; plNum < MAX_PLAYER_NUM; plNum++) {
		DeleteGO(m_stanSe[plNum]);
	}
}

bool Se::Start()
{
	
	return true;
}

void Se::Update()
{

}

void Se::PlaySelectKeySe()
{
	CSoundSource* selectKeySe = NewGO<CSoundSource>(0);
	selectKeySe->Init(SELECT_KEY_SE_FILEPATH);
	selectKeySe->SetVolume(m_seVolume);
	selectKeySe->Play(false);
}

/// @brief SEはこのようにPlay関数を作って再生する場所でSEクラスから呼び出して下さい。
void Se::PlayPressKeySe()
{
	CSoundSource* pressKeySe = NewGO<CSoundSource>(0);
	pressKeySe->Init(PRESS_KEY_SE_FILEPATH);
	pressKeySe->SetVolume(m_seVolume);
	pressKeySe->Play(false);
}

void Se::PlayCountDownSe()
{
	CSoundSource* countDownSe = NewGO<CSoundSource>(0);
	countDownSe->Init(COUNT_DOWN_SE_FILEPATH);
	countDownSe->SetVolume(m_seVolume);
	countDownSe->Play(false);
}

void Se::PlayEndSe()
{
	CSoundSource* endSe = NewGO<CSoundSource>(0);
	endSe->Init(END_SE_FILEPATH);
	endSe->SetVolume(m_seVolume);
	endSe->Play(false);
}

void Se::PlayKickSe()
{
	CSoundSource* kickSe = NewGO<CSoundSource>(0);
	kickSe->Init(KICK_SE_FILEPATH);
	kickSe->SetVolume(1.0f);
	kickSe->Play(false);
}

void Se::PlayPoweredKickSe()
{
	CSoundSource* kickPoweredSe = NewGO<CSoundSource>(0);
	kickPoweredSe->Init(KICK_POWERED_SE_FILEPATH);
	kickPoweredSe->SetVolume(1.0f);
	kickPoweredSe->Play(false);
}

void Se::PlayGuardStartSe()
{
	CSoundSource* guardStart = NewGO<CSoundSource>(0);
	guardStart->Init(GUARD_START_SE_FILEPATH);
	guardStart->SetVolume(1.0f);
	guardStart->Play(false);
}

void  Se::PlayGuardEndSe()
{
	CSoundSource* guardEnd = NewGO<CSoundSource>(0);
	guardEnd->Init(GUARD_END_SE_FILEPATH);
	guardEnd->SetVolume(2.0f);
	guardEnd->Play(false);
}

void Se::PlayJustGuardSe()
{
	CSoundSource* justGuardSe = NewGO<CSoundSource>(0);
	justGuardSe->Init(JUSTGUARD_SE_FILEPATH);
	justGuardSe->SetVolume(1.0f);
	justGuardSe->Play(false);
}

void Se::PlayShieldRepairSe()
{
	CSoundSource* shieldRepairSe = NewGO<CSoundSource>(0);
	shieldRepairSe->Init(SHIELDREPAIR_SE_FILEPATH);
	shieldRepairSe->SetVolume(1.0f);
	shieldRepairSe->Play(false);
}

void Se::PlayShieldHitSe()
{
	CSoundSource* shieldHitSe = NewGO<CSoundSource>(0);
	shieldHitSe->Init(SHIELDHIT_SE_FILEPATH);
	shieldHitSe->SetVolume(1.0f);
	shieldHitSe->Play(false);
}

void Se::PlayBreakSe()
{
	CSoundSource* shieldBreakSe = NewGO<CSoundSource>(0);
	shieldBreakSe->Init(SHIELDBREAK_SE_FILEPATH);
	shieldBreakSe->SetVolume(2.0f);
	shieldBreakSe->Play(false);
}

void Se::PlayReflectSe()
{
	CSoundSource* reflectSe = NewGO<CSoundSource>(0);
	reflectSe->Init(REFLECT_SE_FILEPATH);
	reflectSe->SetVolume(1.0f);
	reflectSe->Play(false);
}

void Se::PlayWeakCollideSe()
{
	CSoundSource* weakCollideSe = NewGO<CSoundSource>(0);
	weakCollideSe->Init(WEAK_COLLIDE_SE_FILEPATH);
	weakCollideSe->SetVolume(2.0f);
	weakCollideSe->Play(false);
}

void Se::PlayStrongCollideSe()
{
	CSoundSource* strongCollideSe = NewGO<CSoundSource>(0);
	strongCollideSe->Init(STRONG_COLLIDE_SE_FILEPATH);
	strongCollideSe->SetVolume(3.0f);
	strongCollideSe->Play(false);
}

void Se::PlayBoxCollideSe()
{
	CSoundSource* boxCollideSe = NewGO<CSoundSource>(0);
	boxCollideSe->Init(BOX_COLLIDE_SE_FILEPATH);
	boxCollideSe->SetVolume(1.0f);
	boxCollideSe->Play(false);
}

void Se::PlayBoxOpenSe()
{
	CSoundSource* boxOpeneSe = NewGO<CSoundSource>(0);
	boxOpeneSe->Init(BOX_OPEN_SE_FILEPATH);
	boxOpeneSe->SetVolume(1.0f);
	boxOpeneSe->Play(false);
}

void Se::PlayStanSe(int plNum)
{
	m_stanSe[plNum]->SetVolume(1.0f);
	m_stanSe[plNum]->Play(true);
}

void Se::PlayStaminaOverSe()
{
	CSoundSource* staminaOverSe = NewGO<CSoundSource>(0);
	staminaOverSe->Init(STAMINA_OVER_SE_FILEPATH);
	staminaOverSe->SetVolume(1.0f);
	staminaOverSe->Play(false);
}

void Se::PlayStaminaRecoverySe()
{
	CSoundSource* staminaRecoverySe = NewGO<CSoundSource>(0);
	staminaRecoverySe->Init(STAMINA_RECOVERY_SE_FILEPATH);
	staminaRecoverySe->SetVolume(1.0f);
	staminaRecoverySe->Play(false);
}

void Se::PlayItemGetSe()
{
	CSoundSource* itemGetSe = NewGO<CSoundSource>(0);
	itemGetSe->Init(ITEM_GET_SE_FILEPATH);
	itemGetSe->SetVolume(1.0f);
	itemGetSe->Play(false);
}

void Se::PlayDefeatSe()
{
	CSoundSource* defeatSe = NewGO<CSoundSource>(0);
	defeatSe->Init(DEFEAT_SE_FILEPATH);
	defeatSe->SetVolume(2.0f);
	defeatSe->Play(false);
}

void Se::PlayReSpawnSe()
{
	CSoundSource* reSpawnSe = NewGO<CSoundSource>(0);
	reSpawnSe->Init(RESPAWN_SE_FILEPATH);
	reSpawnSe->SetVolume(1.0f);
	reSpawnSe->Play(false);
}

void Se::PlayRankingSe()
{
	CSoundSource* rankingSe = NewGO<CSoundSource>(0);
	rankingSe->Init(RANKING_SE_FILEPATH);
	rankingSe->SetVolume(1.0f);
	rankingSe->Play(false);
}

void Se::PlayCheersSe()
{
	CSoundSource* CheersSe = NewGO<CSoundSource>(0);
	CheersSe->Init(CHEER_SE_FILEPATH);
	CheersSe->SetVolume(1.0f);
	CheersSe->Play(false);
}