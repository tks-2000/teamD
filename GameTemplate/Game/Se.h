#pragma once

class CSoundSource;

class Se : public IGameObject
{
private:
	float m_seVolume = 1.0f;

public:
	Se();
	~Se();
	bool Start();
	void Update();

	void PlayPressKeySe();
};

