#pragma once

class Ball;
class GameDirector;
class Box;
class Item;
class Se;

class Objects : public IGameObject
{
public:
	Objects();
	~Objects();
	bool Start();
	void Update();

	void SetObjects(int num);
	void SetItems(int num);

	void SetDelFlag(int num) { m_delFlag[num] = true; }
	void SetItemDelFlag(int num) { m_itemDelFlag[num] = true; }
	void SetItemSpawnPos(const int num, const Vector3& pos) { m_itemSpownPos[num] = pos; }

	bool IsBoxOpen(int num) { return m_boxOpenFlag[num]; }

	void SetBoxOpen(int num) { m_boxOpenFlag[num] = true; }

private: 
	/// @brief ���������t���O
	bool m_setUp = false;
	/// @brief �I�u�W�F�N�g�̍��W
	Vector3 m_position;

	Vector3 m_setPos[OBJECTS_NUMBER];

	Vector3 m_toBallVec[OBJECTS_NUMBER];

	Vector3 m_fallSpeed[OBJECTS_NUMBER];

	//Vector3 m_colliderPos[OBJECTS_NUMBER];

	/// @brief ���̍폜�t���O
	bool m_delFlag[OBJECTS_NUMBER] = { false };
	/// @brief �A�C�e���̍폜�t���O
	bool m_itemDelFlag[OBJECTS_NUMBER] = { false };
	/// @brief �����J���Ă��邩�ǂ����̃t���O
	bool m_boxOpenFlag[OBJECTS_NUMBER] = { false };
	/// @brief �A�C�e�����o���\���ǂ����̃t���O
	bool m_itemCanSpawnFlag[OBJECTS_NUMBER] = { false };

	Vector3 m_itemSpownPos[OBJECTS_NUMBER] = { Vector3::Zero,Vector3::Zero, Vector3::Zero, Vector3::Zero };

	int m_setNum = 0;

	float m_reSpawnTime[OBJECTS_NUMBER] = { 0.0f };

	/// @brief �{�[��
	Ball* m_ball = nullptr;
	/// @brief �Q�[���f�B���N�^�[
	GameDirector* m_gameDirector = nullptr;
	/// @brief �{�[��
	Box* m_box[OBJECTS_NUMBER] = { nullptr };

	Item* m_item[OBJECTS_NUMBER] = { nullptr };

	Se* m_se = nullptr;
};

