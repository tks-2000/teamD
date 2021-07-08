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

	/// @brief ボール速表示用画像
	SpriteRender* m_ballSpeedMeter = nullptr;
	/// @brief ボール速表示用画像その2
	SpriteRender* m_ballSpeedMeterPin = nullptr;
	float PinRot = -60.0f;

	/// @brief ボールの速度
	float m_ballVelocity = 0.0f;

	wchar_t* m_text;

	FontRender* m_GuardDurability[PLAYER_NUMBER] = { nullptr };

	float m_playerGuardDurability[PLAYER_NUMBER] = { 0.0f };

	Player* m_player[PLAYER_NUMBER] = { nullptr };
	Ball* m_ball = nullptr;


	/// @brief 縦横挙列型
	enum DDSWH { Width, Height, WHnum }WH;
	/// @brief ゲージベースサイズ
	int m_gageBaseSize[2] = { 180,20 };
	/// @brief シールドゲージベースの初期化
	SpriteRender* m_ShGageBase[PLAYER_NUMBER] = { nullptr };
	/// @brief スタミナゲージベースの初期化
	SpriteRender* m_StGageBase[PLAYER_NUMBER] = { nullptr };
	/// @brief シールド用ゲージスプライトレンダー
	SpriteRender* m_shieldGage[PLAYER_NUMBER] = { nullptr };
	/// @brief アイコンの縦横のサイズ
	int m_IconSize = 25;
	/// @brief シールドゲージの色
	Vector4 m_ShGageColor = { 0.0f, 0.4f, 1.0f, 1.0f };
	/// @brief シールドブレイク時のゲージカラー
	Vector4 m_ShAlertColor = { 1.0f, 0.0f, 0.0f, 0.5f };
	/// @brief シールドゲージのサイズ
	int m_ShGageSize[2] = { 176, 16 };
	/// @ brief シールドゲージの位置
	Vector3 m_ShGagePos[4] = { /*1P*/{-485.0f, 200.0f, 0.0f}, /*2P*/{485.0f, 200.0f, 0.0f}, /*3P*/{-485.0f, -300.0f, 0.0f}, /*4P*/{485.0f, -300.0f, 0.0f} };
	/// @brief シールドブレイク時のアラートメッセージ
	FontRender* m_breakAlertMassege[PLAYER_NUMBER] = { nullptr };
	/// @brief シールドアラートメッセージの位置
	Vector2 m_ShAlertMassegePos[4] = { {-570.0f, 208.0f},{445.0f, 208.0f},{-570.0f, -293.0f},{445.0f, -293.0f} };
	/// @brief シールドゲージを示すアイコン
	SpriteRender* m_ShGageIcon[PLAYER_NUMBER] = { nullptr };
	/// @brief アイコンの位置
	Vector3 m_ShIconPos[PLAYER_NUMBER] = { {-585.0f,200.0f,0.0f},{585.0f,200.0f,0.0f},{-585.0f,-300,0.0f},{585.0f,-300.0f,0.0f} };
	/// @brief スタミナ用ゲージスプライトレンダー
	SpriteRender* m_staminaGage[PLAYER_NUMBER] = { nullptr };
	/// @brief スタミナゲージカラー
	Vector4 m_StGageColor = { 1.0f,1.0f,0.0f,1.0f };
	/// @brief スタミナ切れ中のゲージカラー
	Vector4 m_StAlertColor = { 0.5f, 0.5f, 0.0f, 0.8f };
	/// @brief スタミナゲージのサイズ
	int m_StGageSize[WHnum] = { 176, 16 };
	/// @brief スタミナゲージの位置
	Vector3 m_StGagePos[4] = { /*1P*/{-485.0f, 170.0f, 0.0f}, /*2P*/{485.0f,170.0f, 0.0f}, /*3P*/{-485.0f, -330.0f, 0.0f}, /*4P*/{485.0f, -330.0f, 0.0f} };
	/// @brief スタミナアラートメッセージ
	FontRender* m_tiredAlertMassege[PLAYER_NUMBER] = { nullptr };
	/// @brief スタミナアラートメッセージの位置
	Vector2 m_StAlertMassegePos[4] = { {-570.0f, 178.0f},{448.0f, 178.0f},{-570.0f, -322.0f},{448.0f, -322.0f} };
	/// @brief スタミナ数値を%化するための数値
	float m_staminaComplement = 100.0f / 6.0f;
	/// @brief スタミナゲージを示すアイコン
	SpriteRender* m_StGageIcon[PLAYER_NUMBER] = { nullptr };
	/// @brief スタミナゲージアイコンの位置
	Vector3 m_StIconPos[PLAYER_NUMBER] = { {-585.0f,170.0f,0.0f},{585.0f,170.0f,0.0f},{-585.0f,-330,0.0f},{585.0f,-330.0f,0.0f} };

	/// @brief シールドゲージ外殻たち
	SpriteRender* m_ShGageBegin[PLAYER_NUMBER] = { nullptr };
	Vector3 m_ShGageBeginPos[PLAYER_NUMBER] = { { -597.0f, 200.0f, 0.0f },{597.0f, 200.0f, 0.0f},{-597.0f,-300.0f, 0.0f},{597.0f, -300.0f, 0.0f} };
	SpriteRender* m_ShGageBody[PLAYER_NUMBER] = { nullptr };
	Vector3 m_ShGageBodyPos[PLAYER_NUMBER] = { { -494.0f, 200.0f, 0.0f }, {494.0f, 200.0f, 0.0f}, {-494.0f, -300.0f, 0.0f}, {494.0f, -300.0f, 0.0f} };
	SpriteRender* m_ShGageFinal[PLAYER_NUMBER] = { nullptr };
	Vector3 m_ShGageFinalPos[4] = { { -400.0f,200.0f,0.0f },{400.0f, 200.0f, 0.0f},{-400.0f, -300.0f,  0.0f},{400.0f, -300.0f, 0.0f} };

	/// @brief スタミナゲージ外殻たち
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

	/// @brief タイマー表示
	FontRender* m_timeFont = nullptr;
	/// @brief タイマーのフレーム
	SpriteRender* m_timerFrame = nullptr;
	/// @brief タイマーヘッダ
	FontRender* m_timerHedder = nullptr;

	Timer* m_timer = nullptr;

	Score* m_score = nullptr;
};

