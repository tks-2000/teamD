#pragma once
#include "effect/Effect.h"

class Lighting;
class SkinModelRender;
class Ball;
class Effect;

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

	/// @brief �{�[���ƂԂ��鏈��
	void BallCollide();

	/// @brief �K�[�h�̏���
	void Guard();

	/// @brief ���X�|�[���̏���
	void ReSpawn() { m_position = m_startPos; m_charaCon.SetPosition(m_position); };

private:
	/// @brief �v���C���[�̔ԍ�
	int m_myNumber = 0;
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
	/// @brief �_���[�W���󂯂ē�����悤�ɂȂ�܂ł̃^�C�}�[
	float m_damageTime = 0.0f;

	/// @brief L�X�e�B�b�N�̉�����
	float m_Lstickx = 0.0f;
	/// @brief L�X�e�B�b�N�̏c����
	float m_Lsticky = 0.0f;

	/// @brief �L�����N�^�[�R���g���[���[
	CharacterController m_charaCon;
	/// @brief ���C�e�B���O
	Lighting* m_lig = nullptr;
	/// @brief �X�L�����f�������_���[
	SkinModelRender* m_skinModelRender = nullptr;
	/// @brief �{�[��
	Ball* m_ball = nullptr;
	/// @brief �{�[�����L�b�N�������̃G�t�F�N�g
	Effect m_kickEffect;
	/// @brief �K�[�h���̃G�t�F�N�g
	Effect m_guardEffect;
	int m_guardEffectCouter = 0;
};

