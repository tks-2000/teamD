#pragma once
#include "effect/Effect.h"


class Lighting;
class SkinModelRender;
class Effect;

class Ball : public IGameObject
{
public:
	Ball();
	~Ball();
	bool Start();
	void Update();

	/// @brief 移動の処理
	void Move();

	void Rotation();
	/// @brief 軌跡用エフェクトの再生処理
	void PlayTrackEffect();

	/// @brief ボールの移動を開始する
	void MoveStart() { m_moveFlag = true; }

	/// @brief ボールが動いているか？
	/// @return ボールの移動フラグ
	bool IsMove() { return m_moveFlag; }

	void BounceX() { m_moveDirection.x *= -1.0f; }

	void BounceZ() { m_moveDirection.z *= -1.0f; }

	/// @brief ボールの座標を入手
	/// @return ボールの座標
	Vector3 GetPosition() { return m_position; }

	/// @brief ボールの移動速度を設定
	/// @param speed ボールに設定したい速度
	void SetMoveSpeed(Vector3 speed) { m_moveSpeed = speed; }

	/// @brief ボールに加える力を設定
	/// @param kickPower キック力
	void Acceleration(float kickPower) { m_moveVelocity += kickPower; }
	
	/// @brief ボールの速度を入手
	/// @return ボールの速度
	float GetVelocity() { return m_moveVelocity; }


	void SetVelocity(float vel) { m_moveVelocity = vel; }

	Vector3 GetMoveDirection() { return m_moveDirection; }

	/// @brief ボールの移動方向を設定
	/// @param dir ボールを進ませたい方向
	void SetMoveDirection(Vector3 dir) { m_moveDirection = dir; m_moveDirection.y = 0.0f; m_moveDirection.Normalize(); }

	void SetBallLightColor(Vector3 color) { m_pointLigColor = color; }

private:
	/// @brief ボールの座標
	Vector3 m_position = Vector3::Zero;
	/// @brief ボールの回転
	Quaternion m_qRot = Quaternion::Identity;

	Vector3 m_scale = Vector3::One;

	Vector3 m_axisRotation = Vector3::Zero;
	/// @brief ボールの移動速度
	Vector3 m_moveSpeed = Vector3::Zero;
	/// @brief ボールの移動方向
	Vector3 m_moveDirection = Vector3::Zero;
	/// @brief ボールの速度
	float m_moveVelocity = 0.0f;
	/// @brief ボールの移動フラグ
	bool m_moveFlag = false;

	float m_angle = 0.0f;

	float m_gravity = 0.0f;

	Vector3 m_pointLigColor = Vector3::Zero;

	CharacterController m_charaCon;
	Lighting* m_lig = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
	
	/// @brief 軌跡用エフェクト
	Effect m_ballTrack;
};

