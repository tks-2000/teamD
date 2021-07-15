#pragma once

class GameDirector;
class Bgm;
class Se;
class SceneChange;

/// @brief �Q�[���̐�������
static const float NORMAL_TIME_LIMIT = 120.0f;
static const float SPECIAL_TIME_LIMIT = 180.0f;

class Timer : public IGameObject
{
private:

	/// @brief �Q�[���J�n�̃J�E���g
	float m_countDownNum = 0.0f;
	/// @brief �Q�[���̐�������
	float m_time = 0.0f;

	float m_timeLimit = 0.0f;
	/// @brief �Q�[���I�����Ƀ��U���g�ɑJ�ڂ���܂ł̎���
	float m_finishTimer = 0.0f;
	/// @brief �^�C�}�[�̏I�����
	bool m_timerEnd = false;

	bool m_countStart = false;
	
	/// @brief �^�C�}�[�̏�Ԃ̗񋓌^
	enum enTimerStatus {
		enCountDown,
		enTimerExecution,
		enFinish,
		enTimerEnd
	};

	/// @brief �^�C�}�[�̏��
	enTimerStatus m_timerStatus = enCountDown;

	GameDirector* m_gameDirector = nullptr;

	Bgm* m_bgm = nullptr;

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

	/// @brief �Q�[���J�n�̃J�E���g�_�E���̐��l�����
	/// @return �J�E���g�_�E�����l
	float GetCountDownNum() { return m_countDownNum; }
	/// @brief �Q�[���̎c�莞�Ԃ����
	/// @return �^�C�}�[�̐��l
	float GetTimer() { return m_time; }

	float GetTimeLimit() { return m_timeLimit; }

	float GetHalfLimit() { return m_timeLimit / 2; }
};

