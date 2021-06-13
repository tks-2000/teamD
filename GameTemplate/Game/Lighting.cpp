#include "stdafx.h"
#include "Lighting.h"
#include "math.h"

Lighting::Lighting()
{
	InitDirectionLight();
	InitPointLight();
	InitSpotLight();
	InitHemiSphereLight();

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

bool Lighting::Start()
{

	return true;
}

void Lighting::Update()
{
	RotationDirectionLight();
	/*if (g_pad[1]->IsPress(enButtonSelect)) {
		
		MovePointLight();
	}
	else {
		RotationSpotLight();
		MoveSpotLight();
	}*/
	
}

void Lighting::InitDirectionLight()
{
	//ディレクションライトの方向
	m_light.directionLight.direction.x = 0.0f;
	m_light.directionLight.direction.y = 0.0f;
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
	if (g_pad[0]->IsPress(enButtonRB1)) {
		qRot.SetRotationDegY(1.0f);
	}
	if (g_pad[0]->IsPress(enButtonLB1)) {
		qRot.SetRotationDegY(-1.0f);
	}
	qRot.Apply(m_light.directionLight.direction);
	if (g_pad[0]->IsPress(enButtonRB2)) {
		qRot.SetRotationDegX(1.0f);
	}
	if (g_pad[0]->IsPress(enButtonLB2)) {
		qRot.SetRotationDegX(-1.0f);
	}
	qRot.Apply(m_light.directionLight.direction);
}

void Lighting::InitPointLight()
{
	//ポイントライトの座標
	m_light.pointLight.position.x = 50.0f;
	m_light.pointLight.position.y = 50.0f;
	m_light.pointLight.position.z = 50.0f;

	//ポイントライトのカラー
	m_light.pointLight.color.x = 5.0f;
	m_light.pointLight.color.y = 0.0f;
	m_light.pointLight.color.z = 0.0f;

	//ポイントライトの影響範囲
	m_light.pointLight.Range = 1000.0f;
}

void Lighting::MovePointLight()
{
	//左スティック入力でポイントライトの座標を操作
	m_light.pointLight.position.x -= g_pad[1]->GetLStickXF();
	if (g_pad[0]->IsPress(enButtonB)) {
		m_light.pointLight.position.y += g_pad[1]->GetLStickYF();
	}
	else {
		m_light.pointLight.position.z -= g_pad[1]->GetLStickYF();
	}
	if (g_pad[0]->IsPress(enButtonA)) {
		m_light.pointLight.position = Vector3::Zero;
	}
}

void Lighting::InitSpotLight()
{
	//スポットライトの座標
	m_light.spotLight.position.x = -50.0f;
	m_light.spotLight.position.y = 50.0f;
	m_light.spotLight.position.z = 50.0f;

	//スポットライトのカラー
	m_light.spotLight.color.x = 1.0f;
	m_light.spotLight.color.y = 1.0f;
	m_light.spotLight.color.z = 1.0f;

	//スポットライトの方向
	m_light.spotLight.direction.x = 1.0f;
	m_light.spotLight.direction.y = -1.0f;
	m_light.spotLight.direction.z = 1.0f;
	//正規化する。
	m_light.spotLight.direction.Normalize();

	//射出範囲を設定
	m_light.spotLight.Range = 300.0f;

	//射出角度を設定
	m_light.spotLight.angle = Math::DegToRad(25.0f);
}

void Lighting::MoveSpotLight()
{
	//左スティック入力でスポットライトの座標を操作
	m_light.spotLight.position.x -= g_pad[1]->GetLStickXF();
	if (g_pad[0]->IsPress(enButtonB)) {
		m_light.spotLight.position.y += g_pad[1]->GetLStickYF();
	}
	else {
		m_light.spotLight.position.z -= g_pad[1]->GetLStickYF();
	}
	if (g_pad[0]->IsPress(enButtonA)) {
		m_light.spotLight.position = Vector3::Zero;
	}
}

void Lighting::RotationSpotLight()
{
	//右スティック入力でスポットライトの方向を操作
	Quaternion qRotY;
	qRotY.SetRotationY(g_pad[1]->GetRStickXF() * 0.01f);
	qRotY.Apply(m_light.spotLight.direction);
	Vector3 rotAxis;
	rotAxis.Cross(g_vec3AxisY, m_light.spotLight.direction);
	Quaternion qRotX;
	qRotX.SetRotation(rotAxis,-g_pad[1]->GetRStickYF() * 0.01f);
	qRotX.Apply(m_light.spotLight.direction);
}

void Lighting::InitHemiSphereLight()
{
	//地面の照り返しカラー
	m_light.hemiSphereLight.groundColor.x = 0.1f;
	m_light.hemiSphereLight.groundColor.y = 0.1f;
	m_light.hemiSphereLight.groundColor.z = 0.3f;

	//天球ライトのカラー
	m_light.hemiSphereLight.skyColor.x = 0.1f;
	m_light.hemiSphereLight.skyColor.y = 0.3f;
	m_light.hemiSphereLight.skyColor.z = 0.1f;

	//地面の法線を設定
	m_light.hemiSphereLight.groundNormal.x = 0.0f;
	m_light.hemiSphereLight.groundNormal.y = 1.0f;
	m_light.hemiSphereLight.groundNormal.z = 0.0f;

}