#pragma once
#include "math.h"
#include "stdafx.h"

const int SPOT_LIGHT_SUM = 4;

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
	SpotLight spotLight[SPOT_LIGHT_SUM];					//スポットライト
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


	Light& GetLight() { return m_light; }
	
	/// @brief ライトの構造体を入手
	/// @return ライト構造体のアドレス
	Light* GetLightAddress() { return &m_light; }


	/// @brief ディレクションライトの初期化
	void InitDirectionLight();

	/// @brief ディレクションライトの方向を入手
	/// @return ディレクションライトの方向
	Vector3 GetDirectionLightDirection() { return m_light.directionLight.direction; }

	/// @brief ディレクションライトの方向を設定
	/// @param dirLigVec ディレクションライトに設定する方向
	void SetDirectionLightDirection(Vector3 dirLigVec) { m_light.directionLight.direction = dirLigVec; m_light.directionLight.direction.Normalize(); }

	void RotationDirectionLight();

	/// @brief ポイントライトの初期化
	void InitPointLight();

	void MovePointLight();

	/// @brief ポイントライトの座標を入手
	/// @return ポイントライトの座標
	Vector3 GetPointLightPos() { return m_light.pointLight.position; }

	/// @brief ポイントライトの座標を設定
	/// @param pos ポイントライトに設定する座標
	void SetPointLighitPos(Vector3 pos) { m_light.pointLight.position = pos; }

	/// @brief ポイントライトのカラーを設定
	/// @param color ポイントライトに設定する座標
	void SetPointLightColor(Vector3 color) { m_light.pointLight.color = color; }
	
	/// @brief スポットライトの初期化
	void InitSpotLight(int num);

	void MoveSpotLight(int num);

	void RotationSpotLight(int num);

	/// @brief スポットライトの座標を入手
	/// @param num 入手するスポットライトの番号
	/// @return スポットライトの座標
	Vector3 GetSpotLightPos(int num) { return m_light.spotLight[num].position; }

	/// @brief スポットライトの座標を設定
	/// @param num 設定したいスポットライトの番号
	/// @param pos スポットライトに設定する座標
	void SetSpotLightPos(int num,Vector3 pos) { m_light.spotLight[num].position = pos; }

	/// @brief スポットライトのカラーを設定
	/// @param num 設定したいスポットライトの番号
	/// @param color スポットライトに設定するカラー
	void SetSpotLightColor(int num, Vector3 color) { m_light.spotLight[num].color = color; }

	/// @brief スポットライトの方向を設定
	/// @param num 設定したいスポットライトの番号
	/// @param dir スポットライトに設定する方向
	void SetSpotLightDirection(int num,Vector3 dir) { m_light.spotLight[num].direction = dir; m_light.spotLight[num].direction.Normalize(); }

	/// @brief スポットライトの点滅を設定
	/// @param num 点滅させたいスポットライトの番号
	/// @param Time 点滅させる時間
	/// @param interval 点滅の間隔
	void SetSpotLightBlinking(int num, float time,float interval);

	/// @brief 半球ライトの初期化
	void InitHemiSphereLight();

private:
	/// @brief ライティング全てのデータ
	Light m_light;

	/// @brief スポットライトの点滅フラグ
	bool m_spLigBlink[SPOT_LIGHT_SUM] = { false };
	/// @brief スポットライトの点滅時間
	float m_spLigBlinkTime[SPOT_LIGHT_SUM] = { 0.0f };
	/// @brief スポットライトの切り替え時間
	float m_spLigBlinkSwitchingTime[SPOT_LIGHT_SUM] = { 0.0f };
	/// @brief スポットライトの点滅間隔
	float m_spLigBlinkInterval[SPOT_LIGHT_SUM] = { 0.0f };
	/// @brief スポットライトを点滅させるカラー
	Vector3 m_spLigColor[SPOT_LIGHT_SUM] = { {Vector3::Zero},{Vector3::Zero},{Vector3::Zero},{Vector3::Zero} };

	bool m_spLigLit[SPOT_LIGHT_SUM] = { true };

	void SpotLightBlinking(int num);
};


