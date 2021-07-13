#include "stdafx.h"
#include "Se.h"
#include "SoundSource.h"


namespace {
	//�t�@�C���p�X�e��
	//�I��
	const wchar_t* SELECT_KEY_SE_FILEPATH = L"Assets/sound/se/SelectKey.wav";
	//����
	const wchar_t* PRESS_KEY_SE_FILEPATH = L"Assets/sound/se/press_key.wav";
	//�����J�n
	const wchar_t* COUNT_DOWN_SE_FILEPATH = L"Assets/sound/se/CountDown.wav";
	//�����I��
	const wchar_t* END_SE_FILEPATH = L"Assets/sound/se/End.wav";
	//�L�b�N��
	const wchar_t* KICK_SE_FILEPATH = L"Assets/sound/se/kick_2.wav";
	//�����L�b�N��
	const wchar_t* KICK_POWERED_SE_FILEPATH = L"Assets/sound/se/attack_hi.wav";
	//�V�[���h�W�J
	const wchar_t* GUARD_START_SE_FILEPATH = L"Assets/sound/se/GuardStart.wav";
	//�V�[���h����
	const wchar_t* GUARD_END_SE_FILEPATH = L"Assets/sound/se/GuardEnd.wav";
	//�W���X�g�K�[�h
	const wchar_t* JUSTGUARD_SE_FILEPATH = L"Assets/sound/se/shield_just.wav";
	//�V�[���h��
	const wchar_t* SHIELDREPAIR_SE_FILEPATH = L"Assets/sound/se/charge_2.wav";
	//�V�[���h���q�b�g
	const wchar_t* SHIELDHIT_SE_FILEPATH = L"Assets/sound/se/shield_2.wav";
	//�V�[���h�u���C�N
	const wchar_t* SHIELDBREAK_SE_FILEPATH = L"Assets/sound/se/shield_1.wav";
	//�ǔ���
	const wchar_t* REFLECT_SE_FILEPATH = L"Assets/sound/se/metal_2.wav";
	//�Փ�(��)
	const wchar_t* WEAK_COLLIDE_SE_FILEPATH = L"Assets/sound/se/WeakCollide.wav";
	//�Փ�(��)
	const wchar_t* STRONG_COLLIDE_SE_FILEPATH = L"Assets/sound/se/StrongCollide.wav";
	//�Փ�(��)
	const wchar_t* BOX_COLLIDE_SE_FILEPATH = L"Assets/sound/se/BoxCollide.wav";
	//�����J��
	const wchar_t* BOX_OPEN_SE_FILEPATH = L"Assets/sound/se/BoxOpen.wav";
	//�s���s�\
	const wchar_t* STAN_SE_FILEPATH = L"Assets/sound/se/Stan.wav";
	//�X�^�~�i�؂�
	const wchar_t* STAMINA_OVER_SE_FILEPATH = L"Assets/sound/se/StaminaOver.wav";
	//�X�^�~�i��
	const wchar_t* STAMINA_RECOVERY_SE_FILEPATH = L"Assets/sound/se/StaminaRecovery.wav";
	//�A�C�e������
	const wchar_t* ITEM_GET_SE_FILEPATH = L"Assets/sound/se/ItemGet.wav";
	//���j
	const wchar_t* DEFEAT_SE_FILEPATH = L"Assets/sound/se/Defeat.wav";
	//���X�|�[��
	const wchar_t* RESPAWN_SE_FILEPATH = L"Assets/sound/se/ReSpawn.wav";
	//���ʕ\��
	const wchar_t* RANKING_SE_FILEPATH = L"Assets/sound/se/Ranking.wav";
	//����
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

/// @brief SE�͂��̂悤��Play�֐�������čĐ�����ꏊ��SE�N���X����Ăяo���ĉ������B
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