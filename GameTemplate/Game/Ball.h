#pragma once
#include "effect/Effect.h"


class Lighting;
class SkinModelRender;
class Effect;

class Ball : public IGameObject
{
public:
	Ball();
	~Ball();
	bool Start();
	void Update();

	/// @brief �ړ��̏���
	void Move();

	/// @brief ��]�̏���
	void Rotation();
	/// @brief �O�՗p�G�t�F�N�g�̍Đ�����
	void PlayTrackEffect();

	/// @brief �{�[���̈ړ����J�n����
	void MoveStart() { m_moveFlag = true; }

	/// @brief �{�[���������Ă��邩�H
	/// @return �{�[���̈ړ��t���O
	bool IsMove() { return m_moveFlag; }

	/// @brief X�����̒��˕Ԃ�
	void BounceX() { m_moveDirection.x *= -1.0f; }

	/// @brief Y�����̒��˕Ԃ�
	void BounceZ() { m_moveDirection.z *= -1.0f; }

	/// @brief �{�[���̍��W�����
	/// @return �{�[���̍��W
	Vector3 GetPosition() { return m_position; }

	/// @brief �{�[���̈ړ����x��ݒ�
	/// @param speed �{�[���ɐݒ肵�������x
	void SetMoveSpeed(Vector3 speed) { m_moveSpeed = speed; }

	/// @brief �{�[���ɉ�����͂�ݒ�
	/// @param kickPower �L�b�N��
	void Acceleration(float kickPower) { m_moveVelocity += kickPower; }
	
	/// @brief �{�[���̑��x�����
	/// @return �{�[���̑��x
	float GetVelocity() { return m_moveVelocity; }

	/// @brief �{�[���̑��x��ݒ�
	/// @param vel �{�[���ɐݒ肵�������x
	void SetVelocity(float vel) { m_moveVelocity = vel; }

	/// @brief �{�[���̕��������
	/// @return �{�[���̐i�s����
	Vector3 GetMoveDirection() { return m_moveDirection; }

	/// @brief �{�[���̈ړ�������ݒ�
	/// @param dir �{�[����i�܂���������
	void SetMoveDirection(Vector3 dir) { m_moveDirection = dir; m_moveDirection.y = 0.0f; m_moveDirection.Normalize(); }

	/// @brief �{�[���̃|�C���g���C�g�̃J���[��ݒ�
	/// @param color �{�[���̃|�C���g���C�g�ɐݒ肵�����J���[
	void SetBallLightColor(Vector3 color) { m_pointLigColor = color; }

private:
	/// @brief �{�[���̍��W
	Vector3 m_position = Vector3::Zero;
	/// @brief �{�[���̉�]
	Quaternion m_qRot = Quaternion::Identity;
	/// @brief �{�[���̊g�嗦
	Vector3 m_scale = Vector3::One;
	/// @brief �{�[���̉�]��
	Vector3 m_axisRotation = Vector3::Zero;
	/// @brief �{�[���̈ړ����x
	Vector3 m_moveSpeed = Vector3::Zero;
	/// @brief �{�[���̈ړ�����
	Vector3 m_moveDirection = Vector3::Zero;
	/// @brief �{�[���̑��x
	float m_moveVelocity = 0.0f;
	/// @brief �{�[���̈ړ��t���O
	bool m_moveFlag = false;
	/// @brief �{�[���̉�]�p�x
	float m_angle = 0.0f;
	/// @brief �{�[���̏d��
	float m_gravity = 0.0f;
	/// @brief �{�[���̈ʒu�ɂ���|�C���g���C�g�̃J���[
	Vector3 m_pointLigColor = Vector3::Zero;

	/// @brief �L�����N�^�[�R���g���[���[
	CharacterController m_charaCon;
	/// @brief ���C�e�B���O
	Lighting* m_lig = nullptr;
	/// @brief �X�L�����f�������_���[
	SkinModelRender* m_skinModelRender = nullptr;
	
	/// @brief �O�՗p�G�t�F�N�g
	Effect m_ballTrack;
};

