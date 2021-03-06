#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::SkinModelRender()
{
	m_lig = FindGO<Lighting>(LIGHTING_NAME);
}

SkinModelRender::~SkinModelRender()
{
	
}

bool SkinModelRender::Start()
{
	m_model.UpdateWorldMatrix(m_position, m_qRot, m_scale);
	return true;
}

void SkinModelRender::Init(const char* modelFilePath, Light* lig)
{
	m_modelInitData.m_tkmFilePath = modelFilePath;
	m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";

	m_modelInitData.m_expandConstantBuffer = lig;
	m_modelInitData.m_expandConstantBufferSize = sizeof(*lig);

	//初期化情報でモデルを初期化する
	m_model.Init(m_modelInitData);
}

void SkinModelRender::Init(const char* modelFilePath)
{
	m_modelInitData.m_tkmFilePath = modelFilePath;
	m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";

	m_modelInitData.m_expandConstantBuffer = m_lig->GetLightAddress();
	m_modelInitData.m_expandConstantBufferSize = sizeof(m_lig->GetLight());

	//初期化情報でモデルを初期化する
	m_model.Init(m_modelInitData);
}

void SkinModelRender::InitA(const char* modelFilePath, const char* skeletonPath, EnModelUpAxis enAxsis, AnimationClip* animationClip, int animationNum ,bool cullMode)
{
	m_modelInitData.m_tkmFilePath = modelFilePath;
	m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	m_modelInitData.m_vsEntryPointFunc = "VSMain";
	m_modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";

	if (skeletonPath != nullptr) {
		m_skeleton.Init(skeletonPath);
		m_modelInitData.m_skeleton = &m_skeleton;
	}

	m_modelInitData.m_modelUpAxis = enAxsis;

	m_modelInitData.m_expandConstantBuffer = m_lig->GetLightAddress();
	m_modelInitData.m_expandConstantBufferSize = sizeof(m_lig->GetLight());

	m_animationClip = animationClip;

	m_animation.Init(m_skeleton, m_animationClip, animationNum);

	m_modelInitData.m_cullMode = cullMode;

	//初期化情報でモデルを初期化する
	m_model.Init(m_modelInitData);
}

void SkinModelRender::PlayAnimation(int animNo, float interpolateTime)
{
	m_animation.Play(animNo, interpolateTime);
}

void SkinModelRender::Update()
{

	m_animation.Progress(1.0f / 60.0f);

	m_model.UpdateWorldMatrix(m_position,m_qRot,m_scale);
	
	m_skeleton.Update(m_model.GetWorldMatrix());

}

void SkinModelRender::Render(RenderContext& rd)
{
	m_model.Draw(rd);
}