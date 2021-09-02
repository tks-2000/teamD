#pragma once

class Player;
class PlayerCollide;
class PlayerEffect;
class PlayerMove;
class PlayerReinforcement;
class Timer;
class Ball;
class Se;
class Score;

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
	const float GetGuardDurability() const { return m_guardDurability; }

	/// @brief ガード耐久値を設定
	/// @param durability 設定するガード耐久値
	void SetGuardDurability(const float durability) { m_guardDurability = durability; }

	/// @brief ガード耐久値を低下させる
	/// @param damage ガード耐久値に与えるダメージ量
	void SetGuardDamage(const float damage) { m_guardDurability - damage; }

	/// @brief ガード耐久値低下量を取得する
	/// @return ガード耐久値低下量
	const float GetGuradDecreaseValue() const { return m_guardDecreaseValue; }

	/// @brief ガード時間を取得
	/// @return ガード時間
	const float GetGuardTime() const { return m_guardTime; }

	/// @brief ガード可能か？
	/// @return trueでガード可能 falseでガード不可能
	bool IsCanGuard();

	/// @brief ガードしているか？
	/// @return trueならガード中 falseならガードしていない
	bool IsGuard();

	/// @brief ガード破壊されているか？
	/// @return trueで破壊されている falseで破壊されていない
	bool IsGuardBreak() const { return m_guardBreak; }

	/// @brief キックが可能か？
	/// @return trueでキック可能 falseでキック不可能
	bool IsCanKick();

private:
	/// @brief 準備完了フラグ
	bool m_setUp = false;
	/// @brief プレイヤーの番号
	int m_playerNum = 0;
	/// @brief ガードフラグ
	bool m_guard = false;
	/// @brief ガード耐久力
	float m_guardDurability = 100.0f;
	/// @brief ガード耐久値低下量
	float m_guardDecreaseValue = 0.0f;
	/// @brief ガード耐久値回復量
	float m_guardRecoveryValue = 0.0f;
	/// @brief ガード破壊の状態
	bool m_guardBreak = false;
	/// @brief シールドにボールが触れたか？
	bool m_shieldHit = false;
	/// @brief 前フレームのガード状態フラグ記録用
	bool m_breakGuardPrevFrame = false;
	/// @brief ガード時間
	float m_guardTime = 0.0f;
	/// @brief ガード中の移動速度
	Vector3 m_guardMoveSpeed = Vector3::Zero;

	/// @brief プレイヤーからボールへのベクトル
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief ボールとの距離
	float m_ballDistance = 0.0f;

	/// @brief キック力
	float m_kickPower = 0.0f;

	/// @brief プレイヤーの吹き飛ぶ勢い
	float m_blowAwayRate = 0.0f;


	/// @brief 状態によって変化するパラメーターを決定する関数
	void DetermineParameters();

	/// @brief ガードの処理
	void Guard();

	/// @brief ガード耐久値回復の処理
	void GuardDecreaseRecovery();

	/// @brief キックの処理
	void Kick();

	/// @brief プレイヤー
	Player* m_player = nullptr;
	/// @brief プレイヤーの接触
	PlayerCollide* m_plCollide = nullptr;
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
	/// @brief スコア
	Score* m_score = nullptr;
};

