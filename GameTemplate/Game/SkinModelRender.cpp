#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::SkinModelRender()
{

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

void SkinModelRender::Update()
{
	m_model.UpdateWorldMatrix(m_position,m_qRot,m_scale);
	auto& renderContext = g_graphicsEngine->GetRenderContext();
	m_model.Draw(renderContext);
}