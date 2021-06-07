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

//ライトをまとめた構造体
struct Light
{
	DirectionLight directionLight;		//ディレクションライト
	PointLight pointLight;				//ポイントライト
	Vector3 eyePos = Vector3::Zero;		//視点の位置
	float pad0 = 0.0f;
	Vector3 ambientlight = Vector3::Zero; //環境光
};

class Lighting : public IGameObject
{
public:
	Lighting();
	~Lighting();
	bool Start();
	void Update();

	void InitDirectionLight();

	Light GetLight() { return m_light; }

	Light* GetLightAddress() { return &m_light; }

	Vector3 GetDirectionLightDirection() { return m_light.directionLight.direction; }

	void SetDirectionLightDirection(Vector3 dirLigVec) { m_light.directionLight.direction = dirLigVec; }

	void RotationDirectionLight();

	void InitPointLight();

	void MovePointLight();
	

private:
	Light m_light;		//ライト

};


