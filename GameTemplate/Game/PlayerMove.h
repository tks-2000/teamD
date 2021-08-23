#pragma once

class Player;
class PlayerAction;
class PlayerReinforcement;
class Se;

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

	/// @brief �v���C���[�̌����Ă�����������
	/// @return �v���C���[�̌����Ă������
	const Vector3& GetDirection() const { return m_direction; }

	/// @brief �v���C���[�̈ړ����x�����
	/// @return �v���C���[�̈ړ����x
	const Vector3& GetMoveSpeed() const { return m_moveSpeed; }

	/// @brief �v���C���[�̈ړ����x��ݒ�
	/// @param move �v���C���[�ɐݒ肷��ړ����x
	void SetMoveSpeed(const Vector3& move) { m_moveSpeed = move; }

	/// @brief �_�b�V�����Ă��邩����
	/// @return true�Ń_�b�V�����Ă��� false�Ń_�b�V�����Ă��Ȃ�
	bool IsDash() const;

	/// @brief ���s�̏���
	void Walk();

	/// @brief �_�b�V���̏���
	void Dash();

	/// @brief �X�^�~�i�񕜂̏���
	void StaminaRecovery();

private:
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
	/// @brief �v���C���[�̃X�^�[�g���̍��W
	Vector3 m_startPos = Vector3::Zero;
	/// @brief ���X�|�[���{�^���������Ă��鎞��
	float m_reSpawnTime = 0.0f;
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
	/// @brief ���������t���O
	bool m_setUp = false;

	/// @brief �ړ�
	void Move();

	/// @brief ��]
	void Rotation();

	/// @brief ��Ԃɂ���ĕω�����p�����[�^�[�����肷��֐�
	void DetermineParameters();

	/// @brief �_�b�V���\�����ׂ�֐�
	void CheckDash();

	/// @brief �ړ����x�𒲂ׂ�֐�
	void CheckMoveSpeed();

	/// @brief �v���C���[�̈ړ����~
	void MoveStop() { m_moveSpeed.x = 0.0f; m_moveSpeed.z = 0.0f; }

	/// @brief ���X�|�[���̃J�E���g��i�߂�֐�
	void ReSpawnCountAdd();

	/// @brief ���X�|�[���̏���
	void ReSpawn();
};

