#pragma once

class Player;
class Ball;
class SkinModelRender;
class Score;
class Objects;
class Timer;


class Box : public IGameObject
{
public:
	Box();
	~Box();
	bool Start();
	void Update();

	void ballCollider();

	void SetBoxPos(Vector3 pos,int num);

	void DistanceCalculation();

private:

	Vector3 m_position = Vector3::Zero;

	Vector3 m_setPos = Vector3::Zero;

	Vector3 m_toBallVec = Vector3::Zero;

	Vector3 m_fallSpeed = Vector3::Zero;

	Vector3 m_colliderPos = Vector3::Zero;

	int m_setNum = 0;

	int m_boxNum = 0;

	//int m_playerNum = 0;

	float m_ballDistance = 0.0f;

	float m_fall = ZeroF;

	/// @brief プレイヤー
	Player* m_player[PLAYER_NUMBER] = { nullptr };
	/// @brief ボール
	Ball* m_ball = nullptr;
	/// @brief スキンモデルレンダラー
	SkinModelRender* m_skinModelRender = nullptr;
	/// @brief キャラクターコントローラー
	CharacterController m_charaCon;
	/// @brief スコア
	Score* m_score = nullptr;
	/// @brief オブジェクト
	Objects* m_objects = nullptr;
	/// @brief タイマー
	Timer* m_timer = nullptr;

};

