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
	/// @brief 準備完了フラグ
	bool m_setUp = false;
	/// @brief オブジェクトの座標
	Vector3 m_position;

	Vector3 m_setPos[OBJECTS_NUMBER];

	Vector3 m_toBallVec[OBJECTS_NUMBER];

	Vector3 m_fallSpeed[OBJECTS_NUMBER];

	//Vector3 m_colliderPos[OBJECTS_NUMBER];

	/// @brief 箱の削除フラグ
	bool m_delFlag[OBJECTS_NUMBER] = { false };
	/// @brief アイテムの削除フラグ
	bool m_itemDelFlag[OBJECTS_NUMBER] = { false };
	/// @brief 箱が開いているかどうかのフラグ
	bool m_boxOpenFlag[OBJECTS_NUMBER] = { false };
	/// @brief アイテムが出現可能かどうかのフラグ
	bool m_itemCanSpawnFlag[OBJECTS_NUMBER] = { false };

	Vector3 m_itemSpownPos[OBJECTS_NUMBER] = { Vector3::Zero,Vector3::Zero, Vector3::Zero, Vector3::Zero };

	int m_setNum = 0;

	float m_reSpawnTime[OBJECTS_NUMBER] = { 0.0f };

	/// @brief ボール
	Ball* m_ball = nullptr;
	/// @brief ゲームディレクター
	GameDirector* m_gameDirector = nullptr;
	/// @brief ボール
	Box* m_box[OBJECTS_NUMBER] = { nullptr };

	Item* m_item[OBJECTS_NUMBER] = { nullptr };

	Se* m_se = nullptr;
};

