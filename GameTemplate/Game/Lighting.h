#pragma once
#include "math.h"
#include "stdafx.h"

/// @brief �f�B���N�V�������C�g�\����
struct DirectionLight
{
	Vector3 direction = Vector3::Zero;	//���C�g�̕���
	float pad0 = 0.0f;					//�p�f�B���O
	Vector3 color = Vector3::Zero;		//���C�g�̃J���[
	float pad1 = 0.0f;					//�p�f�B���O
	
};

/// @brief �|�C���g���C�g�\����
struct PointLight
{
	Vector3 position = Vector3::Zero;	//�ʒu
	float pad0 = 0.0f;					//�p�f�B���O
	Vector3 color = Vector3::Zero;		//�J���[
	float Range = 0.0f;					//�e���͈�

};

/// @brief �X�|�b�g���C�g�\����
struct SpotLight
{
	Vector3 position = Vector3::Zero;	//�ʒu
	float pad0 = 0.0f;					//�p�f�B���O
	Vector3 color = Vector3::Zero;		//�J���[
	float Range = 0.0f;					//�e���͈�
	Vector3 direction = Vector3::Zero;	//�ˏo����
	float angle = 0.0f;					//�ˏo�p�x

};

/// @brief �������C�g�\����
struct HemiSphereLight
{
	Vector3 groundColor = Vector3::Zero;	//�n�ʐF
	float pad0 = 0.0f;						//�p�f�B���O
	Vector3 skyColor = Vector3::Zero;		//�V���F
	float pad1 = 0.0f;						//�p�f�B���O
	Vector3 groundNormal = Vector3::Zero;	//�n�ʂ̖@��
	float pad2 = 0.0f;						//�p�f�B���O
};

/// @brief ���C�g�S�Ă̍\����
struct Light
{
	DirectionLight directionLight;			//�f�B���N�V�������C�g
	PointLight pointLight;					//�|�C���g���C�g
	SpotLight spotLight;					//�X�|�b�g���C�g
	HemiSphereLight hemiSphereLight;		//�������C�g
	Vector3 eyePos = Vector3::Zero;			//���_�̈ʒu
	float pad0 = 0.0f;						//�p�f�B���O
	Vector3 ambientlight = Vector3::Zero;	//����
};

class Lighting : public IGameObject
{
public:
	Lighting();
	~Lighting();
	bool Start();
	void Update();

	void InitDirectionLight();

	Light& GetLight() { return m_light; }

	/// @brief ���C�g�̍\���̂����
	/// @return ���C�g�\���̂̃A�h���X
	Light* GetLightAddress() { return &m_light; }

	/// @brief �f�B���N�V�������C�g�̕��������
	/// @return ����
	Vector3 GetDirectionLightDirection() { return m_light.directionLight.direction; }

	/// @brief �f�B���N�V�������C�g�̕�����ݒ�
	/// @param dirLigVec ���K�����ꂽ����
	void SetDirectionLightDirection(Vector3 dirLigVec) { m_light.directionLight.direction = dirLigVec; }

	void RotationDirectionLight();

	void InitPointLight();

	void MovePointLight();

	/// @brief �|�C���g���C�g�̍��W�����
	/// @return �|�C���g���C�g�̍��W
	Vector3 GetPointLightPos() { return m_light.pointLight.position; }
	
	void InitSpotLight();

	void MoveSpotLight();

	void RotationSpotLight();

	/// @brief �X�|�b�g���C�g�̍��W�����
	/// @return �X�|�b�g���C�g�̍��W
	Vector3 GetSpotLightPos() { return m_light.spotLight.position; }

	void InitHemiSphereLight();

private:
	Light m_light;		//���C�g

};


