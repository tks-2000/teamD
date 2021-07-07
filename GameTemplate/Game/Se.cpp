#include "stdafx.h"
#include "Se.h"

namespace {
	//ファイルパス各種
	//決定
	const wchar_t* PRESS_KEYSE_FILEPATH = L"Assets/sound/se/press_key.wav";
	//キック時
	const wchar_t* KICK_SE_FILEPATH = L"Assets/sound/se/kick_2.wav";
	//強化キック時
	const wchar_t* KICK_POWERED_SE_FILEPATH = L"Assets/sound/se/attack_hi.wav";
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




}

Se::Se()
{

}

Se::~Se()
{

}

bool Se::Start()
{

	return true;
}

void Se::Update()
{

}

/// @brief SEはこのようにPlay関数を作って再生する場所でSEクラスから呼び出して下さい。
void Se::PlayPressKeySe()
{
	CSoundSource* pressKeySe = NewGO<CSoundSource>(0);
	pressKeySe->Init(PRESS_KEYSE_FILEPATH);
	pressKeySe->SetVolume(m_seVolume);
	pressKeySe->Play(false);
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

