#pragma once

class SkinModelRender;
class GameDirector;
class Objects;
class Player;

class Item : public IGameObject
{
public:
	Item();
	~Item();
	bool Start();
	void Update();

	void SetPosition(const Vector3& pos) { m_position = pos; }
	void SetNumber(int num) { m_myNo = num; }

	

	void PlayerDistanceCalculation();

	enum enItemType {
		enAttackUp,
		enGuardUp,
		enSpeedUp
	};

	void SetItem(enItemType itemType) { m_itemState = itemType; ItemModelNewGO(); m_newGoFlag = true; }

private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_toPos[PLAYER_NUM] = { Vector3::Zero ,Vector3::Zero ,Vector3::Zero ,Vector3::Zero };
	float m_distance[PLAYER_NUM] = { 0.0f };
	Quaternion m_qRot = Quaternion::Identity;
	SkinModelRender* m_skinModelRender = nullptr;
	int m_myNo = 4;
	Player* m_player[PLAYER_NUM] = { nullptr };
	GameDirector* m_gameDirector = nullptr;
	Objects* m_objects = nullptr;
	enItemType m_itemState = enAttackUp;
	bool m_newGoFlag = false;

	void ItemModelNewGO();

};

