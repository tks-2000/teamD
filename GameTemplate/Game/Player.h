#pragma once

class Lighting;
class SkinModelRender;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

	/// @brief 移動の処理
	void Move();

	/// @brief 回転の処理
	void Rotation();

	/// @brief プレイヤーの座標を入手
	/// @return 座標
	Vector3 GetPosition() { return m_position; }

private:
	/// @brief プレイヤーの座標
	Vector3 m_position = Vector3::Zero;
	/// @brief プレイやーの回転
	Quaternion m_qRot = Quaternion::Identity;
	/// @brief プレイヤーの拡大率
	Vector3 m_scale = Vector3::One;
	/// @brief プレイヤーの移動速度
	Vector3 m_moveSpeed = Vector3::Zero;

	/// @brief Lスティックの横入力
	float m_Lstickx = 0.0f;
	/// @brief Lスティックの縦入力
	float m_Lsticky = 0.0f;

	/// @brief ライティング
	Lighting* m_lig = nullptr;
	/// @brief スキンモデルレンダラー
	SkinModelRender* m_skinModelRender = nullptr;
};

