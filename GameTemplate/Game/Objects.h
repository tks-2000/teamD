#pragma once

class Player;
class Ball;
class GameUI;
class SkinModelRender;
class GameDirector;


class Objects : public IGameObject
{
public:
	Objects();
	~Objects();
	bool Start();
	void Update();

	void ballCollider(int num);

	void SetObjects(int num);

	void DistanceCalculation();
	
private:
	/// @brief オブジェクトの座標
	Vector3 m_position[OBJECTS_NUMBER];

	Vector3 m_setPos[OBJECTS_NUMBER];

	Vector3 m_toBallVec[OBJECTS_NUMBER];

	Vector3 m_fallSpeed[OBJECTS_NUMBER];

	Vector3 m_colliderPos[OBJECTS_NUMBER];

	int SetNum = 0;

	int SetDelNum = 0;

	int m_playerNum = 0;

	float m_fall = ZeroF;

	float m_ballDistance[OBJECTS_NUMBER] = { 0.0f };

	bool m_delFlag[OBJECTS_NUMBER] = { false };

	/// @brief スキンモデルレンダラー
	SkinModelRender* m_skinModelRender[OBJECTS_NUMBER] = { nullptr };
	/// @brief プレイヤー
	Player* m_player[PLAYER_NUMBER] = { nullptr };
	/// @brief ボール
	Ball* m_ball = nullptr;
	/// @brief ゲームUI
	GameUI* m_ui = nullptr;

	CharacterController m_charaCon[PLAYER_NUMBER];


	GameDirector* m_gameDirector = nullptr;


};

