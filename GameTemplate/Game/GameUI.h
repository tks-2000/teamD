#pragma once

class FontRender;
class GameDirector;
class Timer;
class Score;
class Player;
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

	SpriteRender* m_LBbuttonIcon[PLAYER_NUMBER] = { nullptr };
	Vector3 m_LBbuttonIPos[PLAYER_NUMBER] = { {-370.0f, 208.0f, 0.0f},{370.0f, 208.0f, 0.0f},{-370.0f, -292.0f, 0.0f},{370.0f, -292.0f, 0.0f} };
	SpriteRender* m_RBbuttonIcon[PLAYER_NUMBER] = { nullptr };
	Vector3 m_RBbuttonIPos[PLAYER_NUMBER] = { {-370.0f, 178.0f, 0.0f},{370.0f, 178.0f, 0.0f},{-370.0f, -322.0f, 0.0f},{370.0f, -322.0f, 0.0f} };

	/// @brief �^�C�}�[�\��
	FontRender* m_timeFont = nullptr;

	Timer* m_timer = nullptr;

	Score* m_score = nullptr;
};

