#pragma once
class GameDirector : public IGameObject
{

private:
	enum enGameStatus {
		enTitle,
		enMenu,
		enMainGame,
		enResult
	};

	enGameStatus m_gameState = enTitle;

	int m_playerNum = 0;

public:
	GameDirector();
	~GameDirector();
	bool Start();
	void Update();

	void Title();
	void MainGame();
	void Result();

	/// @brief プレイヤー人数を取得
	/// @return プレイヤーの人数
	int GetPlayerNum() { return m_playerNum; }

	/// @brief プレイヤーの人数を設定
	/// @param plNum 設定する人数
	void SetPlayerNum(int plNum) { m_playerNum = plNum; }

	/// @brief 現在メインゲーム中か？
	/// @return メインゲーム中ならtrue そうでないならfalse
	bool IsMainGame();

	/// @brief 現在リザルト中か？
	/// @return リザルト中ならtrue そうでないならfalse
	bool IsResult();

	void SetMenu() { m_gameState = enMenu; }
	/// @brief 現在の状態をメインゲームに変更
	void SetGameStart() { m_gameState = enMainGame; }
	/// @brief 現在の状態をリザルトに変更
	void SetGameResult() { m_gameState = enResult; }
	/// @brief 現在の状態をタイトルに変更
	void SetTitle() { m_gameState = enTitle; }

};

