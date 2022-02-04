#pragma once

class Player;
class PlayerAction;
class PlayerMove;
class PlayerReinforcement;
class Ball;
class Se;
class Score;

/// @brief �v���C���[�̏Փ˂𐧌䂷��N���X
class PlayerCollide : public IGameObject
{
public:
	PlayerCollide();
	~PlayerCollide();
	bool Start();
	void Update();

	/// @brief ��������P����ݒ�
	/// @param num �ݒ肷��v���C���[�ԍ�
	void SetPlayerNumber(const int num);

	/// @brief �v���C���[����{�[���Ɍ������ĐL�т�x�N�g�����擾
	/// @return �v���C���[����{�[���Ɍ����������x�N�g���̎Q��
	const Vector3& GetToBallVector() const { return m_toBallVec; }

	/// @brief �v���C���[�ƃ{�[���Ƃ̋������擾
	/// @return �v���C���[�ƃ{�[���̋���
	const float GetBallDistance() const { return m_ballDistance; }

private:
	/// @brief ���������t���O
	bool m_setUp = false;
	/// @brief �v���C���[�̔ԍ�
	int m_playerNum = 0;
	/// @brief �v���C���[����{�[���ւ̃x�N�g��
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief �{�[���Ƃ̋���
	float m_ballDistance = 0.0f;
	/// @brief �v���C���[�̐�����Ԑ���
	float m_blowAwayRate = 0.0f;
	/// @brief �K�[�h���Ƀ{�[�����G�ꂽ���H
	bool m_guradHit = false;
	/// @brief �W���X�g�K�[�h����ɂȂ鎞��
	float m_justGuardTime = 0.0f;
	/// @brief �K�[�h�ϋv�l�ቺ��
	float m_guardDecreaseValue = 0.0f;

	/// @brief ��Ԃɂ���ĕω�����p�����[�^�[�����肷��֐�
	void DetermineParameters();

	/// @brief �{�[���Ɍ������x�N�g�����v�Z
	void ToBallVectorCalculation();

	/// @brief �{�[���Ƃ̋������v�Z
	void BallDistanceCalculation();

	/// @brief �{�[���ƐڐG���鏈��
	void BallCollide();

	/// @brief �K�[�h���̃{�[���ڐG����
	void GuardCollide();

	/// @brief �v���C���[
	Player* m_player = nullptr;
	/// @brief �v���C���[�A�N�V����
	PlayerAction* m_plAction = nullptr;
	/// @brief �v���C���[�̈ړ�
	PlayerMove* m_plMove = nullptr;
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

	/// @brief �A�C�e���̐�
	enum {ITEM_NUM = 4};

	
};

