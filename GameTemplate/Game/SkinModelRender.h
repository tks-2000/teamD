#pragma once
#include "Lighting.h"
class AnimationClip;
class Lighting;

class SkinModelRender : public IGameObject
{
private:
	Model m_model;								//モデル
	ModelInitData m_modelInitData;				//モデルの初期化情報
	Skeleton m_skeleton;						//スケルトン
	CharacterController m_charaCon;				//キャラクターコントローラー

	Vector3 m_position = Vector3::Zero;			//座標
	Vector3 m_scale = Vector3::One;				//拡大率
	Quaternion m_rot = Quaternion::Identity;	//回転

	Lighting m_lighting;						//ライティング

public:
	SkinModelRender();
	~SkinModelRender();

	bool Start();
	void Update();

	void SetPosition(Vector3 pos) { m_position = pos; }
	void SetScale(Vector3 scale) { m_scale = scale; }
	void SetRotation(Quaternion rot) { m_rot = rot; }
	void SetNewModel() { m_model.Init(m_modelInitData); }

	Vector3 GetPosition() { return m_position; }
	Vector3 GetScale() { return m_scale; }
	

	void Init(const char* modelFilePath);
	
};

