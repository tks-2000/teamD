#include "stdafx.h"
#include "SkinModelRender.h"
#include "Lighting.h"

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

void SkinModelRender::Init(const char* modelFilePath)
{
	m_modelInitData.m_tkmFilePath = modelFilePath;
	m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";


	m_modelInitData.m_expandConstantBuffer = m_lighting.GetLightAddress();
	m_modelInitData.m_expandConstantBufferSize = sizeof(m_lighting.GetLight());

	//‰Šú‰»î•ñ‚Åƒ‚ƒfƒ‹‚ð‰Šú‰»‚·‚é
	m_model.Init(m_modelInitData);
}

void SkinModelRender::Update()
{

	m_lighting.RotationDirectionLight();
	m_lighting.MovePointLight();

	auto& renderContext = g_graphicsEngine->GetRenderContext();
	m_model.Draw(renderContext);
}