#pragma once

class Player;
class PlayerEffect;
class PlayerMove;
class PlayerReinforcement;
class Timer;
class Ball;
class Se;

/// @brief �v���C���[�̃A�N�V����(�L�b�N�ƃK�[�h)�𐧌䂷��N���X
class PlayerAction : public IGameObject
{
public:
	PlayerAction();
	~PlayerAction();
	bool Start();
	void Update();

	/// @brief ��������P����ݒ�
	/// @param num �ݒ肷��v���C���[�ԍ�
	void SetPlayerNumber(const int num);

	/// @brief �K�[�h�ϋv�l���擾
	/// @return �K�[�h�ϋv�l
	float GetGuardDurability() const { return m_guardDurability; }

	/// @brief �K�[�h�t���O���擾�B
	/// @return true�Ȃ�K�[�h���Bfalse�Ȃ�K�[�h���Ă��Ȃ��B
	bool IsGuard() const {
		return m_guard;
	}
	/// @brief �K�[�h�j�󂳂�Ă��邩�H
	/// @return true�Ŕj�󂳂�Ă���B false�Ŕj�󂳂�Ă��Ȃ��B
	bool IsGuardBreak() const {
		return m_breakGuard;
	}

private:
	/// @brief �v���C���[�̔ԍ�
	int m_playerNum = 0;

	/// @brief �K�[�h�t���O
	bool m_guard = false;
	/// @brief �K�[�h�ϋv��
	float m_guardDurability = 100.0f;
	/// @brief �K�[�h�ϋv�l�ቺ��
	float m_guradDecreaseValue = 0.0f;
	/// @brief �K�[�h�j��̏��
	bool m_breakGuard = false;
	/// @brief �V�[���h�Ƀ{�[�����G�ꂽ���H
	bool m_shieldHit = false;
	/// @brief �O�t���[���̃K�[�h��ԃt���O�L�^�p
	bool m_breakGuardPrevFrame = false;
	/// @brief �W���X�g�K�[�h����ɂȂ鎞��
	float m_justGuardTime = 0.0f;
	/// @brief �K�[�h���̈ړ����x
	Vector3 m_guardMoveSpeed = Vector3::Zero;

	/// @brief �v���C���[����{�[���ւ̃x�N�g��
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief �{�[���Ƃ̋���
	float m_ballDistance = 0.0f;

	/// @brief �L�b�N�\���ǂ����̃t���O
	bool m_kickFlag = false;
	/// @brief �L�b�N��
	float m_kickPower = 0.0f;

	/// @brief �K�[�h�\�����ׂ�
	/// @return true�ŃK�[�h�\�Bfalse�ŃK�[�h�s�\�B
	bool CheckGuard();

	/// @brief �K�[�h�̏���
	void Guard();

	/// @brief �K�[�h���̃{�[���ڐG����
	void GuardCollide();

	/// @brief �v���C���[
	Player* m_player = nullptr;
	/// @brief �v���C���[�̃G�t�F�N�g
	PlayerEffect* m_plEffect = nullptr;
	/// @brief �v���C���[�̈ړ�
	PlayerMove* m_plMove = nullptr;
	/// @brief �v���C���[�̋���
	PlayerReinforcement* m_plReinforcement = nullptr;
	/// @brief �^�C�}�[
	Timer* m_timer = nullptr;
	/// @brief �{�[��
	Ball* m_ball = nullptr;
	/// @brief �T�E���h�G�t�F�N�g
	Se* m_se = nullptr;
};

