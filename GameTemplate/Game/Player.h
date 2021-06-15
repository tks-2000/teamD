#pragma once

class Lighting;
class SkinModelRender;
class Ball;

class Player : public IGameObject
{
public:
	Player();
	Player(int num);
	~Player();
	bool Start();
	void Update();

	/// @brief �ړ��̏���
	void Move();

	/// @brief ��]�̏���
	void Rotation();

	/// @brief �v���C���[�̍��W�����
	/// @return �v���C���[�̍��W
	Vector3 GetPosition() { return m_position; }

	/// @brief �{�[�����R�鏈��
	void KickBall();

	/// @brief �{�[���Ƃ̋������v�Z
	void BallDistanceCalculation();

	/// @brief �{�[���ƂԂ��鏈��
	void BallCollide();

	void Guard();

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
	
	/// @brief �{�[���Ƃ̋���
	float m_ballDistance = 0.0f;
	/// @brief �L�b�N��
	float m_kickPower = 0.0f;

	bool m_guard = false;

	/// @brief L�X�e�B�b�N�̉�����
	float m_Lstickx = 0.0f;
	/// @brief L�X�e�B�b�N�̏c����
	float m_Lsticky = 0.0f;

	/// @brief ���C�e�B���O
	Lighting* m_lig = nullptr;
	/// @brief �X�L�����f�������_���[
	SkinModelRender* m_skinModelRender = nullptr;
	/// @brief �{�[��
	Ball* m_ball = nullptr;

};

