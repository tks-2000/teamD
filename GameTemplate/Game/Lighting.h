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

struct Light
{
	DirectionLight directionLight;		//ディレクションライト
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
	Light m_light;		//ライト

private:
	

};


