#pragma once

class FontRender;
class GameDirector;
class Timer;
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

	/// @brief �{�[���̑��x
	float m_ballVelocity = 0.0f;

	wchar_t* m_text;

	FontRender* m_GuardDurability[PLAYER_NUMBER] = { nullptr };

	float m_playerGuardDurability[PLAYER_NUMBER] = { 0.0f };

	Player* m_player[PLAYER_NUMBER] = { nullptr };
	Ball* m_ball = nullptr;

	/// @brief �c������^
	enum DDSWH { Width, Height, WHnum }WaH;
	/// @brief �V�[���h�p�Q�[�W�X�v���C�g�����_�[
	SpriteRender* m_shieldGage[PLAYER_NUMBER] = { nullptr };
	/// @brief �V�[���h�Q�[�W�̐F
	Vector4 m_ShGageColor = { 0.0f, 0.5f, 0.5f, 0.8f };
	/// @brief �V�[���h�u���C�N���̃Q�[�W�J���[
	Vector4 m_ShAlertColor = { 0.7f, 0.3f, 0.0f, 0.8f };
	/// @brief �V�[���h�Q�[�W�̃T�C�Y
	int m_ShGageSize[2] = { 320, 20 };
	/// @ brief �V�[���h�Q�[�W�̈ʒu
	Vector3 m_ShGagePos[4] = { /*1P*/{-450.0f, 200.0f, 0.0f}, /*2P*/{450.0f, 200.0f, 0.0f}, /*3P*/{-450.0f, -300.0f, 0.0f}, /*4P*/{450.0f, -300.0f, 0.0f} };
	/// @brief �V�[���h�u���C�N���̃A���[�g���b�Z�[�W
	FontRender* m_breakAlertMassege[PLAYER_NUMBER] = { nullptr };
	/// @brief �A���[�g���b�Z�[�W�̈ʒu
	Vector2 m_alertMassegePos[4] = { {-610.0f, 209.0f},{468.0f, 209.0f},{-610.0f, -291.0f},{468.0f, -291.0f} };
	/// @brief �X�^�~�i�p�Q�[�W�X�v���C�g�����_�[
	SpriteRender* m_staminaGage[PLAYER_NUMBER] = { nullptr };
	/// @brief �X�^�~�i�Q�[�W�J���[
	Vector4 m_StGageColor = { 0.3f,0.5f,0.2f,0.8f };
	/// @brief �X�^�~�i�Q�[�W�̃T�C�Y
	int m_StGageSize[WHnum] = { 320, 20 };
	/// @brief �X�^�~�i�Q�[�W�̈ʒu
	Vector3 m_StGagePos[4] = { /*1P*/{-450.0f, 180.0f, 0.0f}, /*2P*/{450.0f,180.0f, 0.0f}, /*3P*/{-450.0f, -320.0f, 0.0f}, /*4P*/{450.0f, -320.0f, 0.0f} };
	/// @brief �X�^�~�i���l��%�����邽�߂̐��l
	float m_staminaComplement = 100.0f / 6.0f;
	
	/// @brief �^�C�}�[�\��
	FontRender* m_timeFont = nullptr;

	Timer* m_timer = nullptr;
};

