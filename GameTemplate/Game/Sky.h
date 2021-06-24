#pragma once
class SkinModelRender;

class Sky : public IGameObject
{
public:
	Sky();

	~Sky();

	bool Start();

	void Update();
	/// @brief スケールセッター(Vector3版)、デフォルト1000
	void SetScaleV(Vector3 Sca = { 1000.0f, 1000.0f, 1000.0f });
	/// @brief スケールセッター(float版)、デフォルト1000
	void SetScaleF(float Sca = 1000.0f);
	
private:
	/// @brief アクティブフラグ
	bool m_Start = false;
	/// @brief 背景の座標ステージが内側になるよう設定すべし
	Vector3 Position = Vector3::Zero;
	/// @brief スケール、ステージの大きさと相談
	Vector3 Scale = Vector3::Zero;
	/// @brief スキンレンダー
	SkinModelRender* m_skinModelRender = nullptr;
	/// @brief モデルの回転
	Quaternion m_rotation = Quaternion::Identity;
	/// @brief モデルの回転角
	float ang = 0;
};

