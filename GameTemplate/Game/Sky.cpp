#include "stdafx.h"
#include "Sky.h"

Sky::Sky()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/sky.tkm");
	ang = 0.0f;
	m_rotation = Quaternion::Identity;
	SetScaleF(1.0f);
}

Sky::~Sky()
{
	DeleteGO(m_skinModelRender);
}

bool Sky::Start()
{
	m_skinModelRender->SetPosition(Position);
	m_skinModelRender->SetScale(Scale);
	return m_Start;
}

void Sky::Update()
{
	ang += 0.001;
	m_rotation.SetRotation(Vector3::AxisY, ang);
	m_skinModelRender->SetRotation(m_rotation);
}

void Sky::SetScaleV(Vector3 Sca)
{
	Scale = Sca;
	m_Start = true;
}

void Sky::SetScaleF(float Sca)
{
	Scale = { Sca, Sca, Sca };
	m_Start = true;
}