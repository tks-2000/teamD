#pragma once

class FontRender;
class GameDirector;
class Timer;
class Score;
class Player;
class PlayerAction;
class PlayerMove;
class Ball;
class SpriteRender;


class GameUI : public IGameObject
{
public:
	GameUI();
	~GameUI();
	bool Start();
	void Update();

	void TimerFont();

	void AddScore(int num, int score);

	/// @brief �d���X�R�A�J�N�V
	void ScoreHider();
	/// @brief �d���v���C���[�J�N�V
	void Playerhider();
	/// @brief �d���Q�[�W�J�N�V
	void GageHider();
	/// @brief �J�E���g�_�E����ʂ̊֐��Ƃ��ăI�~�b�g
	void CountDown(int count);
	//void ScoreIndicator(float addition, Vector3 Pos);

private:
	/// @brief �e�X�g�p�̐��l
	//int m_testNum = 0;
	int m_playerNum = 0;

	int m_plNum[PLAYER_NUMBER] = {};

	/// @brief �e�X�g�p�̃t�H���g
	//FontRender* m_testFont;
	FontRender* m_playerFont[PLAYER_NUMBER] = { nullptr };

	/// @brief �e�X�g�p�̐��l�\���t�H���g
	//FontRender* m_testNumFont;
	FontRender* m_playerNumFont[PLAYER_NUMBER] = { nullptr };

	GameDirector* m_gameDirector = nullptr;

	/// @brief �{�[���̑��x�\���p�̃t�H���g
	FontRender* m_ballSpeed = nullptr;

	/// @brief �{�[�����\���p�摜
	SpriteRender* m_ballSpeedMeter = nullptr;
	/// @brief �{�[�����\���p�摜����2
	SpriteRender* m_ballSpeedMeterPin = nullptr;
	float PinRot = -60.0f;
	
	/// @brief	�t�B�j�b�V�������\���X�v���C�g 
	SpriteRender* m_finishSprite = nullptr;
	/// @brief ���W
	Vector3 m_finishSpritePos = Vector3::Zero;
	/// @brief �X�P�[��
	Vector3 m_finishSpriteScale = Vector3::Zero;
	/// @brief �J���[
	Vector4 m_finishSpriteColor = { 1.0f,1.0f,1.0f,1.0f };


	/// @brief �{�[���̑��x
	float m_ballVelocity = 0.0f;

	wchar_t* m_text;

	FontRender* m_GuardDurability[PLAYER_NUMBER] = { nullptr };

	float m_playerGuardDurability[PLAYER_NUMBER] = { 0.0f };

	Player* m_player[PLAYER_NUMBER] = { nullptr };
	Ball* m_ball = nullptr;


