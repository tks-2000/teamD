#pragma once

class GameDirector;
class Se;
class SceneChange;

/// @brief ゲームの制限時間
static const float TIME_LIMIT = 120.0f;

class Timer : public IGameObject
{
private:

	/// @brief ゲーム開始のカウント
	float m_countDownNum = 0.0f;
	/// @brief ゲームの制限時間
	float m_time = 0.0f;
	/// @brief ゲーム終了時にリザルトに遷移するまでの時間
	float m_finishTimer = 0.0f;
	/// @brief タイマーの終了状態
	bool m_timerEnd = false;

	bool m_countStart = false;
	
	/// @brief タイマーの状態の列挙型
	enum enTimerStatus {
		enCountDown,
		enTimerExecution,
		enFinish,
		enTimerEnd
	};

	/// @brief タイマーの状態
	enTimerStatus m_timerStatus = enCountDown;

	GameDirector* m_gameDirector = nullptr;

	Se* m_se = nullptr;

	SceneChange* m_sceneChange = nullptr;
	
	void CountDown();
	void TimerExecution();
	void Finish();
	
public:
	Timer();
	~Timer();
	bool Start();
	void Update();

	bool IsCountDown();
	bool IsTimerExecution();
	bool IsFinish();
	bool IsTimerEnd();

	/// @brief ゲーム開始のカウントダウンの数値を入手
	/// @return カウントダウン数値
	float GetCountDownNum() { return m_countDownNum; }
	/// @brief ゲームの残り時間を入手
	/// @return タイマーの数値
	float GetTimer() { return m_time; }
};

