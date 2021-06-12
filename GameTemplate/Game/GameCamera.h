#pragma once

class Player;
class BackGround;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	void Move();
	void Rotation();

private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_toPosition = Vector3::Zero;
	Vector3 m_targetPos = Vector3::Zero;
	Quaternion m_qRotY = Quaternion::Identity;
	Quaternion m_qRotX = Quaternion::Identity;
	float m_angleX = 0.0f;

	Player* m_player = nullptr;
	BackGround* m_backGround = nullptr;
};

