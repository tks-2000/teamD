#pragma once
#include "math.h"
#include "stdafx.h"

//�f�B���N�V�������C�g�̍\����
struct DirectionLight
{
	Vector3 direction = Vector3::Zero;	//���C�g�̕���
	float pad0 = 0.0f;					//�p�f�B���O
	Vector3 color = Vector3::Zero;		//���C�g�̃J���[
	float pad1 = 0.0f;					//�p�f�B���O
	
};

//�|�C���g���C�g�̍\����
struct PointLight
{
	Vector3 position = Vector3::Zero;	//�ʒu
	float pad0 = 0.0f;					//�p�f�B���O
	Vector3 color = Vector3::Zero;		//�J���[
	float Range = 0.0f;					//�e���͈�

};

//�X�|�b�g���C�g�̍\����
struct SpotLight
{
	Vector3 position = Vector3::Zero;	//�ʒu
	float pad0 = 0.0f;					//�p�f�B���O
	Vector3 color = Vector3::Zero;		//�J���[
	float Range = 0.0f;					//�e���͈�
	Vector3 direction = Vector3::Zero;	//�ˏo����
	float angle = 0.0f;					//�ˏo�p�x

};

//���C�g���܂Ƃ߂��\����
struct Light
{
	DirectionLight directionLight;			//�f�B���N�V�������C�g
	PointLight pointLight;					//�|�C���g���C�g
	SpotLight spotLight;					//�X�|�b�g���C�g
	Vector3 eyePos = Vector3::Zero;			//���_�̈ʒu
	float pad0 = 0.0f;
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

	Light* GetLightAddress() { return &m_light; }

	Vector3 GetDirectionLightDirection() { return m_light.directionLight.direction; }

	void SetDirectionLightDirection(Vector3 dirLigVec) { m_light.directionLight.direction = dirLigVec; }

	void RotationDirectionLight();

	void InitPointLight();

	void MovePointLight();

	Vector3 GetPointLightPos() { return m_light.pointLight.position; }
	
	void InitSpotLight();

	void MoveSpotLight();

	void RotationSpotLight();

	Vector3 GetSpotLightPos() { return m_light.spotLight.position; }

	

private:
	Light m_light;		//���C�g

};


