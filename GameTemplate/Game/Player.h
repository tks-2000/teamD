#pragma once

class Lighting;
class SkinModelRender;
class Ball;

class Player : public IGameObject
{
public:
	Player();
	Player(int num);
	~Player();
	bool Start();
	void Update();

	/// @brief 移動の処理
	void Move();

	/// @brief 回転の処理
	void Rotation();

	/// @brief プレイヤーの座標を入手
	/// @return プレイヤーの座標
	Vector3 GetPosition() { return m_position; }

	/// @brief ボールを蹴る処理
	void KickBall();

	/// @brief ボールとの距離を計算
	void BallDistanceCalculation();

	/// @brief ボールとぶつかる処理
	void BallCollide();

private:
	/// @brief プレイヤーの番号
	int m_myNumber = 0;
	/// @brief プレイヤーの座標
	Vector3 m_position = Vector3::Zero;
	/// @brief プレイやーの回転
	Quaternion m_qRot = Quaternion::Identity;
	/// @brief プレイヤーの拡大率
	Vector3 m_scale = Vector3::One;
	/// @brief プレイヤーの速度
	float m_moveVelocity = 0.0f;
	/// @brief プレイヤーの移動速度
	Vector3 m_moveSpeed = Vector3::Zero;
	/// @brief プレイヤーの向いている方向
	Vector3 m_direction = Vector3::Zero;
	
	/// @brief ボールとの距離
	float m_ballDistance = 0.0f;
	/// @brief キック力
	float m_kickPower = 0.0f;

	/// @brief Lスティックの横入力
	float m_Lstickx = 0.0f;
	/// @brief Lスティックの縦入力
	float m_Lsticky = 0.0f;

	/// @brief ライティング
	Lighting* m_lig = nullptr;
	/// @brief スキンモデルレンダラー
	SkinModelRender* m_skinModelRender = nullptr;
	/// @brief ボール
	Ball* m_ball = nullptr;
};

