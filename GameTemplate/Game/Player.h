#pragma once
#include "effect/Effect.h"

class Lighting;
class SkinModelRender;
class Ball;
class Effect;
class GameUI;

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

	/// @brief 
	void SetKillerPlayerNumber(int num) { m_killerPlayerNumber = num; }

	/// @brief 
	int GetKillerPlayerNumber() { return m_killerPlayerNumber; }

	/// @brief 移動の処理
	void Move();

	/// @brief 回転の処理
	void Rotation();

	/// @brief プレイヤーの座標を入手
	/// @return プレイヤーの座標
	Vector3 GetPosition() { return m_position; }

	void IsKick();

	/// @brief ボールを蹴る処理
	void KickBall();

	/// @brief ボールとの距離を計算
	void BallDistanceCalculation();

	/// @brief ボールとぶつかる処理
	void BallCollide();

	/// @brief ガードの処理
	void Guard();

	float GetGuardDurability() { return m_guardDurability; }

	/// @brief リスポーンの処理
	void ReSpawn();

	void Muteki();

	void Animation();

private:
	/// @brief プレイヤーの番号
	int m_myNumber = 0;
	/// @brief 
	int m_killerPlayerNumber = 0;
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
	/// @brief プレイヤーからボールへのベクトル
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief プレイヤーが死んだかどうかのフラグ
	bool m_dieFlag = false;
	/// @brief プレイヤーがリスポーンした時の無敵時間
	float m_mutekiTime = 0.0f;
	/// @brief ボールとの距離
	float m_ballDistance = 0.0f;
	/// @brief キック可能かどうかのフラグ
	bool m_kickFlag = false;
	/// @brief キック力
	float m_kickPower = 0.0f;
	/// @brief ガードフラグ
	bool m_guard = false;
	/// @brief 重力
	float m_gravity = 0.0f;
	/// @brief ダメージフラグ
	bool m_damage = false;
	/// @brief 前フレームのダメージフラグ
	bool m_damagePrevFrame = false;
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
	/// @brief 前フレームのガード状態フラグ記録用
	bool m_breakGuardPrevFrame = false;
	/// @brief ジャストガード判定になる時間
	float m_justGuardTime = 0.0f;
	/// @brief キック力が上がるフラグ
	bool m_kickPowerUp = false;
	/// @brief キック力が上がる時間
	float m_powerUpTime = 0.0f;
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
	
	//エフェクト関連//
	/// @brief ボールをキックした時のエフェクト
	Effect m_kickEffect;
	/// @brief ガード時のエフェクト
	Effect m_guardEffect;
	//ガードエフェクトを一定間隔で発生させるためのカウンター
	int m_guardEffectCouter = 0;
	/// @brief ガード発生の予兆エフェクト
	Effect m_guardBeginEffect;
	/// @brief ガードブレイクエフェクト
	Effect m_guardBreakEffect;
	/// @brief シールド回復エフェクト
	Effect m_shieldRepairEffect;
	/// @brief シールド回復フラグ
	bool m_isRepair = true;
	/// @brief ガードヒットエフェクト
	Effect m_shieldHitEffect;
	/// @brief ガードヒットエフェクトを一定間隔で発生させるためのカウンター
	int m_shieldHitEffectCounter = 0;
	/// @brief キックのクールタイムカウンター
	int m_kickCooler = 0;
	/// @brief キックのクールタイム中かの正負
	bool m_kickCooling = false;
	/// @brief m_kickFlagとは別の可不可フラグ
	bool m_readyKick = true;
	//行動不能時エフェクト(ピヨり)
	Effect m_knockOutEffect;

	enum enAnimationClips
	{
		enAnimation_Idle,
		enAnimation_Walk,
		enAnimation_Num
	};

	enAnimationClips m_anim = enAnimation_Idle;

	AnimationClip m_animationClips[enAnimation_Num];

	GameUI* m_ui = nullptr;

};

