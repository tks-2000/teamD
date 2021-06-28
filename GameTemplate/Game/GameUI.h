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
	/// @brief テスト用の数値
	//int m_testNum = 0;
	int m_playerNum = 0;

	int m_plNum[PLAYER_NUMBER] = {};

	/// @brief テスト用のフォント
	//FontRender* m_testFont;
	FontRender* m_playerFont[PLAYER_NUMBER] = { nullptr };

	/// @brief テスト用の数値表示フォント
	//FontRender* m_testNumFont;
	FontRender* m_playerNumFont[PLAYER_NUMBER] = { nullptr };

	GameDirector* m_gameDirector = nullptr;

	/// @brief ボールの速度表示用のフォント
	FontRender* m_ballSpeed = nullptr;

	/// @brief ボールの速度
	float m_ballVelocity = 0.0f;

	wchar_t* m_text;

	FontRender* m_GuardDurability[PLAYER_NUMBER] = { nullptr };

	float m_playerGuardDurability[PLAYER_NUMBER] = { 0.0f };

	Player* m_player[PLAYER_NUMBER] = { nullptr };
	Ball* m_ball = nullptr;

	/// @brief 縦横挙列型
	enum DDSWH { Width, Height, WHnum }WaH;
	/// @brief シールド用ゲージスプライトレンダー
	SpriteRender* m_shieldGage[PLAYER_NUMBER] = { nullptr };
	/// @brief シールドゲージの色
	Vector4 m_ShGageColor = { 0.0f, 0.5f, 0.5f, 0.8f };
	/// @brief シールドブレイク時のゲージカラー
	Vector4 m_ShAlertColor = { 0.7f, 0.3f, 0.0f, 0.8f };
	/// @brief シールドゲージのサイズ
	int m_ShGageSize[2] = { 320, 20 };
	/// @ brief シールドゲージの位置
	Vector3 m_ShGagePos[4] = { /*1P*/{-450.0f, 200.0f, 0.0f}, /*2P*/{450.0f, 200.0f, 0.0f}, /*3P*/{-450.0f, -300.0f, 0.0f}, /*4P*/{450.0f, -300.0f, 0.0f} };
	/// @brief シールドブレイク時のアラートメッセージ
	FontRender* m_breakAlertMassege[PLAYER_NUMBER] = { nullptr };
	/// @brief アラートメッセージの位置
	Vector2 m_alertMassegePos[4] = { {-610.0f, 209.0f},{468.0f, 209.0f},{-610.0f, -291.0f},{468.0f, -291.0f} };
	/// @brief スタミナ用ゲージスプライトレンダー
	SpriteRender* m_staminaGage[PLAYER_NUMBER] = { nullptr };
	/// @brief スタミナゲージカラー
	Vector4 m_StGageColor = { 0.3f,0.5f,0.2f,0.8f };
	/// @brief スタミナゲージのサイズ
	int m_StGageSize[WHnum] = { 320, 20 };
	/// @brief スタミナゲージの位置
	Vector3 m_StGagePos[4] = { /*1P*/{-450.0f, 180.0f, 0.0f}, /*2P*/{450.0f,180.0f, 0.0f}, /*3P*/{-450.0f, -320.0f, 0.0f}, /*4P*/{450.0f, -320.0f, 0.0f} };
	/// @brief スタミナ数値を%化するための数値
	float m_staminaComplement = 100.0f / 6.0f;
	
	/// @brief タイマー表示
	FontRender* m_timeFont = nullptr;

	Timer* m_timer = nullptr;
};

