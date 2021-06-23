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

	int GetPlayerNum() { return m_playerNum; }

	void GameStart() { m_gameState = enMainGame; }
	void GameEnd() { m_gameState = enTitle; }

};

