#pragma once
#include "math.h"
#include "stdafx.h"

/// @brief ディレクションライト構造体
struct DirectionLight
{
	Vector3 direction = Vector3::Zero;	//ライトの方向
	float pad0 = 0.0f;					//パディング
	Vector3 color = Vector3::Zero;		//ライトのカラー
	float pad1 = 0.0f;					//パディング
	
};

/// @brief ポイントライト構造体
struct PointLight
{
	Vector3 position = Vector3::Zero;	//位置
	float pad0 = 0.0f;					//パディング
	Vector3 color = Vector3::Zero;		//カラー
	float Range = 0.0f;					//影響範囲

};

/// @brief スポットライト構造体
struct SpotLight
{
	Vector3 position = Vector3::Zero;	//位置
	float pad0 = 0.0f;					//パディング
	Vector3 color = Vector3::Zero;		//カラー
	float Range = 0.0f;					//影響範囲
	Vector3 direction = Vector3::Zero;	//射出方向
	float angle = 0.0f;					//射出角度

};

/// @brief 半球ライト構造体
struct HemiSphereLight
{
	Vector3 groundColor = Vector3::Zero;	//地面色
	float pad0 = 0.0f;						//パディング
	Vector3 skyColor = Vector3::Zero;		//天球色
	float pad1 = 0.0f;						//パディング
	Vector3 groundNormal = Vector3::Zero;	//地面の法線
	float pad2 = 0.0f;						//パディング
};

/// @brief ライト全ての構造体
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

	/// @brief ライトの構造体を入手
	/// @return ライト構造体のアドレス
	Light* GetLightAddress() { return &m_light; }

	/// @brief ディレクションライトの方向を入手
	/// @return 方向
	Vector3 GetDirectionLightDirection() { return m_light.directionLight.direction; }

	/// @brief ディレクションライトの方向を設定
	/// @param dirLigVec 正規化された方向
	void SetDirectionLightDirection(Vector3 dirLigVec) { m_light.directionLight.direction = dirLigVec; }

	void RotationDirectionLight();

	void InitPointLight();

	void MovePointLight();

	/// @brief ポイントライトの座標を入手
	/// @return ポイントライトの座標
	Vector3 GetPointLightPos() { return m_light.pointLight.position; }
	
	void InitSpotLight();

	void MoveSpotLight();

	void RotationSpotLight();

	/// @brief スポットライトの座標を入手
	/// @return スポットライトの座標
	Vector3 GetSpotLightPos() { return m_light.spotLight.position; }

	void InitHemiSphereLight();

private:
	Light m_light;		//ライト

};


