#pragma once
#include "Lighting.h"
class AnimationClip;
class Lighting;

class SkinModelRender : public IGameObject
{
private:
	Model m_model;								//���f��
	ModelInitData m_modelInitData;				//���f���̏��������
	Skeleton m_skeleton;						//�X�P���g��
	CharacterController m_charaCon;				//�L�����N�^�[�R���g���[���[

	Vector3 m_position = Vector3::Zero;			//���W
	Vector3 m_scale = Vector3::One;				//�g�嗦
	Quaternion m_rot = Quaternion::Identity;	//��]

	Lighting m_lighting;						//���C�e�B���O

public:
	SkinModelRender();
	~SkinModelRender();

	bool Start();
	void Update();

	void SetPosition(Vector3 pos) { m_position = pos; }
	void SetScale(Vector3 scale) { m_scale = scale; }
	void SetRotation(Quaternion rot) { m_rot = rot; }
	void SetNewModel() { m_model.Init(m_modelInitData); }

	Vector3 GetPosition() { return m_position; }
	Vector3 GetScale() { return m_scale; }
	

	void Init(const char* modelFilePath);
	
};

