#pragma once
#include "math.h"
#include "stdafx.h"

//ディレクションライトの構造体
struct DirectionLight
{
	Vector3 direction = Vector3::Zero;	//ライトの方向
	float pad0 = 0.0f;					//パディング
	Vector3 color = Vector3::Zero;		//ライトのカラー
	float pad1 = 0.0f;					//パディング
	
};

//ポイントライトの構造体
struct PointLight
{
	Vector3 position = Vector3::Zero;	//位置
	float pad0 = 0.0f;					//パディング
	Vector3 color = Vector3::Zero;		//カラー
	float Range = 0.0f;					//影響範囲

};

//スポットライトの構造体
struct SpotLight
{
	Vector3 position = Vector3::Zero;	//位置
	float pad0 = 0.0f;					//パディング
	Vector3 color = Vector3::Zero;		//カラー
	float Range = 0.0f;					//影響範囲
	Vector3 direction = Vector3::Zero;	//射出方向
	float angle = 0.0f;					//射出角度

};

//半球ライトの構造体
struct HemiSphereLight
{
	Vector3 groundColor = Vector3::Zero;	//地面色
	float pad0 = 0.0f;						//パディング
	Vector3 skyColor = Vector3::Zero;		//天球色
	float pad1 = 0.0f;						//パディング
	Vector3 groundNormal = Vector3::Zero;	//地面の法線
	float pad2 = 0.0f;						//パディング
};

//ライトをまとめた構造体
struct Light
{
	DirectionLight directionLight;			//ディレクションライト
	PointLight pointLight;					//ポイントライト
	SpotLight spotLight;					//スポットライト
	HemiSphereLight hemiSphereLight;		//半球ライト
	Vector3 eyePos = Vector3::Zero;			//視点の位置
	float pad0 = 0.0f;						//パディング
	Vector3 ambientlight = Vector3::Zero;	//環境光
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

	void InitHemiSphereLight();

private:
	Light m_light;		//ライト

};


