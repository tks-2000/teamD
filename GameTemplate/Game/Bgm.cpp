#include "stdafx.h"
#include "Bgm.h"

namespace {
	const wchar_t* TITLEBGM_FILEPATH = L"Assets/sound/bgm/title.wav";
	const wchar_t* MENUBGM_FILEPATH = L"Assets/sound/bgm/bgm.wav";
	const wchar_t* GAMEBGM_FILEPATH = L"Assets/sound/bgm/normalBGM.wav";

	const float BGM_VOLUME = 1.0f;
}

Bgm::Bgm()
{
	m_bgm = NewGO<CSoundSource>(0);
	m_bgmVolume = BGM_VOLUME;
	

}

Bgm::~Bgm()
{
	DeleteGO(m_bgm);
}

bool Bgm::Start()
{

	return true;
}

void Bgm::Update()
{
	switch (m_bgmStat)
	{
	case enTitleBgm: {
		if (m_bgm->IsPlaying() == false) {
			m_bgm->Init(TITLEBGM_FILEPATH);
			m_bgm->SetVolume(m_bgmVolume);
			m_bgm->Play(true);
		}
	}break;
	case enMenuBgm: {
		if (m_bgm->IsPlaying() == false) {
			m_bgm->Init(MENUBGM_FILEPATH);
			m_bgm->SetVolume(m_bgmVolume);
			m_bgm->Play(true);
		}
	}break;
	case enGameBgm: {
		if (m_bgm->IsPlaying() == false) {
			m_bgm->Init(GAMEBGM_FILEPATH);
			m_bgm->SetVolume(m_bgmVolume);
			m_bgm->Play(true);
		}
	}break;
	case enResultBgm: {

	}break;
	default:
		break;
	}
}