#include "stdafx.h"
#include "Timer.h"

namespace {
	/// @brief �^�C�}�[�̐i�ޗ�
	const float TIMER_AMOUNT_GO = 1.0f;
	/// @brief �^�C�}�[�̏I���n�_
	const float TIMER_ZERO = 0.0f;
	/// @brief �J�E���g�_�E������
	const float TIMER_COUNT_DOUN = 4.0f;
	/// @brief �Q�[���̐�������
	const float TIME_LIMIT = 120.0f;
	/// @brief �Q�[�����I�����Ă��烊�U���g�Ɉڂ�܂ł̎���
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
		m_gameDirector->SetGameResult();
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