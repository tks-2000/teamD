#pragma once
#include "effect/Effect.h"

class Timer;
class Score;
class Lighting;
class SkinModelRender;
class Ball;
class PlayerAction;
class PlayerCollide;
class PlayerEffect;
class PlayerMove;
class PlayerReinforcement;
class Effect;
class GameUI;
class Se;

//自分のアイテムバフが今何に変わったかを伝えるための列挙体
enum ItemBuffChange
{
	enItemBuff_Kick,
	enItemBuff_Guard,
	enItemBuff_Speed,
	enItemBuff_Num
};

enum enPlayerNumber
{
	enPlayer1,
	enPlayer2,
	enPlayer3,
	enPlayer4,
	enPlayerNum
};

enum enAnimationClips
{
	enAnimation_Idle,
	enAnimation_Walk,
	enAnimation_Run,
	enAnimation_Num
};

/// @brief プレイヤークラス。
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start()override;
	void Update()override;

	/// @brief 自分が何Pかを設定
	/// @param num 設定するプレイヤー番号
	void SetPlayerNumber(int num);

	/// @brief 移動の処理
	void Move();

	/// @brief 回転の処理
	void Rotation();

	/// @brief プレイヤーの座標を入手
	/// @return プレイヤーの座標のconst参照
	const Vector3& GetPosition() const { return m_position; }

	/// @brief プレイヤーの座標を設定
	/// @param pos プレイヤーに設定する座標
	void SetPosition(const Vector3& pos) { m_position = pos; }

	/// @brief プレイヤーの向いている方向を入手
	/// @return プレイヤーの向いている方向のconst参照
	const Vector3& GetDirection() const { return m_direction; }

	/// @brief プレイヤーの方向を設定
	/// @param dir プレイヤーに設定する方向
	void SetDirection(const Vector3& dir) { m_direction = dir; }

	/// @brief プレイヤーの移動速度を入手
	/// @return プレイヤーの移動速度のconst参照
	const Vector3& GetMoveSpeed() const { return m_moveSpeed; }

	/// @brief プレイヤーの移動速度を設定
	/// @param move プレイヤーに設定する移動速度
	void SetMoveSpeed(const Vector3& move) { m_moveSpeed = move; }

	/// @brief 回転を設定
	/// @param qRot 設定するクォータニオン
	void SetQrot(const Quaternion& qRot) { m_qRot = qRot; }

	/// @brief ボールに向かうベクトルを取得。
	/// @return ボールに向かうベクトルのconst参照。
	const Vector3& GetToBallVec() const { return m_toBallVec; }

	/// @brief ボールとぶつかる処理
	void BallCollide();

	/// @brief ガードの処理
	void Guard();

	/// @brief ガード耐久値を取得
	/// @return ガード耐久値
	float GetGuardDurability() const { return m_guardDurability; }

	/// @brief リスポーンの処理
	void ReSpawn();
	/// @brief リスポーン時の無敵時間の処理
	void Muteki();
	/// @brief スタミナ値ゲッター
	float GetStamina() const { return m_stamina; }
	/// @brief ダッシュフラグゲッター
	bool GetDashFlg() const { return m_dash; }

	/// @brief アニメーションを進める関数。
	void Animation();

	/// @brief 再生するアニメーションを設定
	/// @param anim 再生するアニメーションの列挙型
	void SetAnimation(const enAnimationClips& anim) { m_anim = anim; }

	/// @brief ガードフラグを取得。
	/// @return ガードフラグ。trueならガード中。
	bool GetGuardFlag() const{
		return m_guard;
	}
	/// @brief ガード状態ゲッター
	bool GetGuardBreak() const{
		return m_breakGuard;
	}
	/// @brief プレイヤーのリスポーン地点ゲッター
	/// @return リスポーン地点のconst参照。
	const Vector3& GetRespawnPoint()const { return m_startPos; }

	void KickPowerUp() { m_kickUp = true; m_guardUp = false; m_speedUp = false; m_itemPowerUp = true; m_itemPowerUpTime = 0.0f; }

	void GuardPowerUp() { m_kickUp = false; m_guardUp = true; m_speedUp = false; m_itemPowerUp = true; m_itemPowerUpTime = 0.0f; }

	void SpeedPowerUp() { m_kickUp = false; m_guardUp = false; m_speedUp = true; m_itemPowerUp = true; m_itemPowerUpTime = 0.0f; }

	/// @brief バフ状態の変化状況を記録,エフェクト用ファイルパスの変更
	void SetItemChangeState();
	
	/// @brief プレイヤーがダメージ中か？
	/// @return trueでダメージ中 falseでダメージ中ではない
	bool IsDamage() const { return m_damage; }

	/// @brief プレイヤーをダメージ状態に変更
	void SetDamage() { m_damage = true; }

	/// @brief プレイヤーからボールに伸びるベクトルを入手
	/// @return プレイヤーからボールに伸びるベクトルのconst参照
	const Vector3& GetToBallVector() const { return m_toBallVec; }

	/// @brief 現フレームのフラグ状態を記録
	void RecordFlags();

	/// @brief キャラクターコントローラーに移動速度を設定
	/// @param moveSpeed 設定する移動速度
	void SetCharaCon(Vector3& moveSpeed) { m_position = m_charaCon.Execute(moveSpeed,1.0f); }

	/// @brief プレイヤーが死亡して無敵時間中か？
	/// @return trueなら死亡 falseなら生存
	bool IsDie() const { return m_dieFlag; }

	/// @brief 最後に攻撃してきたプレイヤーの番号を入手
	/// @return 最後に攻撃してきたプレイヤーの番号
	int GetHaveAttackedPlayer() { return m_haveAttackedPlayer; }

	/// @brief 最後に攻撃してきたプレイヤーを設定
	/// @param num 最後に攻撃してきたプレイヤーの番号
	void SetHaveAttackedPlayer(const int num) { m_haveAttackedPlayer = num; }

	/// @brief プレイヤーに設定しているライトのカラーを入手
	/// @return プレイヤーに設定しているライトのカラーの参照
	const Vector3& GetPlayerColor() const { return m_playerColor; }

	/// @brief 準備完了しているか？
	/// @return trueで準備完了 falseで準備未完了
	const bool IsSetUp() const { return m_setUp; }
