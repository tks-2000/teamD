#pragma once

class Player;
class PlayerAction;
class PlayerMove;
class PlayerReinforcement;
class Ball;
class Se;
class Score;

/// @brief プレイヤーの衝突を制御するクラス
class PlayerCollide : public IGameObject
{
public:
	PlayerCollide();
	~PlayerCollide();
	bool Start();
	void Update();

	/// @brief 自分が何Pかを設定
	/// @param num 設定するプレイヤー番号
	void SetPlayerNumber(const int num);

	/// @brief プレイヤーからボールに向かって伸びるベクトルを取得
	/// @return プレイヤーからボールに向かう方向ベクトルの参照
	const Vector3& GetToBallVector() const { return m_toBallVec; }

	/// @brief プレイヤーとボールとの距離を取得
	/// @return プレイヤーとボールの距離
	const float GetBallDistance() const { return m_ballDistance; }

private:
	/// @brief 準備完了フラグ
	bool m_setUp = false;
	/// @brief プレイヤーの番号
	int m_playerNum = 0;
	/// @brief プレイヤーからボールへのベクトル
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief ボールとの距離
	float m_ballDistance = 0.0f;
	/// @brief プレイヤーの吹き飛ぶ勢い
	float m_blowAwayRate = 0.0f;
	/// @brief ガード中にボールが触れたか？
	bool m_guradHit = false;
	/// @brief ジャストガード判定になる時間
	float m_justGuardTime = 0.0f;
	/// @brief ガード耐久値低下量
	float m_guardDecreaseValue = 0.0f;

	/// @brief 状態によって変化するパラメーターを決定する関数
	void DetermineParameters();

	/// @brief ボールに向かうベクトルを計算
	void ToBallVectorCalculation();

	/// @brief ボールとの距離を計算
	void BallDistanceCalculation();

	/// @brief ボールと接触する処理
	void BallCollide();

	/// @brief ガード中のボール接触処理
	void GuardCollide();

	/// @brief プレイヤー
	Player* m_player = nullptr;
	/// @brief プレイヤーアクション
	PlayerAction* m_plAction = nullptr;
	/// @brief プレイヤーの移動
	PlayerMove* m_plMove = nullptr;
	/// @brief プレイヤーエフェクト
	PlayerEffect* m_plEffect = nullptr;
	/// @brief プレイヤー強化
	PlayerReinforcement* m_plReinforcement = nullptr;
	/// @brief サウンドエフェクト
	Se* m_se = nullptr;
	/// @brief ボール
	Ball* m_ball = nullptr;
	/// @brief スコア
	Score* m_score = nullptr;

	/// @brief アイテムの数
	enum {ITEM_NUM = 4};

	
};

