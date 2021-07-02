#include "stdafx.h"
#include "Timer.h"

namespace {
	/// @brief タイマーの進む量
	const float TIMER_AMOUNT_GO = 1.0f;
	/// @brief タイマーの終了地点
	const float TIMER_ZERO = 0.0f;
	/// @brief カウントダウン時間
	const float TIMER_COUNT_DOUN = 4.0f;
	/// @brief ゲームの制限時間
	const float TIME_LIMIT = 1.0f;
	/// @brief ゲームが終了してからリザルトに移るまでの時間
	const float FINISH_DISPLAY_TIME = 5.0f;
}

Timer::Timer()
{
	m_countDownNum = TIMER_COUNT_DOUN;
	m_time = TIME_LIMIT;
	m_finishTimer = FINISH_DISPLAY_TIME;
	m_timerEnd = false;
	m_timerStatus = enCountDown;
}

Timer::~Timer()
{

}

bool Timer::Start()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	return true;
}

void Timer::CountDown()
{
	m_countDownNum -= TIMER_AMOUNT_GO * g_gameTime->GetFrameDeltaTime();
	if (m_countDownNum < TIMER_ZERO) {
		m_countDownNum = TIMER_ZERO;
		m_timerStatus = enTimerExecution;
	}
}

void Timer::TimerExecution()
{
	m_time -= TIMER_AMOUNT_GO * g_gameTime->GetFrameDeltaTime();
	if (m_time < TIMER_ZERO) {
		m_time = TIMER_ZERO;
		m_timerStatus = enFinish;
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
	if (m_timerEnd == true) {
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