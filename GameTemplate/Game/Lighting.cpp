#include "stdafx.h"
#include "Lighting.h"
#include "math.h"

Lighting::Lighting()
{
	InitDirectionLight();
	InitPointLight();
	InitSpotLight();

	//���_�̈ʒu
	m_light.eyePos = g_camera3D->GetPosition();

	//����
	m_light.ambientlight.x = 0.3f;
	m_light.ambientlight.y = 0.3f;
	m_light.ambientlight.z = 0.3f;
}

Lighting::~Lighting()
{

}

bool Lighting::Start()
{

	return true;
}

void Lighting::Update()
{
	if (g_pad[0]->IsPress(enButtonSelect)) {
		RotationDirectionLight();
		MovePointLight();
	}
	else {
		RotationSpotLight();
		MoveSpotLight();
	}
	
}

void Lighting::InitDirectionLight()
{
	//�f�B���N�V�������C�g�̕���
	m_light.directionLight.direction.x = 0.0f;
	m_light.directionLight.direction.y = 0.0f;
	m_light.directionLight.direction.z = -1.0f;
	//���K������
	m_light.directionLight.direction.Normalize();

	//�f�B���N�V�������C�g�̃J���[
	m_light.directionLight.color.x = 0.5f;
	m_light.directionLight.color.y = 0.5f;
	m_light.directionLight.color.z = 0.5f;
}

void Lighting::RotationDirectionLight()
{
	//�E�X�e�B�b�N���͂Ńf�B���N�V�������C�g�̕����𑀍�
	Quaternion qRot;
	qRot.SetRotationDegY(-g_pad[0]->GetRStickXF());
	qRot.Apply(m_light.directionLight.direction);
	qRot.SetRotationDegX(-g_pad[0]->GetRStickYF());
	qRot.Apply(m_light.directionLight.direction);
}

void Lighting::InitPointLight()
{
	//�|�C���g���C�g�̍��W
	m_light.pointLight.position.x = 50.0f;
	m_light.pointLight.position.y = 50.0f;
	m_light.pointLight.position.z = 50.0f;

	//�|�C���g���C�g�̃J���[
	m_light.pointLight.color.x = 5.0f;
	m_light.pointLight.color.y = 0.0f;
	m_light.pointLight.color.z = 0.0f;

	//�|�C���g���C�g�̉e���͈�
	m_light.pointLight.Range = 100.0f;
}

void Lighting::MovePointLight()
{
	//���X�e�B�b�N���͂Ń|�C���g���C�g�̍��W�𑀍�
	m_light.pointLight.position.x -= g_pad[0]->GetLStickXF();
	if (g_pad[0]->IsPress(enButtonB)) {
		m_light.pointLight.position.y += g_pad[0]->GetLStickYF();
	}
	else {
		m_light.pointLight.position.z -= g_pad[0]->GetLStickYF();
	}
	if (g_pad[0]->IsPress(enButtonA)) {
		m_light.pointLight.position = Vector3::Zero;
	}
}

void Lighting::InitSpotLight()
{
	//�X�|�b�g���C�g�̍��W
	m_light.spotLight.position.x = -50.0f;
	m_light.spotLight.position.y = 50.0f;
	m_light.spotLight.position.z = 50.0f;

	//�X�|�b�g���C�g�̃J���[
	m_light.spotLight.color.x = 1.0f;
	m_light.spotLight.color.y = 1.0f;
	m_light.spotLight.color.z = 1.0f;

	//�X�|�b�g���C�g�̕���
	m_light.spotLight.direction.x = 1.0f;
	m_light.spotLight.direction.y = -1.0f;
	m_light.spotLight.direction.z = 1.0f;
	//���K������B
	m_light.spotLight.direction.Normalize();

	//�ˏo�͈͂�ݒ�
	m_light.spotLight.Range = 300.0f;

	//�ˏo�p�x��ݒ�
	m_light.spotLight.angle = Math::DegToRad(25.0f);
}

void Lighting::MoveSpotLight()
{
	//���X�e�B�b�N���͂ŃX�|�b�g���C�g�̍��W�𑀍�
	m_light.spotLight.position.x -= g_pad[0]->GetLStickXF();
	if (g_pad[0]->IsPress(enButtonB)) {
		m_light.spotLight.position.y += g_pad[0]->GetLStickYF();
	}
	else {
		m_light.spotLight.position.z -= g_pad[0]->GetLStickYF();
	}
	if (g_pad[0]->IsPress(enButtonA)) {
		m_light.spotLight.position = Vector3::Zero;
	}
}

void Lighting::RotationSpotLight()
{
	//�E�X�e�B�b�N���͂ŃX�|�b�g���C�g�̕����𑀍�
	Quaternion qRotY;
	qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f);
	qRotY.Apply(m_light.spotLight.direction);
	Vector3 rotAxis;
	rotAxis.Cross(g_vec3AxisY, m_light.spotLight.direction);
	Quaternion qRotX;
	qRotX.SetRotation(rotAxis,-g_pad[0]->GetRStickYF() * 0.01f);
	qRotX.Apply(m_light.spotLight.direction);
}