private:
	/// @brief 自分のアイテムによる強化状態
	ItemBuffChange m_itemBuffChageState = enItemBuff_Kick;
	/// @brief プレイヤーの番号
	int m_myNumber = 0;
	/// @brief 自分に攻撃してきたプレイヤーの番号
	int m_haveAttackedPlayer = 4;
	/// @brief プレイヤーの座標
	Vector3 m_position = Vector3::Zero;
	/// @brief プレイヤーの回転
	Quaternion m_qRot = Quaternion::Identity;
	/// @brief プレイヤーの拡大率
	Vector3 m_scale = Vector3::One;
	/// @brief プレイヤーの速度
	float m_moveVelocity = 0.0f;
	/// @brief プレイヤーの移動速度
	Vector3 m_moveSpeed = Vector3::Zero;
	/// @brief ダッシュフラグ
	bool m_dash = true;
	/// @brief ダッシュ中のカウンタ
	int m_dashCounter = 0;
	/// @brief プレイヤーのスタミナ
	float m_stamina = 0.0f;
	/// @brief スタミナ低下量
	float m_staminaDecreaseValue = 0.0f;
	/// @brief プレイヤーの向いている方向
	Vector3 m_direction = Vector3::Zero;
	/// @brief プレイヤーのスタート時の座標
	Vector3 m_startPos = Vector3::Zero;
	/// @brief プレイヤーのシンボルカラー
	Vector3 m_playerColor = Vector3::Zero;
	/// @brief プレイヤーにかかる摩擦力
	float m_friction = 0.0f;
	/// @brief プレイヤーからボールへのベクトル
	Vector3 m_toBallVec = Vector3::Zero;
	/// @brief プレイヤーが死んだかどうかのフラグ
	bool m_dieFlag = false;
	/// @brief バースト扱いのフラグ
	bool m_burstFlag = false;
	/// @brief 前フレームのバーストフラグ記録用
	bool m_burstFlagPrevFrame = false;
	/// @brief プレイヤーがリスポーンした時の無敵時間
	float m_mutekiTime = 0.0f;
	/// @brief ボールとの距離
	float m_ballDistance = 0.0f;
	/// @brief キック可能かどうかのフラグ
	bool m_kickFlag = false;
	/// @brief キック力
	float m_kickPower = 0.0f;
	/// @brief ガードフラグ
	bool m_guard = false;
	/// @brief 重力
	float m_gravity = 0.0f;
	/// @brief ダメージフラグ
	bool m_damage = false;
	/// @brief 前フレームのダメージフラグ
	bool m_damagePrevFrame = false;
	/// @brief ダメージを受けて動けるようになるまでのタイマー
	float m_damageTime = 0.0f;

	/// @brief Lスティックの横入力
	float m_Lstickx = 0.0f;
	/// @brief Lスティックの縦入力
	float m_Lsticky = 0.0f;

	/// @brief ガード耐久力
	float m_guardDurability = 100.0f;
	/// @brief ガード耐久値低下量
	float m_guradDecreaseValue = 0.0f;
	/// @brief ガードの状態
	bool m_breakGuard = false;
	/// @brief シールドにボールが触れたか？
	bool m_shieldHit = false;
	/// @brief 前フレームのガード状態フラグ記録用
	bool m_breakGuardPrevFrame = false;
	/// @brief ジャストガード判定になる時間
	float m_justGuardTime = 0.0f;
	/// @brief パワーアップフラグ
	bool m_powerUp = false;
	/// @brief パワーアップ中のカウンター
	int m_powerUpCounter = 0;
	/// @brief パワーアップの時間
	float m_powerUpTime = 0.0f;
	/// @brief ガード破壊によって起きるダウン状態
	//bool m_breakDown = false;
	
	/// @brief キック強化フラグ
	bool m_kickUp = false;
	bool m_kickUpPrevFrame = false;
	/// @brief ガード強化フラグ
	bool m_guardUp = false;
	bool m_guardUpPrevFrame = false;
	/// @brief スピード強化フラグ
	bool m_speedUp = false;
	bool m_speedUpPrevFrame = false;

	bool m_itemPowerUp = false;

	float m_itemPowerUpTime = 0.0f;
	/// @brief アイテムバフエフェクト再生用カウンター
	int m_itemPowerUpCounter = 0;
	/// @brief 準備完了フラグ
	bool m_setUp = false;
	/// @brief キャラクターコントローラー
	CharacterController m_charaCon;
	/// @brief ライティング
	Lighting* m_lig = nullptr;
	/// @brief スキンモデルレンダラー
	SkinModelRender* m_skinModelRender = nullptr;
	/// @brief ボール
	Ball* m_ball = nullptr;

	//エフェクト関連//
	/// @brief ボールをキックした時のエフェクト
	Effect m_kickEffect;
	/// @brief ガード時のエフェクト
	Effect m_guardEffect;
	//ガードエフェクトを一定間隔で発生させるためのカウンター
	int m_guardEffectCouter = 0;
	/// @brief ガード発生の予兆エフェクト
	Effect m_guardBeginEffect;
	/// @brief ガードブレイクエフェクト
	Effect m_guardBreakEffect;
	/// @brief シールド回復エフェクト
	Effect m_shieldRepairEffect;
	/// @brief シールド回復フラグ
	bool m_isRepair = true;
	/// @brief ガードヒットエフェクト
	Effect m_shieldHitEffect;
	/// @brief ガードヒットエフェクトを一定間隔で発生させるためのカウンター
	int m_shieldHitEffectCounter = 0;
	/// @brief キックのクールタイムカウンター
	int m_kickCooler = 0;
	/// @brief キックのクールタイム中かの正負
	bool m_kickCooling = false;
	/// @brief m_kickFlagとは別の可不可フラグ
	bool m_readyKick = true;
	//行動不能時エフェクト(ピヨり)
	Effect m_knockOutEffect;
	//ジャストガードエフェクト
	Effect m_justGuardEffect;

	float m_reSpawnTime = 0.0f;

	enAnimationClips m_anim = enAnimation_Idle;

	AnimationClip m_animationClips[enAnimation_Num];

	/// @brief タイマー
	Timer* m_timer = nullptr;

	/// @brief スコア
	Score* m_score = nullptr;
	/// @brief ゲームUI
	GameUI* m_ui = nullptr;
	//SE
	Se* m_se = nullptr;
	/// @brief プレイヤーのアクション
	PlayerAction* m_plAction = nullptr;
	/// @brief プレイヤーの接触
	PlayerCollide* m_plCollide = nullptr;
	/// @brief プレイヤーのエフェクト
	PlayerEffect* m_plEffect = nullptr;
	/// @brief プレイヤーの移動
	PlayerMove* m_plMove = nullptr;
	/// @brief プレイヤーの強化
	PlayerReinforcement* m_plReinforcement = nullptr;
};

