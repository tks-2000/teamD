#include "stdafx.h"
#include "Lighting.h"
#include "math.h"

Lighting::Lighting()
{
	InitDirectionLight();

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

void Lighting::InitDirectionLight()
{
	//���C�g�̕���
	m_light.directionLight.direction.x = 1.0f;
	m_light.directionLight.direction.y = -1.0f;
	m_light.directionLight.direction.z = -1.0f;
	//���K������
	m_light.directionLight.direction.Normalize();

	//���C�g�̃J���[
	m_light.directionLight.color.x = 1.0f;
	m_light.directionLight.color.y = 1.0f;
	m_light.directionLight.color.z = 1.0f;
}

bool Lighting::Start()
{
	
	return true;
}

void Lighting::Update()
{

}