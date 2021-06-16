#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	
}

BackGround::~BackGround()
{
	DeleteGO(m_skinModelRender);
}

bool BackGround::Start()
{
	m_lig = FindGO<Lighting>("Lighting");
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/bg/testmap.tkm", m_lig->GetLightAddress());
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_qRot);
	m_skinModelRender->SetScale(m_scale);
	Matrix pos, rot, scale,world;
	pos.MakeTranslation(m_position);
	rot.MakeRotationFromQuaternion(m_qRot);
	scale.MakeScaling(m_scale);
	m_world = pos * rot * scale;
	m_paysicsStaticObject.CreateFromModel(m_skinModelRender->GetModel(), m_skinModelRender->GetModelWorldMatrix());
	
	return true;
}

void BackGround::Update()
{
	
}