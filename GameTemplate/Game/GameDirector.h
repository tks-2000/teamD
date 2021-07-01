#pragma once
class GameDirector : public IGameObject
{

private:
	enum enGameStatus {
		enTitle,
		enMenu,
		enMainGame,
		enResult,
		enRePlay
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

	/// @brief �v���C���[�l�����擾
	/// @return �v���C���[�̐l��
	int GetPlayerNum() { return m_playerNum; }

	/// @brief �v���C���[�̐l����ݒ�
	/// @param plNum �ݒ肷��l��
	void SetPlayerNum(int plNum) { m_playerNum = plNum; }

	/// @brief ���݃��C���Q�[�������H
	/// @return ���C���Q�[�����Ȃ�true �����łȂ��Ȃ�false
	bool IsMainGame();

	/// @brief ���݃��U���g�����H
	/// @return ���U���g���Ȃ�true �����łȂ��Ȃ�false
	bool IsResult();

	void SetMenu() { m_gameState = enMenu; }
	/// @brief ���݂̏�Ԃ����C���Q�[���ɕύX
	void SetGameStart() { m_gameState = enMainGame; }
	/// @brief ���݂̏�Ԃ����U���g�ɕύX
	void SetGameResult() { m_gameState = enResult; }
	/// @brief ���݂̏�Ԃ��^�C�g���ɕύX
	void SetTitle() { m_gameState = enTitle; }

	void SetRePlay() { m_gameState = enRePlay; }

};

