#pragma once

class Player;
class PlayerAction;
class PlayerEffect;
class PlayerMove;

/// @brief アイテムで強化されている状態を表す列挙型
enum enItemPowerUp {
	enKickUp,			//キック力アップ
	enDefenseUp,		//防御力アップ
	enSpeedUp,			//速度アップ
	enItemPowerUpNum	//強化無し・強化の要素数
};

/// @brief プレイヤーの強化状態を制御するクラス
class PlayerReinforcement : public IGameObject
{
public:
	PlayerReinforcement();
	~PlayerReinforcement();
	bool Start();
	void Update();

	/// @brief 自分が何Pかを設定
	/// @param num 設定するプレイヤー番号
	void SetPlayerNumber(const int num);

	/// @brief プレイヤーが自己強化状態か？
	/// @return trueで強化状態 falseで強化されていない状態
	bool IsSelfPowerUp() const { return m_selfPowerUp; }

	/// @brief プレイヤーがキック強化状態か？
	/// @return trueでキック強化状態 falseでキック強化状態ではない
	bool IsKickUp() const;

	/// @brief プレイヤーが防御強化状態か？
	/// @return trueで防御強化状態 falseで防御強化状態ではない
	bool IsDefenseUp() const;

	/// @brief プレイヤーが速度強化状態か？
	/// @return trueで速度強化状態　falseで速度強化状態ではない
	bool IsSpeedUp() const;

	/// @brief プレイヤーを自己強化状態に変更
	void ChangeSelfPowerUp() { m_selfPowerUp = true; m_selfPowerUpCount = 0.0f; }

	/// @brief プレイヤーをキック力強化状態に変更
	void ChangeKickPowerUp();

	/// @brief プレイヤーを防御強化状態に変更
	void ChangeDefenseUp();

	/// @brief プレイヤーを速度強化状態に変更
	void ChangeSpeedUp();

	/// @brief 強化状態を解除
	void ReinforcementRelease();

private:
	/// @brief 準備完了フラグ
	bool m_setUp = false;
	/// @brief プレイヤーの番号
	int m_playerNumber = 0;
	/// @brief 自己強化フラグ
	bool m_selfPowerUp = false;
	/// @brief 自己強化中のカウント
	float m_selfPowerUpCount = 0.0f;
	/// @brief どのアイテム強化状態かを表すステータス
	enItemPowerUp m_itemPowerUpState = enItemPowerUpNum;
	/// @brief アイテムによる強化中のカウント
	float m_itemPowerUpCount = 0.0f;

	/// @brief プレイヤー
	Player* m_player = nullptr;
	/// @brief プレイヤーのアクション
	PlayerAction* m_playerAction = nullptr;
	/// @brief プレイヤーの動き
	PlayerMove* m_playerMove = nullptr;
	/// @brief プレイヤーのエフェクト
	PlayerEffect* m_plEffect = nullptr;

	/// @brief 自己強化中の処理
	void SelfPowerUp();

	/// @brief アイテムによる強化中の処理
	void ItemPowerUp();
};

