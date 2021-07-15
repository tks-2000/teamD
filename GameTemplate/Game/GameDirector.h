#pragma once

class Title;
class Menu;
class Game;
class Result;
class Bgm;
class Se;
class Lighting;
class SceneChange;
class Timer;

class GameDirector : public IGameObject
{
public:
	GameDirector();
	~GameDirector();
	bool Start();
	void Update();

	enum enGameStatus {
		enTitle,
		enMenu,
		enMainGame,
		enResult,
		enEnd,
	};

	enum enGameMode {
		enNormal,
		enSpecial
	};

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

	/// @brief 現在の状態をメニューに変更
	void SetMenu() { m_gameState = enMenu; }
	/// @brief 現在の状態をメインゲームに変更
	void SetGameStart() { m_gameState = enMainGame; }
	/// @brief 現在の状態をリザルトに変更
	void SetGameResult() { m_gameState = enResult; }
	/// @brief 現在の状態をタイトルに変更
	void SetTitle() { m_gameState = enTitle; }

	/// @brief 現在の状態を終了に変更
	void SetEnd() { m_gameState = enEnd; }

	/// @brief タイトルを終了させる
	void TitleEnd() { DeleteGO(m_title); m_title = nullptr; }

	/// @brief メニューを終了させる
	void MenuEnd() { DeleteGO(m_menu); m_menu = nullptr; }

	void SetGameMode(enGameMode gameMode) { m_gameMode = gameMode; }

	enGameMode GetGameMode() { return m_gameMode; }

	void CangeHemLigt();

private:
	

	enGameStatus m_gameState = enTitle;

	enGameMode m_gameMode = enNormal;

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

	Timer* m_timer = nullptr;

	Vector3 m_hemLigColorStart = Vector3::Zero;

	Vector3 m_hemLigCplorHalf = Vector3::Zero;

	Vector3 m_hemLigColorEnd = Vector3::Zero;
};

