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

/// @brief SE�͂��̂悤��Play�֐�������čĐ�����ꏊ��SE�N���X����Ăяo���ĉ������B
void Se::PlayPressKeySe()
{
	CSoundSource* pressKeySe = NewGO<CSoundSource>(0);
	pressKeySe->Init(PRESS_KEYSE_FILEPATH);
	pressKeySe->SetVolume(m_seVolume);
	pressKeySe->Play(false);
}