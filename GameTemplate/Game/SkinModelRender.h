#pragma once
#include "Lighting.h"
class AnimationClip;
class Lighting;

class SkinModelRender : public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Model& GetModel() { return m_model; }


	

	/// @brief ���f���̍��W��ݒ�
	/// @param pos ���W
	void SetPosition(Vector3 pos) { m_position = pos; }

	/// @brief ���f���̑傫����ݒ�
	/// @param scale �g�嗦
	void SetScale(Vector3 scale) { m_scale = scale; }

	/// @brief ���f���̉�]��ݒ�
	/// @param rot �N�H�[�^�j�I��
	void SetRotation(Quaternion rot) { m_qRot = rot; }


	void SetNewModel() { m_model.Init(m_modelInitData); }

	/// @brief ���f���̍��W�����
	/// @return ���W
	Vector3 GetPosition() { return m_position; }


	/// @brief ���f���̏�����
	/// @param modelFilePath ���f���̃t�@�C���p�X
	/// @param lig ���C�e�B���O�\���̂̃A�h���X
	void Init(const char* modelFilePath, Light* lig);

	/// @brief ���f���̏�����
	/// @param modelFilePath ���f���̃t�@�C���p�X
	void Init(const char* modelFilePath);

	/// @brief �X�L�����f�������_���[�̃��[���h�s����擾
	/// @return ���f���̃��[���h�s��
	Matrix GetModelWorldMatrix() { return m_model.GetWorldMatrix(); }
	
private:
	Model m_model;								//���f��
	ModelInitData m_modelInitData;				//���f���̏��������
	Lighting* m_lig = nullptr;					//���C�e�B���O

	Vector3 m_position = Vector3::Zero;			//���W
	Vector3 m_scale = Vector3::One;				//�g�嗦
	Quaternion m_qRot = Quaternion::Identity;	//��]

};

