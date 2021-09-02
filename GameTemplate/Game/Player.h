#pragma once
#include "effect/Effect.h"

class Timer;
class Score;
class Lighting;
class SkinModelRender;
class Ball;
class PlayerAction;
class PlayerCollide;
class PlayerEffect;
class PlayerMove;
class PlayerReinforcement;
class Effect;
class GameUI;
class Se;

//�����̃A�C�e���o�t�������ɕς��������`���邽�߂̗񋓑�
enum ItemBuffChange
{
	enItemBuff_Kick,
	enItemBuff_Guard,
	enItemBuff_Speed,
	enItemBuff_Num
};

enum enPlayerNumber
{
	enPlayer1,
	enPlayer2,
	enPlayer3,
	enPlayer4,
	enPlayerNum
};

enum enAnimationClips
{
	enAnimation_Idle,
	enAnimation_Walk,
	enAnimation_Run,
	enAnimation_Num
};

/// @brief �v���C���[�N���X�B
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start()override;
	void Update()override;

	/// @brief ��������P����ݒ�
	/// @param num �ݒ肷��v���C���[�ԍ�
	void SetPlayerNumber(int num);

	/// @brief �ړ��̏���
	void Move();

	/// @brief ��]�̏���
	void Rotation();

	/// @brief �v���C���[�̍��W�����
	/// @return �v���C���[�̍��W��const�Q��
	const Vector3& GetPosition() const { return m_position; }

	/// @brief �v���C���[�̍��W��ݒ�
	/// @param pos �v���C���[�ɐݒ肷����W
	void SetPosition(const Vector3& pos) { m_position = pos; }

	/// @brief �v���C���[�̌����Ă�����������
	/// @return �v���C���[�̌����Ă��������const�Q��
	const Vector3& GetDirection() const { return m_direction; }

	/// @brief �v���C���[�̕�����ݒ�
	/// @param dir �v���C���[�ɐݒ肷�����
	void SetDirection(const Vector3& dir) { m_direction = dir; }

	/// @brief �v���C���[�̈ړ����x�����
	/// @return �v���C���[�̈ړ����x��const�Q��
	const Vector3& GetMoveSpeed() const { return m_moveSpeed; }

	/// @brief �v���C���[�̈ړ����x��ݒ�
	/// @param move �v���C���[�ɐݒ肷��ړ����x
	void SetMoveSpeed(const Vector3& move) { m_moveSpeed = move; }

	/// @brief ��]��ݒ�
	/// @param qRot �ݒ肷��N�H�[�^�j�I��
	void SetQrot(const Quaternion& qRot) { m_qRot = qRot; }
	/// @brief �L�b�N�\������
	void CheckKick() ;

	/// @brief �{�[�����R�鏈��
	void KickBall();

	/// @brief �_�b�V���\������
	bool IsDash() const;

	/// @brief �{�[���Ɍ������x�N�g�����v�Z
	void ToBallVectorCalculation();

	/// @brief �{�[���Ƃ̋������v�Z
	void BallDistanceCalculation();

	/// @brief �{�[���Ɍ������x�N�g�����擾�B
	/// @return �{�[���Ɍ������x�N�g����const�Q�ƁB
	const Vector3& GetToBallVec() const { return m_toBallVec; }

	/// @brief �{�[���ƂԂ��鏈��
	void BallCollide();

	/// @brief �K�[�h�̏���
	void Guard();

	/// @brief �K�[�h�ϋv�l���擾
	/// @return �K�[�h�ϋv�l
	float GetGuardDurability() const { return m_guardDurability; }

	/// @brief ���X�|�[���̏���
	void ReSpawn();
	/// @brief ���X�|�[�����̖��G���Ԃ̏���
	void Muteki();
	/// @brief �X�^�~�i�l�Q�b�^�[
	float GetStamina() const { return m_stamina; }
	/// @brief �_�b�V���t���O�Q�b�^�[
	bool GetDashFlg() const { return m_dash; }

	/// @brief �A�j���[�V������i�߂�֐��B
	void Animation();

	/// @brief �Đ�����A�j���[�V������ݒ�
	/// @param anim �Đ�����A�j���[�V�����̗񋓌^
	void SetAnimation(const enAnimationClips& anim) { m_anim = anim; }

	/// @brief �K�[�h�t���O���擾�B
	/// @return �K�[�h�t���O�Btrue�Ȃ�K�[�h���B
	bool GetGuardFlag() const{
		return m_guard;
	}
	/// @brief �K�[�h��ԃQ�b�^�[
	bool GetGuardBreak() const{
		return m_breakGuard;
	}
	/// @brief �v���C���[�̃��X�|�[���n�_�Q�b�^�[
	/// @return ���X�|�[���n�_��const�Q�ƁB
	const Vector3& GetRespawnPoint()const { return m_startPos; }

	void KickPowerUp() { m_kickUp = true; m_guardUp = false; m_speedUp = false; m_itemPowerUp = true; m_itemPowerUpTime = 0.0f; }

	void GuardPowerUp() { m_kickUp = false; m_guardUp = true; m_speedUp = false; m_itemPowerUp = true; m_itemPowerUpTime = 0.0f; }

	void SpeedPowerUp() { m_kickUp = false; m_guardUp = false; m_speedUp = true; m_itemPowerUp = true; m_itemPowerUpTime = 0.0f; }

	/// @brief �o�t��Ԃ̕ω��󋵂��L�^,�G�t�F�N�g�p�t�@�C���p�X�̕ύX
	void SetItemChangeState();
	
	/// @brief �v���C���[���_���[�W�����H
	/// @return true�Ń_���[�W�� false�Ń_���[�W���ł͂Ȃ�
	bool IsDamage() const { return m_damage; }

	/// @brief �v���C���[���_���[�W��ԂɕύX
	void SetDamage() { m_damage = true; }

	/// @brief �v���C���[����{�[���ɐL�т�x�N�g�������
	/// @return �v���C���[����{�[���ɐL�т�x�N�g����const�Q��
	const Vector3& GetToBallVector() const { return m_toBallVec; }

	/// @brief ���t���[���̃t���O��Ԃ��L�^
	void RecordFlags();

	/// @brief �L�����N�^�[�R���g���[���[�Ɉړ����x��ݒ�
	/// @param moveSpeed �ݒ肷��ړ����x
	void SetCharaCon(Vector3& moveSpeed) { m_position = m_charaCon.Execute(moveSpeed,1.0f); }

	/// @brief �v���C���[�����S���Ė��G���Ԓ����H
	/// @return true�Ȃ玀�S false�Ȃ琶��
	bool IsDie() const { return m_dieFlag; }

	/// @brief �Ō�ɍU�����Ă����v���C���[�̔ԍ������
	/// @return �Ō�ɍU�����Ă����v���C���[�̔ԍ�
	int GetHaveAttackedPlayer() { return m_haveAttackedPlayer; }

	/// @brief �Ō�ɍU�����Ă����v���C���[��ݒ�
	/// @param num �Ō�ɍU�����Ă����v���C���[�̔ԍ�
	void SetHaveAttackedPlayer(const int num) { m_haveAttackedPlayer = num; }

	/// @brief �v���C���[�ɐݒ肵�Ă��郉�C�g�̃J���[�����
	/// @return �v���C���[�ɐݒ肵�Ă��郉�C�g�̃J���[�̎Q��
	const Vector3& GetPlayerColor() const { return m_playerColor; }
