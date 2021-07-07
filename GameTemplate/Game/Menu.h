#pragma once

class Lighting;
class FontRender;
class SkinModelRender;
class GameDirector;

const int PLAYER_NUM = 4;

class Menu : public IGameObject
{
private:
	int m_playerNum = 0;

	SkinModelRender* m_plModel[PLAYER_NUM] = { nullptr };

	Vector3 m_pos[PLAYER_NUM] = { Vector3::Zero,Vector3::Zero ,Vector3::Zero ,Vector3::Zero };

	Vector3 m_spLigPos[PLAYER_NUM] = { Vector3::Zero,Vector3::Zero ,Vector3::Zero ,Vector3::Zero };

	Quaternion m_qRot[PLAYER_NUM] = { Quaternion::Identity,Quaternion::Identity,Quaternion::Identity,Quaternion::Identity };

	float m_angle[PLAYER_NUM] = { 0.0f };

	float m_riseSpeed[PLAYER_NUM] = { 0.0f };

	enum enAnimationClips
	{
		enAnimation_Idle,
		enAnimation_clear,
		enAnimation_jump,
		enAnimation_Num
	};

	enAnimationClips m_anim = enAnimation_Idle;

	AnimationClip m_animationClips[enAnimation_Num];

	/// @brief �v���C���[�̃t�H���g
	FontRender* m_plFont = nullptr;
	/// @brief �v���C���[�̐l���̃t�H���g
	FontRender* m_plNumFont = nullptr;

	GameDirector* m_gameDirector = nullptr;

	Lighting* m_lig = nullptr;

	bool m_endFlag = false;

public:
	Menu();
	~Menu();
	bool Start();
	void Update();
	void End() { m_endFlag = true; }
};

