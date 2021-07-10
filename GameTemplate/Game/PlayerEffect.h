#pragma once

class GameDirector;
class Player;
class Effect;

class PlayerEffect : public IGameObject
{
private:
	//�G�t�F�N�g�֘A//
	/// @brief �{�[�����L�b�N�������̃G�t�F�N�g
	Effect m_kickEffect[PLAYER_NUMBER];
	/// @brief �K�[�h���̃G�t�F�N�g
	Effect m_guardEffect[PLAYER_NUMBER];
	Vector3 m_guardEffectPos[PLAYER_NUMBER] = { Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero };
	//�K�[�h�G�t�F�N�g�����Ԋu�Ŕ��������邽�߂̃J�E���^�[
	int m_guardEffectCouter = 0;
	/// @brief �K�[�h�����̗\���G�t�F�N�g
	Effect m_guardBeginEffect[PLAYER_NUMBER];
	/// @brief �K�[�h�u���C�N�G�t�F�N�g
	Effect m_guardBreakEffect[PLAYER_NUMBER];
	/// @brief �V�[���h�񕜃G�t�F�N�g
	Effect m_shieldRepairEffect[PLAYER_NUMBER];
	/// @brief �V�[���h�q�b�g�G�t�F�N�g
	Effect m_shieldHitEffect[PLAYER_NUMBER];
	/// @brief �K�[�h�q�b�g�G�t�F�N�g�����Ԋu�Ŕ��������邽�߂̃J�E���^�[
	int m_shieldHitEffectCounter = 0;
	//�s���s�\���G�t�F�N�g(�s����)
	Effect m_knockOutEffect[PLAYER_NUMBER];
	//�W���X�g�K�[�h�G�t�F�N�g
	Effect m_justGuardEffect[PLAYER_NUMBER];
	/// @brief �W���X�g�K�[�h���̃v���C���[�����G�t�F�N�g
	Effect m_kickBuffEffect[PLAYER_NUMBER];
	/// @brief �_���[�W����̉񕜃G�t�F�N�g
	Effect m_repairEffect[PLAYER_NUMBER];
	/// @brief ���X�|�[�����̃G�t�F�N�g
	Effect m_respawnEffect[PLAYER_NUMBER];
	/// @brief �_���[�W�G�t�F�N�g
	Effect m_damageEffect[PLAYER_NUMBER];


	GameDirector* m_gameDirector = nullptr;
	Player* m_player[PLAYER_NUMBER] = { nullptr };
	Ball* m_ball = nullptr;

	/// @brief �K�[�h�n�G�t�F�N�g�̋��ʍ��W
	Vector3 m_efcGuardPos[PLAYER_NUMBER] = { { Vector3::Zero },{ Vector3::Zero },{ Vector3::Zero },{ Vector3::Zero } };

	/// @brief �K�[�h�\���G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void GuardBeginEffectUpdate(int plNum);

	/// @brief �K�[�h�G�t�F�N�g�̍X�V
	/// @param plnum �X�V����v���C���[�ԍ�
	void GuardEffectUpdate(int plNum);

	/// @brief �V�[���h�񕜃G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void ShieldRepairEffectUpdate(int plNum);

	/// @brief �s���s�\�G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void KnockOutEffectUpdate(int plNum);

	/// @brief �����G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void KickBuffEffectUpdate(int plNum);

	/// @brief �_���[�W�񕜃G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void RepairEffectUpdate(int plNum);

	/// @brief ���X�|�[�����̃G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void RespawnEffectUpdate(int plNum);

public:
	
	PlayerEffect();
	~PlayerEffect();
	bool Start();
	void Update();
	/// @brief �L�b�N�G�t�F�N�g���Đ�
	/// @param plnum �Đ�����v���C���[�ԍ�
	void PlayKickEffect(int plNum);

	/// @brief �K�[�h�\���G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayGuardBeginEffect(int plNum) { m_guardBeginEffect[plNum].Play(); }
	

	/// @brief �K�[�h�G�t�F�N�g���Đ�
	/// @param plnum �Đ�����v���C���[�ԍ�
	void PlayGuardEffect(int plNum) { m_guardEffect[plNum].Play(); }
	/// @brief �K�[�h�G�t�F�N�g���~
	/// @param plnum ��~����v���C���[�ԍ�
	void StopGuardEffect(int plNum) { m_guardEffect[plNum].Stop(); }
	
	/// @brief �K�[�h�u���C�N�G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayGuardBreakEffect(int plNum);

	/// @brief �W���X�g�K�[�h�G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayJustGuardEffect(int plNum);

	/// @brief �V�[���h�q�b�g�G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayShieldHitEffect(int plNum);

	/// @brief �V�[���h�񕜃G�t�F�N�g�̍Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayShieldRepairEffect(int plNum) { m_shieldRepairEffect[plNum].Play(); }

	/// @brief �s���s�\�G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayKnockOutEffect(int plNum) { m_knockOutEffect[plNum].Play(); }

	/// @brief �s���s�\�G�t�F�N�g���~
	/// @param plNum ��~����v���C���[�ԍ�
	void StopKnockOutEffect(int plNum) { m_knockOutEffect[plNum].Stop(); }
	
	/// @brief �v���C���[�����G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayKickBuffEffect(int plNum) { m_kickBuffEffect[plNum].Play(); }

	/// @brief �_���[�W����̉񕜃G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayRepairEffect(int plNum) { m_repairEffect[plNum].Play(); }
	
	/// @brief �_���[�W�G�t�F�N�g���Đ�
	/// @param plNum 
	void PlayDamageEffect(int plNum);

	/// @brief ���X�|�[�����̃G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayRespawnEffect(int plNum) { m_respawnEffect[plNum].Play(); }

};

