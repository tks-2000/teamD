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
	
	return true;
}

void SkinModelRender::Init(const char* modelFilePath, Light* lig)
{
	m_modelInitData.m_tkmFilePath = modelFilePath;
	m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";

	m_modelInitData.m_expandConstantBuffer = lig;
	m_modelInitData.m_expandConstantBufferSize = sizeof(*lig);

	//���������Ń��f��������������
	m_model.Init(m_modelInitData);
}

void SkinModelRender::Init(const char* modelFilePath)
{
	m_modelInitData.m_tkmFilePath = modelFilePath;
	m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";

	m_modelInitData.m_expandConstantBuffer = m_lig->GetLightAddress();
	m_modelInitData.m_expandConstantBufferSize = sizeof(m_lig->GetLight());

	//���������Ń��f��������������
	m_model.Init(m_modelInitData);
}

void SkinModelRender::InitA(const char* modelFilePath, const char* skeletonPath, AnimationClip* animationClip, int animationNum)
{
	m_modelInitData.m_tkmFilePath = modelFilePath;
	m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";

	if (skeletonPath != nullptr) {
		m_skeleton.Init(skeletonPath);
		m_modelInitData.m_skeleton = &m_skeleton;
	}

	m_modelInitData.m_expandConstantBuffer = m_lig->GetLightAddress();
	m_modelInitData.m_expandConstantBufferSize = sizeof(m_lig->GetLight());

	m_animationClip = animationClip;

	m_animation.Init(m_skeleton, m_animationClip, animationNum);


	//���������Ń��f��������������
	m_model.Init(m_modelInitData);
}

void SkinModelRender::PlayAnimation(int animNo, float interpolateTime)
{
	m_animation.Play(animNo, interpolateTime);
}

void SkinModelRender::Update()
{
	m_skeleton.Update(m_model.GetWorldMatrix());

	m_animation.Progress(1.0f / 60.0f);

	m_model.UpdateWorldMatrix(m_position,m_qRot,m_scale);
	

}

void SkinModelRender::Render(RenderContext& rd)
{
	m_model.Draw(rd);
}