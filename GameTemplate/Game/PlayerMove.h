#pragma once

class Player;
class PlayerAction;
class PlayerReinforcement;
class Ball;
class Se;
class Score;
class Timer;

/// @brief �v���C���[�̈ړ��𐧌䂷��N���X
class PlayerMove : public IGameObject
{
public:
	PlayerMove();
	~PlayerMove();
	bool Start()override;
	void Update()override;

	/// @brief �v���C���[�̔ԍ���ݒ�
	/// @param plNum �ݒ肷��v���C���[�ԍ�
	void SetPlayerNumber(const int plNum);

	/// @brief �ړ��\���H
	/// @return true�Ȃ�\�@false�Ȃ�s�\
	bool IsCanMove() const;

	/// @brief �_�b�V�����Ă��邩����
	/// @return true�Ń_�b�V�����Ă��� false�Ń_�b�V�����Ă��Ȃ�
	bool IsDash() const;

	/// @brief �v���C���[�̌����Ă�����������
	/// @return �v���C���[�̌����Ă������
	const Vector3& GetDirection() const { return m_direction; }

	/// @brief �v���C���[�̈ړ����x�����
	/// @return �v���C���[�̈ړ����x
	const Vector3& GetMoveSpeed() const { return m_moveSpeed; }

	/// @brief �v���C���[�̈ړ����x��ݒ�
	/// @param move �v���C���[�ɐݒ肷��ړ����x
	void SetMoveSpeed(const Vector3& move) { m_moveSpeed = move; }

	/// @brief �v���C���[�̃X�^�~�i�����
	/// @return �v���C���[�̃X�^�~�i
	const float GetStamina() const { return m_stamina; }

private:
	/// @brief ���������t���O
	bool m_setUp = false;
	/// @brief �v���C���[�̔ԍ�
	int m_playerNum = 0;
	/// @brief L�X�e�B�b�N�̉�����
	float m_Lstickx = 0.0f;
	/// @brief L�X�e�B�b�N�̏c����
	float m_Lsticky = 0.0f;
	/// @brief �v���C���[�̑��x
	float m_moveVelocity = 0.0f;
	/// @brief �v���C���[�ɉ��Z���鑬�x
	float m_addVelocity = 0.0f;
	/// @brief �v���C���[�̈ړ����x
	Vector3 m_moveSpeed = Vector3::Zero;
	/// @brief �v���C���[�ɂ����門�C��
	float m_friction = 0.0f;
	/// @brief �d��
	float m_gravity = 0.0f;
	/// @brief �_�b�V���\�t���O
	bool m_dash = true;
	/// @brief �v���C���[�̃X�^�~�i
	float m_stamina = 0.0f;
	/// @brief �X�^�~�i�ቺ��
	float m_staminaDecreaseValue = 0.0f;
	/// @brief �v���C���[�̌����Ă������
	Vector3 m_direction = Vector3::Zero;
	/// @brief �v���C���[�̉�]
	Quaternion m_qRot = Quaternion::Identity;
	/// @brief �v���C���[����{�[���ւ̃x�N�g��
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief �{�[���Ƃ̋���
	float m_ballDistance = 0.0f;
	/// @brief �v���C���[��������Ԑ���
	float m_blowAwayRate = 0.0f;

	/// @brief �v���C���[
	Player* m_player = nullptr;
	/// @brief �v���C���[�A�N�V����
	PlayerAction* m_plAction = nullptr;
	/// @brief �v���C���[�G�t�F�N�g
	PlayerEffect* m_plEffect = nullptr;
	/// @brief �v���C���[����
	PlayerReinforcement* m_plReinforcement = nullptr;
	/// @brief �T�E���h�G�t�F�N�g
	Se* m_se = nullptr;
	/// @brief �{�[��
	Ball* m_ball = nullptr;
	/// @brief �X�R�A
	Score* m_score = nullptr;
	/// @brief �^�C�}�[
	Timer* m_timer = nullptr;
	
	/// @brief ��Ԃɂ���ĕω�����p�����[�^�[�����肷��֐�
	void DetermineParameters();

	/// @brief �ړ�
	void Move();

	/// @brief ���s�̏���
	void Walk();

	/// @brief �_�b�V���̏���
	void Dash();

	/// @brief �X�^�~�i�񕜂̏���
	void StaminaRecovery();

	/// @brief �X�^�~�i���Ǘ�����֐�
	void StaminaManagement();

	/// @brief ��]
	void Rotation();

	/// @brief �v���C���[�̈ړ����~
	void MoveStop() { m_moveSpeed.x = 0.0f; m_moveSpeed.z = 0.0f; }
};

