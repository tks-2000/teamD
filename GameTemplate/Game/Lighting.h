#pragma once
#include "math.h"
#include "stdafx.h"

const int POINT_LIGHT_SUM = 5;
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
	PointLight pointLight[POINT_LIGHT_SUM];					//�|�C���g���C�g
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


	Light& GetLight() { return m_light; }
	
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

	/// @brief �f�B���N�V�������C�g�̃J���[��ݒ�
	/// @param color �f�B���N�V�������C�g�ɐݒ肷��J���[
	void SetDirectionLightColor(const Vector3& color) { m_light.directionLight.color = color; }

	void RotationDirectionLight();

	/// @brief �|�C���g���C�g�̏�����
	void InitPointLight(int num);

	void MovePointLight();

	/// @brief �|�C���g���C�g�̍��W�����
	/// @return �|�C���g���C�g�̍��W
	Vector3 GetPointLightPos(int num) { return m_light.pointLight[num].position; }

	/// @brief �|�C���g���C�g�̍��W��ݒ�
	/// @param pos �|�C���g���C�g�ɐݒ肷����W
	void SetPointLighitPos(int num,Vector3 pos) { m_light.pointLight[num].position = pos; }

	/// @brief �|�C���g���C�g�̃J���[��ݒ�
	/// @param color �|�C���g���C�g�ɐݒ肷����W
	void SetPointLightColor(int num,Vector3 color) { m_light.pointLight[num].color = color; }

	/// @brief �|�C���g���C�g�̉e���͈͂�ݒ�
	/// @param num �ݒ肵�����|�C���g���C�g�̔ԍ�
	/// @param range �|�C���g���C�g�ɐݒ肷��e���͈�
	void SetPointLightRange(int num, float range) { m_light.pointLight[num].Range = range; }

	void ResetPointLight();
	
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

	/// @brief �X�|�b�g���C�g�̓_�ł�ݒ�
	/// @param num �_�ł��������X�|�b�g���C�g�̔ԍ�
	/// @param Time �_�ł����鎞��
	/// @param interval �_�ł̊Ԋu
	void SetSpotLightBlinking(int num, float time,float interval);

	void ResetSpotLight();

	/// @brief �|�C���g���C�g�̓_�ł�ݒ�
	/// @param num �_�ł��������|�C���g���C�g�̔ԍ�
	/// @param Time �_�ł����鎞��
	/// @param interval �_�ł̊Ԋu
	void SetPointLightBlinking(int num, float time, float interval);

	/// @brief �������C�g�̏�����
	void InitHemiSphereLight();

private:
	/// @brief ���C�e�B���O�S�Ẵf�[�^
	Light m_light;

	/// @brief �X�|�b�g���C�g�̓_�Ńt���O
	bool m_spLigBlink[SPOT_LIGHT_SUM] = { false };

	/// @brief �X�|�b�g���C�g�̓_�Ŏ���
	float m_spLigBlinkTime[SPOT_LIGHT_SUM] = { 0.0f };

	/// @brief �X�|�b�g���C�g�̐؂�ւ�����
	float m_spLigBlinkSwitchingTime[SPOT_LIGHT_SUM] = { 0.0f };

	/// @brief �X�|�b�g���C�g�̓_�ŊԊu
	float m_spLigBlinkInterval[SPOT_LIGHT_SUM] = { 0.0f };

	/// @brief �X�|�b�g���C�g��_�ł�����J���[
	Vector3 m_spLigColor[SPOT_LIGHT_SUM] = { {Vector3::Zero},{Vector3::Zero},{Vector3::Zero},{Vector3::Zero} };

	/// @brief �X�|�b�g���C�g���_���Ă���t���O
	bool m_spLigLit[SPOT_LIGHT_SUM] = { true };

	/// @brief �|�C���g���C�g�̓_�Ńt���O
	bool m_ptLigBlink[POINT_LIGHT_SUM] = { false };

	/// @brief �|�C���g���C�g�̓_�Ŏ���
	float m_ptLigBlinkTime[POINT_LIGHT_SUM] = { 0.0f };

	/// @brief �|�C���g���C�g�̐؂�ւ�����
	float m_ptLigBlinkSwitchingTime[POINT_LIGHT_SUM] = { 0.0f };

	/// @brief �|�C���g���C�g�̓_�ŊԊu
	float m_ptLigBlinkInterval[POINT_LIGHT_SUM] = { 0.0f };

	/// @brief �|�C���g���C�g��_�ł�����J���[
	Vector3 m_ptLigColor[POINT_LIGHT_SUM] = { {Vector3::Zero},{Vector3::Zero},{Vector3::Zero},{Vector3::Zero},{Vector3::Zero} };

	/// @brief �|�C���g���C�g���_���Ă���t���O
	bool m_ptLigLit[POINT_LIGHT_SUM] = { true };

	void SpotLightBlinking(int num);

	void PointLightBlinking(int num);
};


