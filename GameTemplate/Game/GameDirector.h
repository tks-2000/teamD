#pragma once

class Title;
class Menu;
class Game;
class Result;
class Bgm;
class Se;
class Lighting;
class SceneChange;

class GameDirector : public IGameObject
{

private:
	enum enGameStatus {
		enTitle,
		enMenu,
		enMainGame,
		enResult,
		enEnd,
	};

	enGameStatus m_gameState = enTitle;

	bool m_delete = false;

	int m_playerNum = 0;

	Title* m_title = nullptr;

	Menu* m_menu = nullptr;

	Game* m_game = nullptr;

	Result* m_result = nullptr;

	Bgm* m_bgm = nullptr;

	Se* m_se = nullptr;

	Lighting* m_lighting = nullptr;

	SceneChange* m_sceneChange = nullptr;

public:
	GameDirector();
	~GameDirector();
	bool Start();
	void Update();

	
	

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

	/// @brief ���݂̏�Ԃ����j���[�ɕύX
	void SetMenu() { m_gameState = enMenu; }
	/// @brief ���݂̏�Ԃ����C���Q�[���ɕύX
	void SetGameStart() { m_gameState = enMainGame; }
	/// @brief ���݂̏�Ԃ����U���g�ɕύX
	void SetGameResult() { m_gameState = enResult; }
	/// @brief ���݂̏�Ԃ��^�C�g���ɕύX
	void SetTitle() { m_gameState = enTitle; }

	/// @brief ���݂̏�Ԃ��I���ɕύX
	void SetEnd() { m_gameState = enEnd; }

	/// @brief �^�C�g�����I��������
	void TitleEnd() { DeleteGO(m_title); m_title = nullptr; }

	/// @brief ���j���[���I��������
	void MenuEnd() { DeleteGO(m_menu); m_menu = nullptr; }
};

