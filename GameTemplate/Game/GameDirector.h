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

	/// @brief ���݃��C���Q�[�������H
	/// @return ���C���Q�[�����Ȃ�true �����łȂ��Ȃ�false
	bool IsMainGame();

	/// @brief ���݃��U���g�����H
	/// @return ���U���g���Ȃ�true �����łȂ��Ȃ�false
	bool IsResult();

	/// @brief ���݂̏�Ԃ����C���Q�[���ɕύX
	void SetGameStart() { m_gameState = enMainGame; }
	/// @brief ���݂̏�Ԃ����U���g�ɕύX
	void SetGameResult() { m_gameState = enResult; }
	/// @brief ���݂̏�Ԃ��^�C�g���ɕύX
	void SetTitle() { m_gameState = enTitle; }

};

