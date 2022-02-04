#pragma once

class Player;
class PlayerAction;
class PlayerEffect;
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

	/// @brief �v���C���[�����ȋ�����Ԃ��H
	/// @return true�ŋ������ false�ŋ�������Ă��Ȃ����
	bool IsSelfPowerUp() const { return m_selfPowerUp; }

	/// @brief �v���C���[���L�b�N������Ԃ��H
	/// @return true�ŃL�b�N������� false�ŃL�b�N������Ԃł͂Ȃ�
	bool IsKickUp() const;

	/// @brief �v���C���[���h�䋭����Ԃ��H
	/// @return true�Ŗh�䋭����� false�Ŗh�䋭����Ԃł͂Ȃ�
	bool IsDefenseUp() const;

	/// @brief �v���C���[�����x������Ԃ��H
	/// @return true�ő��x������ԁ@false�ő��x������Ԃł͂Ȃ�
	bool IsSpeedUp() const;

	/// @brief �v���C���[�����ȋ�����ԂɕύX
	void ChangeSelfPowerUp() { m_selfPowerUp = true; m_selfPowerUpCount = 0.0f; }

	/// @brief �v���C���[���L�b�N�͋�����ԂɕύX
	void ChangeKickPowerUp();

	/// @brief �v���C���[��h�䋭����ԂɕύX
	void ChangeDefenseUp();

	/// @brief �v���C���[�𑬓x������ԂɕύX
	void ChangeSpeedUp();

	/// @brief ������Ԃ�����
	void ReinforcementRelease();

private:
	/// @brief ���������t���O
	bool m_setUp = false;
	/// @brief �v���C���[�̔ԍ�
	int m_playerNumber = 0;
	/// @brief ���ȋ����t���O
	bool m_selfPowerUp = false;
	/// @brief ���ȋ������̃J�E���g
	float m_selfPowerUpCount = 0.0f;
	/// @brief �ǂ̃A�C�e��������Ԃ���\���X�e�[�^�X
	enItemPowerUp m_itemPowerUpState = enItemPowerUpNum;
	/// @brief �A�C�e���ɂ�鋭�����̃J�E���g
	float m_itemPowerUpCount = 0.0f;

	/// @brief �v���C���[
	Player* m_player = nullptr;
	/// @brief �v���C���[�̃A�N�V����
	PlayerAction* m_playerAction = nullptr;
	/// @brief �v���C���[�̓���
	PlayerMove* m_playerMove = nullptr;
	/// @brief �v���C���[�̃G�t�F�N�g
	PlayerEffect* m_plEffect = nullptr;

	/// @brief ���ȋ������̏���
	void SelfPowerUp();

	/// @brief �A�C�e���ɂ�鋭�����̏���
	void ItemPowerUp();
};

