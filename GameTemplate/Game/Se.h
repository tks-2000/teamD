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
	//キック時
	void PlayKickSe();
	//強化時キック
	void PlayPoweredKickSe();
	//ジャストガード
	void PlayJustGuardSe();
	//シールド回復
	void PlayShieldRepairSe();
	//シールド時ヒット
	void PlayShieldHitSe();
	//シールドブレイク
	void PlayBreakSe();
	//壁反射
	void PlayReflectSe();
	


};

