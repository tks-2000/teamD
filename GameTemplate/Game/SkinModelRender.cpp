#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::SkinModelRender()
{
	m_lig = FindGO<Lighting>("Lighting");
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

void SkinModelRender::Update()
{
	m_model.UpdateWorldMatrix(m_position,m_qRot,m_scale);
	

}

void SkinModelRender::Render(RenderContext& rd)
{
	m_model.Draw(rd);
}