	/// @brief �c������^
	enum DDSWH { Width, Height, WHnum }WH;
	/// @brief �Q�[�W�x�[�X�T�C�Y
	int m_gageBaseSize[2] = { 180,20 };
	/// @brief �V�[���h�Q�[�W�x�[�X�̏�����
	SpriteRender* m_ShGageBase[PLAYER_NUMBER] = { nullptr };
	/// @brief �X�^�~�i�Q�[�W�x�[�X�̏�����
	SpriteRender* m_StGageBase[PLAYER_NUMBER] = { nullptr };
	/// @brief �V�[���h�p�Q�[�W�X�v���C�g�����_�[
	SpriteRender* m_shieldGage[PLAYER_NUMBER] = { nullptr };
	/// @brief �A�C�R���̏c���̃T�C�Y
	int m_IconSize = 25;
	/// @brief �V�[���h�Q�[�W�̐F
	Vector4 m_ShGageColor = { 0.0f, 0.4f, 1.0f, 1.0f };
	/// @brief �V�[���h�u���C�N���̃Q�[�W�J���[
	Vector4 m_ShAlertColor = { 1.0f, 0.0f, 0.0f, 0.5f };
	/// @brief �V�[���h�Q�[�W�̃T�C�Y
	int m_ShGageSize[2] = { 176, 16 };
	/// @ brief �V�[���h�Q�[�W�̈ʒu
	Vector3 m_ShGagePos[4] = { /*1P*/{-485.0f, 200.0f, 0.0f}, /*2P*/{485.0f, 200.0f, 0.0f}, /*3P*/{-485.0f, -300.0f, 0.0f}, /*4P*/{485.0f, -300.0f, 0.0f} };
	/// @brief �V�[���h�u���C�N���̃A���[�g���b�Z�[�W
	FontRender* m_breakAlertMassege[PLAYER_NUMBER] = { nullptr };
	/// @brief �V�[���h�A���[�g���b�Z�[�W�̈ʒu
	Vector2 m_ShAlertMassegePos[4] = { {-570.0f, 208.0f},{445.0f, 208.0f},{-570.0f, -293.0f},{445.0f, -293.0f} };
	/// @brief �V�[���h�Q�[�W�������A�C�R��
	SpriteRender* m_ShGageIcon[PLAYER_NUMBER] = { nullptr };
	/// @brief �A�C�R���̈ʒu
	Vector3 m_ShIconPos[PLAYER_NUMBER] = { {-585.0f,200.0f,0.0f},{585.0f,200.0f,0.0f},{-585.0f,-300,0.0f},{585.0f,-300.0f,0.0f} };
	/// @brief �X�^�~�i�p�Q�[�W�X�v���C�g�����_�[
	SpriteRender* m_staminaGage[PLAYER_NUMBER] = { nullptr };
	/// @brief �X�^�~�i�Q�[�W�J���[
	Vector4 m_StGageColor = { 1.0f,1.0f,0.0f,1.0f };
	/// @brief �X�^�~�i�؂ꒆ�̃Q�[�W�J���[
	Vector4 m_StAlertColor = { 0.5f, 0.5f, 0.0f, 0.8f };
	/// @brief �X�^�~�i�Q�[�W�̃T�C�Y
	int m_StGageSize[WHnum] = { 176, 16 };
	/// @brief �X�^�~�i�Q�[�W�̈ʒu
	Vector3 m_StGagePos[4] = { /*1P*/{-485.0f, 170.0f, 0.0f}, /*2P*/{485.0f,170.0f, 0.0f}, /*3P*/{-485.0f, -330.0f, 0.0f}, /*4P*/{485.0f, -330.0f, 0.0f} };
	/// @brief �X�^�~�i�A���[�g���b�Z�[�W
	FontRender* m_tiredAlertMassege[PLAYER_NUMBER] = { nullptr };
	/// @brief �X�^�~�i�A���[�g���b�Z�[�W�̈ʒu
	Vector2 m_StAlertMassegePos[4] = { {-570.0f, 178.0f},{448.0f, 178.0f},{-570.0f, -322.0f},{448.0f, -322.0f} };
	/// @brief �X�^�~�i���l��%�����邽�߂̐��l
	float m_staminaComplement = 100.0f / 6.0f;
	/// @brief �X�^�~�i�Q�[�W�������A�C�R��
	SpriteRender* m_StGageIcon[PLAYER_NUMBER] = { nullptr };
	/// @brief �X�^�~�i�Q�[�W�A�C�R���̈ʒu
	Vector3 m_StIconPos[PLAYER_NUMBER] = { {-585.0f,170.0f,0.0f},{585.0f,170.0f,0.0f},{-585.0f,-330,0.0f},{585.0f,-330.0f,0.0f} };

	/// @brief �V�[���h�Q�[�W�O�k����
	SpriteRender* m_ShGageBegin[PLAYER_NUMBER] = { nullptr };
	Vector3 m_ShGageBeginPos[PLAYER_NUMBER] = { { -597.0f, 200.0f, 0.0f },{597.0f, 200.0f, 0.0f},{-597.0f,-300.0f, 0.0f},{597.0f, -300.0f, 0.0f} };
	SpriteRender* m_ShGageBody[PLAYER_NUMBER] = { nullptr };
	Vector3 m_ShGageBodyPos[PLAYER_NUMBER] = { { -494.0f, 200.0f, 0.0f }, {494.0f, 200.0f, 0.0f}, {-494.0f, -300.0f, 0.0f}, {494.0f, -300.0f, 0.0f} };
	SpriteRender* m_ShGageFinal[PLAYER_NUMBER] = { nullptr };
	Vector3 m_ShGageFinalPos[4] = { { -400.0f,200.0f,0.0f },{400.0f, 200.0f, 0.0f},{-400.0f, -300.0f,  0.0f},{400.0f, -300.0f, 0.0f} };

