#pragma once
#include "effect/Effect.h"

class Timer;
class Score;
class Lighting;
class SkinModelRender;
class Ball;
class PlayerEffect;
class Effect;
class GameUI;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

	/// @brief �v���C���[�����Ԃ���ݒ�
	/// @param num �v���C���[�ԍ�
	void SetPlayerNumber(int num);

	/// @brief �ړ��̏���
	void Move();

	/// @brief ��]�̏���
	void Rotation();

	/// @brief �v���C���[�̍��W�����
	/// @return �v���C���[�̍��W
	Vector3 GetPosition() { return m_position; }

	void IsKick();

	/// @brief �{�[�����R�鏈��
	void KickBall();

	/// @brief �{�[���Ƃ̋������v�Z
	void BallDistanceCalculation();

	Vector3 GetToBallVec() { return m_toBallVec; }

	/// @brief �{�[���ƂԂ��鏈��
	void BallCollide();

	/// @brief �K�[�h�̏���
	void Guard();

	float GetGuardDurability() { return m_guardDurability; }

	/// @brief ���X�|�[���̏���
	void ReSpawn();
	/// @brief ���X�|�[�����̖��G���Ԃ̏���
	void Muteki();

	float GetStamina() { return m_stamina; }

	void Animation();

	bool GetGuardFlag() {
		return m_guard;
	}
	/// @brief �K�[�h��ԃQ�b�^�[
	bool GetGuardBreak() {
		return m_breakGuard;
	}

private:
	/// @brief �v���C���[�̔ԍ�
	int m_myNumber = 0;
	/// @brief �����ɍU�����Ă����v���C���[�̔ԍ�
	int m_haveAttackedPlayer = 4;
	/// @brief �v���C���[�̍��W
	Vector3 m_position = Vector3::Zero;
	/// @brief �v���C��[�̉�]
	Quaternion m_qRot = Quaternion::Identity;
	/// @brief �v���C���[�̊g�嗦
	Vector3 m_scale = Vector3::One;
	/// @brief �v���C���[�̑��x
	float m_moveVelocity = 0.0f;
	/// @brief �v���C���[�̈ړ����x
	Vector3 m_moveSpeed = Vector3::Zero;
	/// @brief �_�b�V���t���O
	bool m_dash = true;
	/// @brief �v���C���[�̃X�^�~�i
	float m_stamina = 0.0f;
	/// @brief �v���C���[�̌����Ă������
	Vector3 m_direction = Vector3::Zero;
	/// @brief �v���C���[�̃X�^�[�g���̍��W
	Vector3 m_startPos = Vector3::Zero;
	/// @brief �v���C���[�̃V���{���J���[
	Vector3 m_playerColor = Vector3::Zero;
	/// @brief �v���C���[�ɂ����門�C��
	float m_friction = 0.0f;
	/// @brief �v���C���[����{�[���ւ̃x�N�g��
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief �v���C���[�����񂾂��ǂ����̃t���O
	bool m_dieFlag = false;
	/// @brief �v���C���[�����X�|�[���������̖��G����
	float m_mutekiTime = 0.0f;
	/// @brief �{�[���Ƃ̋���
	float m_ballDistance = 0.0f;
	/// @brief �L�b�N�\���ǂ����̃t���O
	bool m_kickFlag = false;
	/// @brief �L�b�N��
	float m_kickPower = 0.0f;
	/// @brief �K�[�h�t���O
	bool m_guard = false;
	/// @brief �d��
	float m_gravity = 0.0f;
	/// @brief �_���[�W�t���O
	bool m_damage = false;
	/// @brief �O�t���[���̃_���[�W�t���O
	bool m_damagePrevFrame = false;
	/// @brief �_���[�W���󂯂ē�����悤�ɂȂ�܂ł̃^�C�}�[
	float m_damageTime = 0.0f;

	/// @brief L�X�e�B�b�N�̉�����
	float m_Lstickx = 0.0f;
	/// @brief L�X�e�B�b�N�̏c����
	float m_Lsticky = 0.0f;

	/// @brief �K�[�h�ϋv��
	float m_guardDurability = 100.0f;
	/// @brief �K�[�h�̏��
	bool m_breakGuard = false;
	/// @brief �V�[���h�Ƀ{�[�����G�ꂽ���H
	bool m_shieldHit = false;
	/// @brief �O�t���[���̃K�[�h��ԃt���O�L�^�p
	bool m_breakGuardPrevFrame = false;
	/// @brief �W���X�g�K�[�h����ɂȂ鎞��
	float m_justGuardTime = 0.0f;
	/// @brief �L�b�N�͂��オ��t���O
	bool m_kickPowerUp = false;
	/// @brief �L�b�N�͂��オ�鎞��
	float m_powerUpTime = 0.0f;
	/// @brief �K�[�h�j��ɂ���ċN����_�E�����
	//bool m_breakDown = false;

	/// @brief �L�����N�^�[�R���g���[���[
	CharacterController m_charaCon;
	/// @brief ���C�e�B���O
	Lighting* m_lig = nullptr;
	/// @brief �X�L�����f�������_���[
	SkinModelRender* m_skinModelRender = nullptr;
	/// @brief �{�[��
	Ball* m_ball = nullptr;

	//�G�t�F�N�g�֘A//
	/// @brief �{�[�����L�b�N�������̃G�t�F�N�g
	Effect m_kickEffect;
	/// @brief �K�[�h���̃G�t�F�N�g
	Effect m_guardEffect;
	//�K�[�h�G�t�F�N�g�����Ԋu�Ŕ��������邽�߂̃J�E���^�[
	int m_guardEffectCouter = 0;
	/// @brief �K�[�h�����̗\���G�t�F�N�g
	Effect m_guardBeginEffect;
	/// @brief �K�[�h�u���C�N�G�t�F�N�g
	Effect m_guardBreakEffect;
	/// @brief �V�[���h�񕜃G�t�F�N�g
	Effect m_shieldRepairEffect;
	/// @brief �V�[���h�񕜃t���O
	bool m_isRepair = true;
	/// @brief �K�[�h�q�b�g�G�t�F�N�g
	Effect m_shieldHitEffect;
	/// @brief �K�[�h�q�b�g�G�t�F�N�g�����Ԋu�Ŕ��������邽�߂̃J�E���^�[
	int m_shieldHitEffectCounter = 0;
	/// @brief �L�b�N�̃N�[���^�C���J�E���^�[
	int m_kickCooler = 0;
	/// @brief �L�b�N�̃N�[���^�C�������̐���
	bool m_kickCooling = false;
	/// @brief m_kickFlag�Ƃ͕ʂ̉s�t���O
	bool m_readyKick = true;
	//�s���s�\���G�t�F�N�g(�s����)
	Effect m_knockOutEffect;
	//�W���X�g�K�[�h�G�t�F�N�g
	Effect m_justGuardEffect;

	enum enAnimationClips
	{
		enAnimation_Idle,
		enAnimation_Walk,
		enAnimation_Run,
		enAnimation_Num
	};

	enAnimationClips m_anim = enAnimation_Idle;

	AnimationClip m_animationClips[enAnimation_Num];

	/// @brief �^�C�}�[
	Timer* m_timer = nullptr;

	/// @brief �X�R�A
	Score* m_score = nullptr;

	/// @brief �Q�[��UI
	GameUI* m_ui = nullptr;

	/// @brief �v���C���[�̃G�t�F�N�g
	PlayerEffect* m_plEffect = nullptr;
};

