#include "stdafx.h"
#include "Se.h"

namespace {
	const wchar_t* PRESS_KEYSE_FILEPATH = L"Assets/sound/se/press_key.wav";
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