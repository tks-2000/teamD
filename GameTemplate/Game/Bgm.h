#pragma once

class CSoundSource;

class Bgm : public IGameObject
{
private:
	CSoundSource* m_bgm = nullptr;

	enum enBgmStatus {
		enTitleBgm,
		enMenuBgm,
		enGameBgm,
		enResultBgm
	};

	/// @brief どんなBGMを流すかのステータス
	enBgmStatus m_bgmStat = enTitleBgm;

	/// @brief BGMの音量
	float m_bgmVolume = 0.0f;

public:
	Bgm();
	~Bgm();
	bool Start();
	void Update();
	void BgmStop() { m_bgm->Stop(); }
	/// @brief タイトル画面のBGMを流す
	void ChangeTitleBgm() { m_bgmStat = enTitleBgm; m_bgm->Stop(); }
	/// @brief メニュー画面のBGMを流す
	void ChangeMenuBgm() { m_bgmStat = enMenuBgm; m_bgm->Stop(); }
	/// @brief ゲーム中のBGMを流す
	void ChangeGameBgm() { m_bgmStat = enGameBgm; m_bgm->Stop(); }
	/// @brief リザルト中のBGMを流す
	void ChangeResultBgm() { m_bgmStat = enResultBgm; m_bgm->Stop(); }
};

