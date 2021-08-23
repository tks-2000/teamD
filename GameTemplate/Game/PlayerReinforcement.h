#pragma once

class Player;
class PlayerAction;
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

	/// @brief プレイヤーが強化状態か？
	/// @return trueで強化状態 falseで強化されていない状態
	bool IsPowerUp() const { return m_powerUp; }

	/// @brief プレイヤーを強化状態に変更
	void ChangePowerUp() { m_powerUp = true; m_powerUpTime = 0.0f; }

	/// @brief プレイヤーがキック強化状態か？
	/// @return trueでキック強化状態 falseでキック強化状態ではない
	bool IsKickUp() const;

	/// @brief プレイヤーが防御強化状態か？
	/// @return trueで防御強化状態 falseで防御強化状態ではない
	bool IsDefenseUp() const;

	/// @brief プレイヤーが速度強化状態か？
	/// @return trueで速度強化状態　falseで速度強化状態ではない
	bool IsSpeedUp() const;

private:
	/// @brief プレイヤーの番号
	int m_playerNumber = 0;
	/// @brief パワーアップフラグ
	bool m_powerUp = false;
	/// @brief パワーアップ中のカウンター
	int m_powerUpCounter = 0;
	/// @brief パワーアップの時間
	float m_powerUpTime = 0.0f;
	/// @brief アイテムによるパワーアップフラグ
	bool m_itemPowerUp = false;
	/// @brief アイテムによるパワーアップ時間
	float m_itemPowerUpTime = 0.0f;
	/// @brief どのアイテム強化状態かを表すステータス
	enItemPowerUp m_itemPowerUpState = enItemPowerUpNum;
	/// @brief プレイヤー
	Player* m_player = nullptr;
	/// @brief プレイヤーのアクション
	PlayerAction* m_playerAction = nullptr;
	/// @brief プレイヤーの動き
	PlayerMove* m_playerMove = nullptr;
};

