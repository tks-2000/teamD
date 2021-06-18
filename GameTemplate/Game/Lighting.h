#pragma once
#include "math.h"
#include "stdafx.h"

const int SPOT_LIGHT_SUM = 4;

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
	SpotLight spotLight[SPOT_LIGHT_SUM];					//�X�|�b�g���C�g
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


	Light GetLight() { return m_light; }
	
	/// @brief ���C�g�̍\���̂����
	/// @return ���C�g�\���̂̃A�h���X
	Light* GetLightAddress() { return &m_light; }


	/// @brief �f�B���N�V�������C�g�̏�����
	void InitDirectionLight();

	/// @brief �f�B���N�V�������C�g�̕��������
	/// @return �f�B���N�V�������C�g�̕���
	Vector3 GetDirectionLightDirection() { return m_light.directionLight.direction; }

	/// @brief �f�B���N�V�������C�g�̕�����ݒ�
	/// @param dirLigVec �f�B���N�V�������C�g�ɐݒ肷�����
	void SetDirectionLightDirection(Vector3 dirLigVec) { m_light.directionLight.direction = dirLigVec; m_light.directionLight.direction.Normalize(); }

	void RotationDirectionLight();

	/// @brief �|�C���g���C�g�̏�����
	void InitPointLight();

	void MovePointLight();

	/// @brief �|�C���g���C�g�̍��W�����
	/// @return �|�C���g���C�g�̍��W
	Vector3 GetPointLightPos() { return m_light.pointLight.position; }

	/// @brief �|�C���g���C�g�̍��W��ݒ�
	/// @param pos �|�C���g���C�g�ɐݒ肷����W
	void SetPointLighitPos(Vector3 pos) { m_light.pointLight.position = pos; }

	/// @brief �|�C���g���C�g�̃J���[��ݒ�
	/// @param color �|�C���g���C�g�ɐݒ肷����W
	void SetPointLightColor(Vector3 color) { m_light.pointLight.color = color; }
	
	/// @brief �X�|�b�g���C�g�̏�����
	void InitSpotLight(int num);

	void MoveSpotLight(int num);

	void RotationSpotLight(int num);

	/// @brief �X�|�b�g���C�g�̍��W�����
	/// @param num ���肷��X�|�b�g���C�g�̔ԍ�
	/// @return �X�|�b�g���C�g�̍��W
	Vector3 GetSpotLightPos(int num) { return m_light.spotLight[num].position; }

	/// @brief �X�|�b�g���C�g�̍��W��ݒ�
	/// @param num �ݒ肵�����X�|�b�g���C�g�̔ԍ�
	/// @param pos �X�|�b�g���C�g�ɐݒ肷����W
	void SetSpotLightPos(int num,Vector3 pos) { m_light.spotLight[num].position = pos; }

	/// @brief �X�|�b�g���C�g�̃J���[��ݒ�
	/// @param num �ݒ肵�����X�|�b�g���C�g�̔ԍ�
	/// @param color �X�|�b�g���C�g�ɐݒ肷��J���[
	void SetSpotLightColor(int num, Vector3 color) { m_light.spotLight[num].color = color; }

	/// @brief �X�|�b�g���C�g�̕�����ݒ�
	/// @param num �ݒ肵�����X�|�b�g���C�g�̔ԍ�
	/// @param dir �X�|�b�g���C�g�ɐݒ肷�����
	void SetSpotLightDirection(int num,Vector3 dir) { m_light.spotLight[num].direction = dir; m_light.spotLight[num].direction.Normalize(); }

	/// @brief �������C�g�̏�����
	void InitHemiSphereLight();

private:
	/// @brief ���C�e�B���O�S�Ẵf�[�^
	Light m_light;

};


