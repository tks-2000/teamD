#pragma once

class Player;
class PlayerEffect;
class PlayerMove;
class PlayerReinforcement;
class Timer;
class Ball;
class Se;

/// @brief プレイヤーのアクション(キックとガード)を制御するクラス
class PlayerAction : public IGameObject
{
public:
	PlayerAction();
	~PlayerAction();
	bool Start();
	void Update();

	/// @brief 自分が何Pかを設定
	/// @param num 設定するプレイヤー番号
	void SetPlayerNumber(const int num);

	/// @brief ガード耐久値を取得
	/// @return ガード耐久値
	float GetGuardDurability() const { return m_guardDurability; }

	/// @brief ガードフラグを取得。
	/// @return trueならガード中。falseならガードしていない。
	bool IsGuard() const {
		return m_guard;
	}
	/// @brief ガード破壊されているか？
	/// @return trueで破壊されている。 falseで破壊されていない。
	bool IsGuardBreak() const {
		return m_breakGuard;
	}

private:
	/// @brief プレイヤーの番号
	int m_playerNum = 0;

	/// @brief ガードフラグ
	bool m_guard = false;
	/// @brief ガード耐久力
	float m_guardDurability = 100.0f;
	/// @brief ガード耐久値低下量
	float m_guradDecreaseValue = 0.0f;
	/// @brief ガード破壊の状態
	bool m_breakGuard = false;
	/// @brief シールドにボールが触れたか？
	bool m_shieldHit = false;
	/// @brief 前フレームのガード状態フラグ記録用
	bool m_breakGuardPrevFrame = false;
	/// @brief ジャストガード判定になる時間
	float m_justGuardTime = 0.0f;
	/// @brief ガード中の移動速度
	Vector3 m_guardMoveSpeed = Vector3::Zero;

	/// @brief プレイヤーからボールへのベクトル
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief ボールとの距離
	float m_ballDistance = 0.0f;

	/// @brief キック可能かどうかのフラグ
	bool m_kickFlag = false;
	/// @brief キック力
	float m_kickPower = 0.0f;

	/// @brief ガード可能か調べる
	/// @return trueでガード可能。falseでガード不可能。
	bool CheckGuard();

	/// @brief ガードの処理
	void Guard();

	/// @brief ガード中のボール接触処理
	void GuardCollide();

	/// @brief プレイヤー
	Player* m_player = nullptr;
	/// @brief プレイヤーのエフェクト
	PlayerEffect* m_plEffect = nullptr;
	/// @brief プレイヤーの移動
	PlayerMove* m_plMove = nullptr;
	/// @brief プレイヤーの強化
	PlayerReinforcement* m_plReinforcement = nullptr;
	/// @brief タイマー
	Timer* m_timer = nullptr;
	/// @brief ボール
	Ball* m_ball = nullptr;
	/// @brief サウンドエフェクト
	Se* m_se = nullptr;
};

