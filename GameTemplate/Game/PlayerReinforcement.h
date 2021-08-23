#pragma once

class Player;
class PlayerAction;
class PlayerMove;

/// @brief �A�C�e���ŋ�������Ă����Ԃ�\���񋓌^
enum enItemPowerUp {
	enKickUp,			//�L�b�N�̓A�b�v
	enDefenseUp,		//�h��̓A�b�v
	enSpeedUp,			//���x�A�b�v
	enItemPowerUpNum	//���������E�����̗v�f��
};

/// @brief �v���C���[�̋�����Ԃ𐧌䂷��N���X
class PlayerReinforcement : public IGameObject
{
public:
	PlayerReinforcement();
	~PlayerReinforcement();
	bool Start();
	void Update();

	/// @brief ��������P����ݒ�
	/// @param num �ݒ肷��v���C���[�ԍ�
	void SetPlayerNumber(const int num);

	/// @brief �v���C���[��������Ԃ��H
	/// @return true�ŋ������ false�ŋ�������Ă��Ȃ����
	bool IsPowerUp() const { return m_powerUp; }

	/// @brief �v���C���[��������ԂɕύX
	void ChangePowerUp() { m_powerUp = true; m_powerUpTime = 0.0f; }

	/// @brief �v���C���[���L�b�N������Ԃ��H
	/// @return true�ŃL�b�N������� false�ŃL�b�N������Ԃł͂Ȃ�
	bool IsKickUp() const;

	/// @brief �v���C���[���h�䋭����Ԃ��H
	/// @return true�Ŗh�䋭����� false�Ŗh�䋭����Ԃł͂Ȃ�
	bool IsDefenseUp() const;

	/// @brief �v���C���[�����x������Ԃ��H
	/// @return true�ő��x������ԁ@false�ő��x������Ԃł͂Ȃ�
	bool IsSpeedUp() const;

private:
	/// @brief �v���C���[�̔ԍ�
	int m_playerNumber = 0;
	/// @brief �p���[�A�b�v�t���O
	bool m_powerUp = false;
	/// @brief �p���[�A�b�v���̃J�E���^�[
	int m_powerUpCounter = 0;
	/// @brief �p���[�A�b�v�̎���
	float m_powerUpTime = 0.0f;
	/// @brief �A�C�e���ɂ��p���[�A�b�v�t���O
	bool m_itemPowerUp = false;
	/// @brief �A�C�e���ɂ��p���[�A�b�v����
	float m_itemPowerUpTime = 0.0f;
	/// @brief �ǂ̃A�C�e��������Ԃ���\���X�e�[�^�X
	enItemPowerUp m_itemPowerUpState = enItemPowerUpNum;
	/// @brief �v���C���[
	Player* m_player = nullptr;
	/// @brief �v���C���[�̃A�N�V����
	PlayerAction* m_playerAction = nullptr;
	/// @brief �v���C���[�̓���
	PlayerMove* m_playerMove = nullptr;
};

