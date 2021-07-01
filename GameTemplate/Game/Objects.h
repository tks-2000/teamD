#pragma once

class Ball;
class GameDirector;
class Box;


class Objects : public IGameObject
{
public:
	Objects();
	~Objects();
	bool Start();
	void Update();

	void SetObjects(int num);

	void SetDelFlag(int num) { m_delFlag[num] = true; }

private:
	/// @brief �I�u�W�F�N�g�̍��W
	Vector3 m_position;

	Vector3 m_setPos[OBJECTS_NUMBER];

	Vector3 m_toBallVec[OBJECTS_NUMBER];

	Vector3 m_fallSpeed[OBJECTS_NUMBER];

	//Vector3 m_colliderPos[OBJECTS_NUMBER];

	bool m_delFlag[OBJECTS_NUMBER] = { false };

	int m_setNum = 0;

	float m_reSpawnTime[OBJECTS_NUMBER] = { 0.0f };

	/// @brief �{�[��
	Ball* m_ball = nullptr;
	/// @brief �Q�[���f�B���N�^�[
	GameDirector* m_gameDirector = nullptr;
	/// @brief �{�[��
	Box* m_box[OBJECTS_NUMBER] = { nullptr };
};

