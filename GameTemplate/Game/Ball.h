#pragma once

class Lighting;
class SkinModelRender;

class Ball : public IGameObject
{
public:
	Ball();
	~Ball();
	bool Start();
	void Update();

	void Move();

	void MoveStart() { m_moveFlag = true; }

	Vector3 GetPosition() { return m_position; }

	void SetMoveSpeed(Vector3 speed) { m_moveSpeed = speed; }

	void SetMoveDirection(Vector3 dir) { m_moveDirection = dir; m_moveDirection.Normalize(); }

private:
	Vector3 m_position = Vector3::Zero;
	Quaternion m_qRot = Quaternion::Identity;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_moveDirection = Vector3::Zero;
	bool m_moveFlag = false;

	Lighting* m_lig = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
};

