#pragma once

class Lighting;
class SkinModelRender;

class Ball : public IGameObject
{
public:
	Ball();
	~Ball();
	bool Start();
	void Update();

	/// @brief �ړ��̏���
	void Move();

	void Rotation();

	/// @brief �{�[���̈ړ����J�n����
	void MoveStart() { m_moveFlag = true; }

	/// @brief �{�[���������Ă��邩�H
	/// @return �{�[���̈ړ��t���O
	bool IsMove() { return m_moveFlag; }

	void BounceX() { m_moveDirection.x *= -1.0f; }

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


	void SetVelocity(float vel) { m_moveVelocity = vel; }

	Vector3 GetMoveDirection() { return m_moveDirection; }

	/// @brief �{�[���̈ړ�������ݒ�
	/// @param dir �{�[����i�܂���������
	void SetMoveDirection(Vector3 dir) { m_moveDirection = dir; m_moveDirection.y = 0.0f; m_moveDirection.Normalize(); }

private:
	/// @brief �{�[���̍��W
	Vector3 m_position = Vector3::Zero;
	/// @brief �{�[���̉�]
	Quaternion m_qRot = Quaternion::Identity;

	Vector3 m_scale = Vector3::One;

	Vector3 m_axisRotation = Vector3::Zero;
	/// @brief �{�[���̈ړ����x
	Vector3 m_moveSpeed = Vector3::Zero;
	/// @brief �{�[���̈ړ�����
	Vector3 m_moveDirection = Vector3::Zero;
	/// @brief �{�[���̑��x
	float m_moveVelocity = 0.0f;
	/// @brief �{�[���̈ړ��t���O
	bool m_moveFlag = false;

	float m_angle = 0.0f;

	Lighting* m_lig = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
};

