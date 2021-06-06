#include "stdafx.h"
#include "Lighting.h"
#include "math.h"

Lighting::Lighting()
{
	InitDirectionLight();

	//視点の位置
	m_light.eyePos = g_camera3D->GetPosition();

	//環境光
	m_light.ambientlight.x = 0.3f;
	m_light.ambientlight.y = 0.3f;
	m_light.ambientlight.z = 0.3f;
}

Lighting::~Lighting()
{

}

void Lighting::InitDirectionLight()
{
	//ライトの方向
	m_light.directionLight.direction.x = 1.0f;
	m_light.directionLight.direction.y = -1.0f;
	m_light.directionLight.direction.z = -1.0f;
	//正規化する
	m_light.directionLight.direction.Normalize();

	//ライトのカラー
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