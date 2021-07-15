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

	/// @brief �ǂ��BGM�𗬂����̃X�e�[�^�X
	enBgmStatus m_bgmStat = enTitleBgm;

	/// @brief BGM�̉���
	float m_bgmVolume = 0.0f;

	const wchar_t* m_bgmFilePath = nullptr;

public:
	Bgm();
	~Bgm();
	bool Start();
	void Update();
	void BgmStop() { m_bgm->Stop(); }
	/// @brief �^�C�g����ʂ�BGM�𗬂�
	void ChangeTitleBgm() { m_bgmStat = enTitleBgm; m_bgm->Stop(); }
	/// @brief ���j���[��ʂ�BGM�𗬂�
	void ChangeMenuBgm() { m_bgmStat = enMenuBgm; m_bgm->Stop(); }
	/// @brief �Q�[������BGM�𗬂�
	void ChangeGameBgm() { m_bgmStat = enGameBgm; m_bgm->Stop(); }
	/// @brief ���U���g����BGM�𗬂�
	void ChangeResultBgm() { m_bgmStat = enResultBgm; m_bgm->Stop(); }

	void ChangeNormalBgm();

	void ChangeSpecialBgm();
};

