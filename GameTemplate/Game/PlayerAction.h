#pragma once

class Player;
class PlayerCollide;
class PlayerEffect;
class PlayerMove;
class PlayerReinforcement;
class Timer;
class Ball;
class Se;
class Score;

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
	const float GetGuardDurability() const { return m_guardDurability; }

	/// @brief �K�[�h�ϋv�l��ݒ�
	/// @param durability �ݒ肷��K�[�h�ϋv�l
	void SetGuardDurability(const float durability) { m_guardDurability = durability; }

	/// @brief �K�[�h�ϋv�l��ቺ������
	/// @param damage �K�[�h�ϋv�l�ɗ^����_���[�W��
	void SetGuardDamage(const float damage) { m_guardDurability - damage; }

	/// @brief �K�[�h�ϋv�l�ቺ�ʂ��擾����
	/// @return �K�[�h�ϋv�l�ቺ��
	const float GetGuradDecreaseValue() const { return m_guardDecreaseValue; }

	/// @brief �K�[�h���Ԃ��擾
	/// @return �K�[�h����
	const float GetGuardTime() const { return m_guardTime; }

	/// @brief �K�[�h�\���H
	/// @return true�ŃK�[�h�\ false�ŃK�[�h�s�\
	bool IsCanGuard();

	/// @brief �K�[�h���Ă��邩�H
	/// @return true�Ȃ�K�[�h�� false�Ȃ�K�[�h���Ă��Ȃ�
	bool IsGuard();

	/// @brief �K�[�h�j�󂳂�Ă��邩�H
	/// @return true�Ŕj�󂳂�Ă��� false�Ŕj�󂳂�Ă��Ȃ�
	bool IsGuardBreak() const { return m_guardBreak; }

	/// @brief �L�b�N���\���H
	/// @return true�ŃL�b�N�\ false�ŃL�b�N�s�\
	bool IsCanKick();

private:
	/// @brief ���������t���O
	bool m_setUp = false;
	/// @brief �v���C���[�̔ԍ�
	int m_playerNum = 0;
	/// @brief �K�[�h�t���O
	bool m_guard = false;
	/// @brief �K�[�h�ϋv��
	float m_guardDurability = 100.0f;
	/// @brief �K�[�h�ϋv�l�ቺ��
	float m_guardDecreaseValue = 0.0f;
	/// @brief �K�[�h�ϋv�l�񕜗�
	float m_guardRecoveryValue = 0.0f;
	/// @brief �K�[�h�j��̏��
	bool m_guardBreak = false;
	/// @brief �V�[���h�Ƀ{�[�����G�ꂽ���H
	bool m_shieldHit = false;
	/// @brief �O�t���[���̃K�[�h��ԃt���O�L�^�p
	bool m_breakGuardPrevFrame = false;
	/// @brief �K�[�h����
	float m_guardTime = 0.0f;
	/// @brief �K�[�h���̈ړ����x
	Vector3 m_guardMoveSpeed = Vector3::Zero;

	/// @brief �v���C���[����{�[���ւ̃x�N�g��
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief �{�[���Ƃ̋���
	float m_ballDistance = 0.0f;

	/// @brief �L�b�N��
	float m_kickPower = 0.0f;

	/// @brief �v���C���[�̐�����Ԑ���
	float m_blowAwayRate = 0.0f;


	/// @brief ��Ԃɂ���ĕω�����p�����[�^�[�����肷��֐�
	void DetermineParameters();

	/// @brief �K�[�h�̏���
	void Guard();

	/// @brief �K�[�h�ϋv�l�񕜂̏���
	void GuardDecreaseRecovery();

	/// @brief �L�b�N�̏���
	void Kick();

	/// @brief �v���C���[
	Player* m_player = nullptr;
	/// @brief �v���C���[�̐ڐG
	PlayerCollide* m_plCollide = nullptr;
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
	/// @brief �X�R�A
	Score* m_score = nullptr;
};

