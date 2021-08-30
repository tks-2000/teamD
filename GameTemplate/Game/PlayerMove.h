#pragma once

class Player;
class PlayerAction;
class PlayerReinforcement;
class Ball;
class Se;
class Score;

/// @brief プレイヤーの移動を制御するクラス
class PlayerMove : public IGameObject
{
public:
	PlayerMove();
	~PlayerMove();
	bool Start()override;
	void Update()override;

	/// @brief プレイヤーの番号を設定
	/// @param plNum 設定するプレイヤー番号
	void SetPlayerNumber(const int plNum);

	/// @brief プレイヤーの向いている方向を入手
	/// @return プレイヤーの向いている方向
	const Vector3& GetDirection() const { return m_direction; }

	/// @brief プレイヤーの移動速度を入手
	/// @return プレイヤーの移動速度
	const Vector3& GetMoveSpeed() const { return m_moveSpeed; }

	/// @brief プレイヤーの移動速度を設定
	/// @param move プレイヤーに設定する移動速度
	void SetMoveSpeed(const Vector3& move) { m_moveSpeed = move; }

	/// @brief ダッシュしているか判定
	/// @return trueでダッシュしている falseでダッシュしていない
	bool IsDash() const;

private:
	/// @brief プレイヤーの番号
	int m_playerNum = 0;
	/// @brief Lスティックの横入力
	float m_Lstickx = 0.0f;
	/// @brief Lスティックの縦入力
	float m_Lsticky = 0.0f;
	/// @brief プレイヤーの速度
	float m_moveVelocity = 0.0f;
	/// @brief プレイヤーに加算する速度
	float m_addVelocity = 0.0f;
	/// @brief プレイヤーの移動速度
	Vector3 m_moveSpeed = Vector3::Zero;
	/// @brief プレイヤーにかかる摩擦力
	float m_friction = 0.0f;
	/// @brief 重力
	float m_gravity = 0.0f;
	/// @brief ダッシュ可能フラグ
	bool m_dash = true;
	/// @brief プレイヤーのスタミナ
	float m_stamina = 0.0f;
	/// @brief スタミナ低下量
	float m_staminaDecreaseValue = 0.0f;
	/// @brief プレイヤーの向いている方向
	Vector3 m_direction = Vector3::Zero;
	/// @brief プレイヤーのスタート時の座標
	Vector3 m_startPos = Vector3::Zero;
	/// @brief リスポーンボタンを押している時間
	float m_reSpawnTime = 0.0f;
	/// @brief プレイヤーからボールへのベクトル
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief ボールとの距離
	float m_ballDistance = 0.0f;
	/// @brief プレイヤーが吹き飛ぶ勢い
	float m_blowAwayRate = 0.0f;
	/// @brief プレイヤー
	Player* m_player = nullptr;
	/// @brief プレイヤーアクション
	PlayerAction* m_plAction = nullptr;
	/// @brief プレイヤーエフェクト
	PlayerEffect* m_plEffect = nullptr;
	/// @brief プレイヤー強化
	PlayerReinforcement* m_plReinforcement = nullptr;
	/// @brief サウンドエフェクト
	Se* m_se = nullptr;
	/// @brief ボール
	Ball* m_ball = nullptr;
	/// @brief スコア
	Score* m_score = nullptr;
	/// @brief 準備完了フラグ
	bool m_setUp = false;

	/// @brief 移動
	void Move();

	/// @brief 回転
	void Rotation();

	/// @brief 状態によって変化するパラメーターを決定する関数
	void DetermineParameters();

	/// @brief 歩行の処理
	void Walk();

	/// @brief ダッシュの処理
	void Dash();

	/// @brief スタミナ回復の処理
	void StaminaRecovery();

	/// @brief スタミナを管理する関数
	void StaminaManagement();

	/// @brief ボールに向かうベクトルを計算
	void ToBallVectorCalculation();

	/// @brief ボールとの距離を計算
	void BallDistanceCalculation();

	/// @brief ボールとぶつかる処理
	void BallCollide();

	/// @brief プレイヤーの移動を停止
	void MoveStop() { m_moveSpeed.x = 0.0f; m_moveSpeed.z = 0.0f; }
};

