#include "stdafx.h"
#include "Bgm.h"

namespace {
	const wchar_t* TITLEBGM_FILEPATH = L"Assets/sound/bgm/title.wav";
	const wchar_t* MENUBGM_FILEPATH = L"Assets/sound/bgm/Menu.wav";
	const wchar_t* GAMEBGM_FILEPATH = L"Assets/sound/bgm/MainBgm.wav";
	const wchar_t* SPECIALBGM_FILEPATH  = L"Assets/sound/bgm/SpecialBgm.wav";
	const wchar_t* RESULTBGM_FILEPATH = L"Assets/sound/bgm/Result.wav";

	const float BGM_VOLUME = 1.0f;
}

Bgm::Bgm()
{
	m_bgm = NewGO<CSoundSource>(0);
	m_bgmVolume = BGM_VOLUME;
	m_bgmFilePath = GAMEBGM_FILEPATH;

}

Bgm::~Bgm()
{
	DeleteGO(m_bgm);
}

bool Bgm::Start()
{

	return true;
}

void Bgm::ChangeNormalBgm()
{
	m_bgmFilePath = GAMEBGM_FILEPATH;
}

void Bgm::ChangeSpecialBgm()
{
	m_bgmFilePath = SPECIALBGM_FILEPATH;
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
			m_bgm->Init(m_bgmFilePath);
			m_bgm->SetVolume(m_bgmVolume);
			m_bgm->Play(true);
		}
	}break;
	case enResultBgm: {
		if (m_bgm->IsPlaying() == false) {
			m_bgm->Init(RESULTBGM_FILEPATH);
			m_bgm->SetVolume(m_bgmVolume);
			m_bgm->Play(true);
		}
	}break;

	default:
		break;
	}
}