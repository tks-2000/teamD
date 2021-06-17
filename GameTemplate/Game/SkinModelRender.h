#pragma once
#include "Lighting.h"
class AnimationClip;
class Lighting;

class SkinModelRender : public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Model& GetModel() { return m_model; }


	

	/// @brief モデルの座標を設定
	/// @param pos 座標
	void SetPosition(Vector3 pos) { m_position = pos; }

	/// @brief モデルの大きさを設定
	/// @param scale 拡大率
	void SetScale(Vector3 scale) { m_scale = scale; }

	/// @brief モデルの回転を設定
	/// @param rot クォータニオン
	void SetRotation(Quaternion rot) { m_qRot = rot; }


	void SetNewModel() { m_model.Init(m_modelInitData); }

	/// @brief モデルの座標を入手
	/// @return 座標
	Vector3 GetPosition() { return m_position; }


	/// @brief モデルの初期化
	/// @param modelFilePath モデルのファイルパス
	/// @param lig ライティング構造体のアドレス
	void Init(const char* modelFilePath, Light* lig);

	Matrix GetModelWorldMatrix() { return m_model.GetWorldMatrix(); }
	
private:
	Model m_model;								//モデル
	ModelInitData m_modelInitData;				//モデルの初期化情報
	

	Vector3 m_position = Vector3::Zero;			//座標
	Vector3 m_scale = Vector3::One;				//拡大率
	Quaternion m_qRot = Quaternion::Identity;	//回転

};

