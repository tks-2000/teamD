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
	void Move();

	Vector3 GetPosition() { return m_position; }

private:
	Vector3 m_position = Vector3::Zero;
	Quaternion m_qRot = Quaternion::Identity;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed = Vector3::Zero;

	float m_Lstickx = 0.0f;
	float m_Lsticky = 0.0f;

	Lighting* m_lig = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
};

