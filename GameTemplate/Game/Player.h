#pragma once
#include "effect/Effect.h"

class Lighting;
class SkinModelRender;
class Ball;
class Effect;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

	/// @brief プレイヤーが何番かを設定
	/// @param num プレイヤー番号
	void SetPlayerNumber(int num);

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

	/// @brief ガードの処理
	void Guard();

	/// @brief リスポーンの処理
	void ReSpawn() { m_position = m_startPos; m_charaCon.SetPosition(m_position); };

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
	/// @brief プレイヤーのスタート時の座標
	Vector3 m_startPos = Vector3::Zero;
	/// @brief プレイヤーのシンボルカラー
	Vector3 m_playerColor = Vector3::Zero;
	/// @brief プレイヤーにかかる摩擦力
	float m_friction = 0.0f;
	
	/// @brief ボールとの距離
	float m_ballDistance = 0.0f;
	/// @brief キック力
	float m_kickPower = 0.0f;
	/// @brief ガードフラグ
	bool m_guard = false;
	/// @brief 重力
	float m_gravity = 0.0f;
	/// @brief ダメージフラグ
	bool m_damage = false;
	/// @brief ダメージを受けて動けるようになるまでのタイマー
	float m_damageTime = 0.0f;

	/// @brief Lスティックの横入力
	float m_Lstickx = 0.0f;
	/// @brief Lスティックの縦入力
	float m_Lsticky = 0.0f;

	/// @brief ガード耐久力
	float m_guardDurability = 100.0f;
	/// @brief ガードの状態
	bool m_breakGuard = false;
	/// @brief ガード破壊によって起きるダウン状態
	//bool m_breakDown = false;

	/// @brief キャラクターコントローラー
	CharacterController m_charaCon;
	/// @brief ライティング
	Lighting* m_lig = nullptr;
	/// @brief スキンモデルレンダラー
	SkinModelRender* m_skinModelRender = nullptr;
	/// @brief ボール
	Ball* m_ball = nullptr;
	/// @brief ボールをキックした時のエフェクト
	Effect m_kickEffect;
	/// @brief ガード時のエフェクト
	Effect m_guardEffect;
	int m_guardEffectCouter = 0;
};

