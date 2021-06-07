#include "stdafx.h"
#include "Lighting.h"
#include "math.h"

Lighting::Lighting()
{
	InitDirectionLight();
	InitPointLight();

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
	//ディレクションライトの方向
	m_light.directionLight.direction.x = 1.0f;
	m_light.directionLight.direction.y = -1.0f;
	m_light.directionLight.direction.z = -1.0f;
	//正規化する
	m_light.directionLight.direction.Normalize();

	//ディレクションライトのカラー
	m_light.directionLight.color.x = 0.5f;
	m_light.directionLight.color.y = 0.5f;
	m_light.directionLight.color.z = 0.5f;
}

void Lighting::RotationDirectionLight()
{
	//右スティック入力でディレクションライトの方向を操作
	Quaternion qRot;
	qRot.SetRotationDegY(-g_pad[0]->GetRStickXF());
	qRot.Apply(m_light.directionLight.direction);
	qRot.SetRotationDegX(-g_pad[0]->GetRStickYF());
	qRot.Apply(m_light.directionLight.direction);
}

void Lighting::InitPointLight()
{
	//ポイントライトの座標
	m_light.pointLight.position.x = 0.0f;
	m_light.pointLight.position.y = 50.0f;
	m_light.pointLight.position.z = 50.0f;

	//ポイントライトのカラー
	m_light.pointLight.color.x = 5.0f;
	m_light.pointLight.color.y = 0.0f;
	m_light.pointLight.color.z = 0.0f;

	//ポイントライトの影響範囲
	m_light.pointLight.Range = 100.0f;
}

void Lighting::MovePointLight()
{
	//左スティック入力でポイントライトの座標を操作
	m_light.pointLight.position.x -= g_pad[0]->GetLStickXF();
	if (g_pad[0]->IsPress(enButtonB)) {
		m_light.pointLight.position.y += g_pad[0]->GetLStickYF();
	}
	else {
		m_light.pointLight.position.z += g_pad[0]->GetLStickYF();
	}
	if (g_pad[0]->IsPress(enButtonA)) {
		m_light.pointLight.position = Vector3::Zero;
	}
}

bool Lighting::Start()
{
	
	return true;
}

void Lighting::Update()
{

}