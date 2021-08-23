#include "stdafx.h"
#include "Timer.h"



namespace {
	/// @brief 開始時のタイマーの進む量
	const float START_TIMER_AMOUNT_GO = 1.1f;
	/// @brief タイマーの進む量
	const float TIMER_AMOUNT_GO = 1.0f;
	/// @brief タイマーの終了地点
	const float TIMER_ZERO = 0.0f;
	/// @brief カウントダウン時間
	const float TIMER_COUNT_DOUN = 2.99999f;
	
	/// @brief ゲームが終了してからリザルトに移るまでの時間
	const float FINISH_DISPLAY_TIME = 3.0f;
}

Timer::Timer()
{
	m_countDownNum = TIMER_COUNT_DOUN;
	
	m_finishTimer = FINISH_DISPLAY_TIME;
	m_timerEnd = false;
	m_timerStatus = enCountDown;
	m_bgm = FindGO<Bgm>(BGM_NAME);
	m_se = FindGO<Se>(SE_NAME);
	m_sceneChange = FindGO<SceneChange>(SCENE_CHANGE_NAME);
	m_countStart = false;
}

Timer::~Timer()
{

}

bool Timer::Start()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	switch (m_gameDirector->GetGameMode())
	{
	case GameDirector::enNormal: {
		m_timeLimit = NORMAL_TIME_LIMIT;
	}break;
	case GameDirector::enSpecial: {
		m_timeLimit = SPECIAL_TIME_LIMIT;
	}break;
	default:
		break;
	}
	m_time = m_timeLimit;
	return true;
}

void Timer::CountDown()
{
	if (m_countStart == false) {
		m_se->PlayCountDownSe();
		m_countStart = true;
	}
	m_countDownNum -= START_TIMER_AMOUNT_GO * g_gameTime->GetFrameDeltaTime();
	m_bgm->BgmStop();
	if (m_countDownNum < TIMER_ZERO) {
		m_countDownNum = TIMER_ZERO;
		m_timerStatus = enTimerExecution;
		m_bgm->ChangeGameBgm();
	}
}

void Timer::TimerExecution()
{
	m_time -= TIMER_AMOUNT_GO * g_gameTime->GetFrameDeltaTime();
	if (m_time < TIMER_ZERO) {
		m_time = TIMER_ZERO;
		m_timerStatus = enFinish;
		m_se->PlayEndSe();
	}
}

void Timer::Finish()
{
	m_finishTimer -= TIMER_AMOUNT_GO * g_gameTime->GetFrameDeltaTime();
	if (m_finishTimer < TIMER_ZERO) {
		m_finishTimer = TIMER_ZERO;
		m_timerStatus = enTimerEnd;
	}
}

void Timer::Update()
{
	if (m_timerEnd == true || m_sceneChange->TransparencyChangeStart() == false) {
		return;
	}

	switch (m_timerStatus) {
	case enCountDown: {
		CountDown();
	}break;
	case enTimerExecution: {
		TimerExecution();
	}break;
	case enFinish: {
		Finish();
	}break;
	case enTimerEnd: {
		m_timerEnd = true;
	}break;
	}
}

bool Timer::IsCountDown()
{
	if (m_timerStatus == enCountDown) {
		return true;
	}
	else {
		return false;
	}
}

bool Timer::IsTimerExecution()
{
	if (m_timerStatus == enTimerExecution) {
		return true;
	}
	else {
		return false;
	}
}

bool Timer::IsFinish()
{
	if (m_timerStatus == enFinish) {
		return true;
	}
	else {
		return false;
	}
}

bool Timer::IsTimerEnd()
{
	if (m_timerStatus == enTimerEnd) {
		return true;
	}
	else {
		return false;
	}
}