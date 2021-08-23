#pragma once

class GameDirector;
class Player;
class Effect;

class PlayerEffect : public IGameObject
{
private:
	/// @brief �v���C���[�̔ԍ�
	int m_playerNum = 0;
	//�G�t�F�N�g�֘A//
	/// @brief �{�[�����L�b�N�������̃G�t�F�N�g
	Effect m_kickEffect;
	/// @brief �K�[�h���̃G�t�F�N�g
	Effect m_guardEffect;

	Vector3 m_guardEffectPos =  Vector3::Zero;
	//�K�[�h�G�t�F�N�g�����Ԋu�Ŕ��������邽�߂̃J�E���^�[
	int m_guardEffectCouter = 0;
	/// @brief �K�[�h�����̗\���G�t�F�N�g
	Effect m_guardBeginEffect;
	/// @brief �K�[�h�u���C�N�G�t�F�N�g
	Effect m_guardBreakEffect;
	/// @brief �V�[���h�񕜃G�t�F�N�g
	Effect m_shieldRepairEffect;
	/// @brief �V�[���h�q�b�g�G�t�F�N�g
	Effect m_shieldHitEffect;
	/// @brief �K�[�h�q�b�g�G�t�F�N�g�����Ԋu�Ŕ��������邽�߂̃J�E���^�[
	int m_shieldHitEffectCounter = 0;
	//�s���s�\���G�t�F�N�g(�s����)
	Effect m_knockOutEffect;
	//�W���X�g�K�[�h�G�t�F�N�g
	Effect m_justGuardEffect;
	/// @brief �W���X�g�K�[�h���̃v���C���[�����G�t�F�N�g
	Effect m_kickBuffEffect;
	/// @brief �p���[�A�b�v���̃J�E���^�[
	int m_powerUpCounter = 0;
	/// @brief �_���[�W����̉񕜃G�t�F�N�g
	Effect m_repairEffect;
	/// @brief ���X�|�[�����̃G�t�F�N�g
	Effect m_respawnEffect;
	/// @brief �_���[�W�G�t�F�N�g
	Effect m_damageEffect;
	/// @brief �o�[�X�g���̃G�t�F�N�g
	Effect m_burstEffect;
	/// @brief �A�C�e���o�t�G�t�F�N�g
	Effect m_itemBuffEffect;
	/// @brief �A�C�e���o�t�G�t�F�N�g�Đ��p�J�E���^�[
	int m_itemPowerUpCounter = 0;
	/// @brief �_�b�V�����̃G�t�F�N�g
	Effect m_dashEffect;
	/// @brief �_�b�V�����̃J�E���^
	int m_dashCounter =  0;


	GameDirector* m_gameDirector = nullptr;
	Player* m_player =  nullptr;
	Ball* m_ball = nullptr;

	
	/// @brief �K�[�h�n�G�t�F�N�g�̋��ʍ��W
	Vector3 m_efcGuardPos = Vector3::Zero;

	/// @brief �K�[�h�\���G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void GuardBeginEffectUpdate();

	/// @brief �K�[�h�G�t�F�N�g�̍X�V
	/// @param plnum �X�V����v���C���[�ԍ�
	void GuardEffectUpdate();

	/// @brief �V�[���h�񕜃G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void ShieldRepairEffectUpdate();

	/// @brief �s���s�\�G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void KnockOutEffectUpdate();

	/// @brief �����G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void KickBuffEffectUpdate();

	/// @brief �_���[�W�񕜃G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void RepairEffectUpdate();

	/// @brief ���X�|�[�����̃G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void RespawnEffectUpdate();

	/// @brief �A�C�e���o�t�G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void ItemBuffEffectUpdate();

	/// @brief �_�b�V���G�t�F�N�g�̍X�V
	/// @param plNum �X�V����v���C���[�ԍ�
	void DashEffectUpdate();

public:
	
	PlayerEffect();
	~PlayerEffect();
	bool Start();
	void Update();

	/// @brief �v���C���[�̔ԍ���ݒ�
	/// @param plNum �ݒ肷��v���C���[�ԍ�
	void SetPlayerNumber(const int plNum);

	/// @brief �L�b�N�G�t�F�N�g���Đ�
	/// @param plnum �Đ�����v���C���[�ԍ�
	void PlayKickEffect();

	/// @brief �K�[�h�\���G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayGuardBeginEffect() { m_guardBeginEffect.Play(); }
	

	/// @brief �K�[�h�G�t�F�N�g���Đ�
	/// @param plnum �Đ�����v���C���[�ԍ�
	void PlayGuardEffect();
	/// @brief �K�[�h�G�t�F�N�g���~
	/// @param plnum ��~����v���C���[�ԍ�
	void StopGuardEffect() { m_guardEffect.Stop(); }
	
	/// @brief �K�[�h�u���C�N�G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayGuardBreakEffect();

	/// @brief �W���X�g�K�[�h�G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayJustGuardEffect();

	/// @brief �V�[���h�q�b�g�G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayShieldHitEffect();

	/// @brief �_���[�W�G�t�F�N�g���Đ�
	/// @param plNum 
	void PlayDamageEffect();

	/// @brief �o�[�X�g�G�t�F�N�g���Đ�
	void PlayBurstEffect();

	/// @brief �V�[���h�񕜃G�t�F�N�g�̍Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayShieldRepairEffect() { m_shieldRepairEffect.Play(); }

	/// @brief �s���s�\�G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayKnockOutEffect() { m_knockOutEffect.Play(); }

	/// @brief �s���s�\�G�t�F�N�g���~
	/// @param plNum ��~����v���C���[�ԍ�
	void StopKnockOutEffect() { m_knockOutEffect.Stop(); }
	
	/// @brief �v���C���[�����G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayKickBuffEffect();

	/// @brief �_���[�W����̉񕜃G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayRepairEffect() { m_repairEffect.Play(); }
	
	/// @brief ���X�|�[�����̃G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayRespawnEffect() { m_respawnEffect.Play(); }

	/// @brief �A�C�e���o�t�G�t�F�N�g���Đ�
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayItemBuffEffect();
	
	//�t�@�C���p�X�̕ύX
	void ChangeItemBuffEffect(ItemBuffChange buffNum);
	
	/// @brief �_�b�V�����̃G�t�F�N�g���Đ� 
	/// @param plNum �Đ�����v���C���[�ԍ�
	void PlayDashEffect();

};

