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

	bool IsResult();

	void SetGameStart() { m_gameState = enMainGame; }
	void SetGameResult() { m_gameState = enResult; }
	void SetGameEnd() { m_gameState = enTitle; }

};