	/// @brief �X�^�~�i�Q�[�W�O�k����
	SpriteRender* m_StGageBegin[PLAYER_NUMBER] = { nullptr };
	Vector3 m_StGageBeginPos[PLAYER_NUMBER] = { {-597.0f, 170.0f, 0.0f}, {597.0f, 170.0f, 0.0f}, {-597.0f, -330.0f,0.0f},{597.0f, -330.0f, 0.0f} };
	SpriteRender* m_StGageBody[PLAYER_NUMBER] = { nullptr };
	Vector3 m_StGageBodyPos[PLAYER_NUMBER] = { {-494.0f, 170.0f, 0.0f}, {494.0f, 170.0f, 0.0f}, {-494.0f, -330.0f, 0.0f}, {494.0f, -330.0f, 0.0f } };
	SpriteRender* m_StGageFinal[PLAYER_NUMBER] = { nullptr };
	Vector3 m_StGageFinalPos[PLAYER_NUMBER] = { {-400.0f, 170.0f, 0.0f}, {400.0f, 170.0f, 0.0f}, {-400.0f, -330.0f, 0.0f},{400.0f, -330.0f, 0.0f} };

	float PinAngArrival = 0.0f;

	/// @brief ��������A�C�R��
	SpriteRender* m_LBbuttonIcon[PLAYER_NUMBER] = { nullptr };
	Vector3 m_LBbuttonIPos[PLAYER_NUMBER] = { {-370.0f, 208.0f, 0.0f},{370.0f, 208.0f, 0.0f},{-370.0f, -292.0f, 0.0f},{370.0f, -292.0f, 0.0f} };
	SpriteRender* m_RBbuttonIcon[PLAYER_NUMBER] = { nullptr };
	Vector3 m_RBbuttonIPos[PLAYER_NUMBER] = { {-370.0f, 178.0f, 0.0f},{370.0f, 178.0f, 0.0f},{-370.0f, -322.0f, 0.0f},{370.0f, -322.0f, 0.0f} };

	/// @brief �X�R�A�̓��B�_
	float NowScore[PLAYER_NUMBER] = { 0.0f };
	/// @brief �ÃX�R�A
	float oldScore[PLAYER_NUMBER] = { 0.0f };
	/// @brief �����X�R�A
	float viewScore[PLAYER_NUMBER] = { 0.0f };

	/// @brief �X�R�A�ϓ��\��
	FontRender* m_fluctiationIndicater[PLAYER_NUMBER] = { nullptr };
	/// @brief �X�R�A�ϓ��\���̈ʒu
	Vector2 m_IndicaterPos[PLAYER_NUMBER] = { { -450.0f,250.0f },{ 400.0f,250.0f },{ -450.0f,-250.0f },{ 400.0f,-250.0f } };
	/// @brief �\������ϓ��X�R�A
	int m_fluctiationScore[PLAYER_NUMBER] = { 0 };
	/// @brief �C���W�P�[�^�[�E�F�C�^�[
	int m_indicaterWaiter;


	/// @brief �^�C�}�[�\��
	FontRender* m_timeFont = nullptr;
	/// @brief �^�C�}�[�̃t���[��
	SpriteRender* m_timerFrame = nullptr;
	/// @brief �^�C�}�[�w�b�_
	FontRender* m_timerHedder = nullptr;
	/// @brief GO�T�C��
	SpriteRender* m_goSign = nullptr;
	bool m_Gone = false;
	float m_GOScale = 12.0f;
	/// @brief �J�E���g��`��
	SpriteRender* m_countDDS[3] = { nullptr };

	bool m_isInitd = false;
	int goGoneWaiter = 0;
	bool m_GoisGone = false;

	Timer* m_timer = nullptr;

	Score* m_score = nullptr;

	PlayerAction* m_plAction[PLAYER_NUMBER] = { nullptr };

	PlayerMove* m_plMove[PLAYER_NUMBER] = { nullptr };
};