private:
	/// @brief �����̃A�C�e���ɂ�鋭�����
	ItemBuffChange m_itemBuffChageState = enItemBuff_Kick;
	/// @brief �v���C���[�̔ԍ�
	int m_myNumber = 0;
	/// @brief �����ɍU�����Ă����v���C���[�̔ԍ�
	int m_haveAttackedPlayer = 4;
	/// @brief �v���C���[�̍��W
	Vector3 m_position = Vector3::Zero;
	/// @brief �v���C���[�̉�]
	Quaternion m_qRot = Quaternion::Identity;
	/// @brief �v���C���[�̊g�嗦
	Vector3 m_scale = Vector3::One;
	/// @brief �v���C���[�̑��x
	float m_moveVelocity = 0.0f;
	/// @brief �v���C���[�̈ړ����x
	Vector3 m_moveSpeed = Vector3::Zero;
	/// @brief �_�b�V���t���O
	bool m_dash = true;
	/// @brief �_�b�V�����̃J�E���^
	int m_dashCounter = 0;
	/// @brief �v���C���[�̃X�^�~�i
	float m_stamina = 0.0f;
	/// @brief �X�^�~�i�ቺ��
	float m_staminaDecreaseValue = 0.0f;
	/// @brief �v���C���[�̌����Ă������
	Vector3 m_direction = Vector3::Zero;
	/// @brief �v���C���[�̃X�^�[�g���̍��W
	Vector3 m_startPos = Vector3::Zero;
	/// @brief �v���C���[�̃V���{���J���[
	Vector3 m_playerColor = Vector3::Zero;
	/// @brief �v���C���[�ɂ����門�C��
	float m_friction = 0.0f;
	/// @brief �v���C���[����{�[���ւ̃x�N�g��
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief �v���C���[�����񂾂��ǂ����̃t���O
	bool m_dieFlag = false;
	/// @brief �o�[�X�g�����̃t���O
	bool m_burstFlag = false;
	/// @brief �O�t���[���̃o�[�X�g�t���O�L�^�p
	bool m_burstFlagPrevFrame = false;
	/// @brief �v���C���[�����X�|�[���������̖��G����
	float m_mutekiTime = 0.0f;
	/// @brief �{�[���Ƃ̋���
	float m_ballDistance = 0.0f;
	/// @brief �L�b�N�\���ǂ����̃t���O
	bool m_kickFlag = false;
	/// @brief �L�b�N��
	float m_kickPower = 0.0f;
	/// @brief �K�[�h�t���O
	bool m_guard = false;
	/// @brief �d��
	float m_gravity = 0.0f;
	/// @brief �_���[�W�t���O
	bool m_damage = false;
	/// @brief �O�t���[���̃_���[�W�t���O
	bool m_damagePrevFrame = false;
	/// @brief �_���[�W���󂯂ē�����悤�ɂȂ�܂ł̃^�C�}�[
	float m_damageTime = 0.0f;

	/// @brief L�X�e�B�b�N�̉�����
	float m_Lstickx = 0.0f;
	/// @brief L�X�e�B�b�N�̏c����
	float m_Lsticky = 0.0f;

	/// @brief �K�[�h�ϋv��
	float m_guardDurability = 100.0f;
	/// @brief �K�[�h�ϋv�l�ቺ��
	float m_guradDecreaseValue = 0.0f;
	/// @brief �K�[�h�̏��
	bool m_breakGuard = false;
	/// @brief �V�[���h�Ƀ{�[�����G�ꂽ���H
	bool m_shieldHit = false;
	/// @brief �O�t���[���̃K�[�h��ԃt���O�L�^�p
	bool m_breakGuardPrevFrame = false;
	/// @brief �W���X�g�K�[�h����ɂȂ鎞��
	float m_justGuardTime = 0.0f;
	/// @brief �p���[�A�b�v�t���O
	bool m_powerUp = false;
	/// @brief �p���[�A�b�v���̃J�E���^�[
	int m_powerUpCounter = 0;
	/// @brief �p���[�A�b�v�̎���
	float m_powerUpTime = 0.0f;
	/// @brief �K�[�h�j��ɂ���ċN����_�E�����
	//bool m_breakDown = false;
	
	/// @brief �L�b�N�����t���O
	bool m_kickUp = false;
	bool m_kickUpPrevFrame = false;
	/// @brief �K�[�h�����t���O
	bool m_guardUp = false;
	bool m_guardUpPrevFrame = false;
	/// @brief �X�s�[�h�����t���O
	bool m_speedUp = false;
	bool m_speedUpPrevFrame = false;

	bool m_itemPowerUp = false;

	float m_itemPowerUpTime = 0.0f;
	/// @brief �A�C�e���o�t�G�t�F�N�g�Đ��p�J�E���^�[
	int m_itemPowerUpCounter = 0;
	/// @brief ���������t���O
	bool m_setUp = false;
	/// @brief �L�����N�^�[�R���g���[���[
	CharacterController m_charaCon;
	/// @brief ���C�e�B���O
	Lighting* m_lig = nullptr;
	/// @brief �X�L�����f�������_���[
	SkinModelRender* m_skinModelRender = nullptr;
	/// @brief �{�[��
	Ball* m_ball = nullptr;

	//�G�t�F�N�g�֘A//
	/// @brief �{�[�����L�b�N�������̃G�t�F�N�g
	Effect m_kickEffect;
	/// @brief �K�[�h���̃G�t�F�N�g
	Effect m_guardEffect;
	//�K�[�h�G�t�F�N�g�����Ԋu�Ŕ��������邽�߂̃J�E���^�[
	int m_guardEffectCouter = 0;
	/// @brief �K�[�h�����̗\���G�t�F�N�g
	Effect m_guardBeginEffect;
	/// @brief �K�[�h�u���C�N�G�t�F�N�g
	Effect m_guardBreakEffect;
	/// @brief �V�[���h�񕜃G�t�F�N�g
	Effect m_shieldRepairEffect;
	/// @brief �V�[���h�񕜃t���O
	bool m_isRepair = true;
	/// @brief �K�[�h�q�b�g�G�t�F�N�g
	Effect m_shieldHitEffect;
	/// @brief �K�[�h�q�b�g�G�t�F�N�g�����Ԋu�Ŕ��������邽�߂̃J�E���^�[
	int m_shieldHitEffectCounter = 0;
	/// @brief �L�b�N�̃N�[���^�C���J�E���^�[
	int m_kickCooler = 0;
	/// @brief �L�b�N�̃N�[���^�C�������̐���
	bool m_kickCooling = false;
	/// @brief m_kickFlag�Ƃ͕ʂ̉s�t���O
	bool m_readyKick = true;
	//�s���s�\���G�t�F�N�g(�s����)
	Effect m_knockOutEffect;
	//�W���X�g�K�[�h�G�t�F�N�g
	Effect m_justGuardEffect;

	float m_reSpawnTime = 0.0f;

	enAnimationClips m_anim = enAnimation_Idle;

	AnimationClip m_animationClips[enAnimation_Num];

	/// @brief �^�C�}�[
	Timer* m_timer = nullptr;

	/// @brief �X�R�A
	Score* m_score = nullptr;
	/// @brief �Q�[��UI
	GameUI* m_ui = nullptr;
	//SE
	Se* m_se = nullptr;
	/// @brief �v���C���[�̃A�N�V����
	PlayerAction* m_plAction = nullptr;
	/// @brief �v���C���[�̐ڐG
	PlayerCollide* m_plCollide = nullptr;
	/// @brief �v���C���[�̃G�t�F�N�g
	PlayerEffect* m_plEffect = nullptr;
	/// @brief �v���C���[�̈ړ�
	PlayerMove* m_plMove = nullptr;
	/// @brief �v���C���[�̋���
	PlayerReinforcement* m_plReinforcement = nullptr;
};

