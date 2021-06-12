#pragma once

class Lighting;
class SkinModelRender;
class Ball;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

	/// @brief �ړ��̏���
	void Move();

	/// @brief ��]�̏���
	void Rotation();

	/// @brief �v���C���[�̍��W�����
	/// @return ���W
	Vector3 GetPosition() { return m_position; }

	void KickBall();

	void BallDistanceCalculation();

private:
	/// @brief �v���C���[�̍��W
	Vector3 m_position = Vector3::Zero;
	/// @brief �v���C��[�̉�]
	Quaternion m_qRot = Quaternion::Identity;
	/// @brief �v���C���[�̊g�嗦
	Vector3 m_scale = Vector3::One;
	/// @brief �v���C���[�̈ړ����x
	Vector3 m_moveSpeed = Vector3::Zero;
	
	float m_ballDistance = 0.0f;

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

