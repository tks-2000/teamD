#pragma once

class CSoundSource;

class Se : public IGameObject
{
private:
	float m_seVolume = 1.0f;

public:
	Se();
	~Se();
	bool Start();
	void Update();

	void PlayPressKeySe();
	//�L�b�N��
	void PlayKickSe();
	//�������L�b�N
	void PlayPoweredKickSe();
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
	


};

