#pragma once

class CSoundSource;
class GameDirector;

const int PLNUM = 4;

class Se : public IGameObject
{
private:
	float m_seVolume = 1.0f;

	CSoundSource* m_stanSe[PLNUM] = { nullptr };

	GameDirector* m_gameDirector = nullptr;

public:
	Se();
	~Se();
	bool Start();
	void Update();

	//�R�}���h�I��
	void PlaySelectKeySe();
	//�R�}���h����
	void PlayPressKeySe();
	//�����J�n�̃J�E���g
	void PlayCountDownSe();
	//�����I��
	void PlayEndSe();
	//�L�b�N��
	void PlayKickSe();
	//�������L�b�N
	void PlayPoweredKickSe();
	//�V�[���h�W�J
	void PlayGuardStartSe();
	//�V�[���h����
	void PlayGuardEndSe();
	//�W���X�g�K�[�h
	void PlayJustGuardSe();
	//�V�[���h��
	void PlayShieldRepairSe();
	//�V�[���h���q�b�g
	void PlayShieldHitSe();
	//�V�[���h�u���C�N
	void PlayBreakSe();
	//�ǔ���
	void PlayReflectSe();
	//�{�[���ɏՓ�(��)
	void PlayWeakCollideSe();
	//�{�[���ɏՓ�(��)
	void PlayStrongCollideSe();
	//���ɏՓ�
	void PlayBoxCollideSe();
	//�����J��
	void PlayBoxOpenSe();
	//�s���s�\
	void PlayStanSe(int plNum);
	//�s���s�\��~
	void StopStanSe(int plNum) { m_stanSe[plNum]->Stop(); }
	//�X�^�~�i�؂�
	void PlayStaminaOverSe();
	//�X�^�~�i��
	void PlayStaminaRecoverySe();
	//�A�C�e������
	void PlayItemGetSe();
	//���j
	void PlayDefeatSe();
	//���X�|�[��
	void PlayReSpawnSe();
	//���ʕ\��
	void PlayRankingSe();
	//����
	void PlayCheersSe();
};

