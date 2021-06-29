#pragma once
class GameDirector : public IGameObject
{

private:
	enum enGameStatus {
		enTitle,
		enPlayerSelect,
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

	int GetPlayerNum() { return m_playerNum; }

	/// @brief 現在メインゲーム中か？
	/// @return メインゲーム中ならtrue そうでないならfalse
	bool IsMainGame();

	/// @brief 現在リザルト中か？
	/// @return リザルト中ならtrue そうでないならfalse
	bool IsResult();

	/// @brief 現在の状態をメインゲームに変更
	void SetGameStart() { m_gameState = enMainGame; }
	/// @brief 現在の状態をリザルトに変更
	void SetGameResult() { m_gameState = enResult; }
	/// @brief 現在の状態をタイトルに変更
	void SetTitle() { m_gameState = enTitle; }

};

