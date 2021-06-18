#include "stdafx.h"
#include "Ball.h"

namespace
{
	//�O�ՃG�t�F�N�g�֌W
	const char16_t* TRACKEFFECT_PL01_FILEPATH = u"Assets/effect/balltrack.efk";	//�O�ՃG�t�F�N�g�̃t�@�C���p�X
	const Vector3 TRACKEFFECT_SCALE_MAX = { 30.0f,30.0f,1.0f };				//�G�t�F�N�g�̍ő�T�C�Y
	const Vector3 TRACKEFFECT_SCALE_MIN = { 3.0f,3.0f,1.0f };					//�G�t�F�N�g�̍ŏ��T�C�Y	
	const float TRACKEFFECT_BASE_MAX = 30.0f;									//��ԗ������߂邽�߂̍ő��l
	const float TRACKEFFECT_PLAY_MIN = 10.0f;									//�O�Ղ�\�����n�߂鑬�x
}

Ball::Ball()
{

	//�O�՗p�G�t�F�N�g�̃��[�h
	ballTrack.Init(TRACKEFFECT_PL01_FILEPATH);

	m_position.y += 50.0f;

	m_moveFlag = true;
	m_position.y = 1000.0f;

	m_scale = { 0.5f,0.5f,0.5f };
	m_gravity = 5.0f;
}

Ball::~Ball()
{
	DeleteGO(m_skinModelRender);
}

bool Ball::Start()
{
	m_lig = FindGO<Lighting>("Lighting");
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/sphere/sphere.tkm", m_lig->GetLightAddress());
	m_position.y += 40.0f;
	m_charaCon.Init(40.0f, 40.0f, m_position);
	return true;
}

void Ball::Move()
{
	m_moveSpeed += m_moveDirection * m_moveVelocity;
	m_moveSpeed = m_moveSpeed * m_friction;
	m_moveSpeed.y -= m_gravity;

	m_position = m_charaCon.Execute(m_moveSpeed,1.0f);

	if (m_position.x > 650.0f) {
		m_position.x = 650.0f;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.x *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}
	if (m_position.x < -650.0f) {
		m_position.x = -650.0f;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.x *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}
	if (m_position.z > 650.0f) {
		m_position.z = 650.0f;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.z *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}
	if (m_position.z < -650.0f) {
		m_position.z = -650.0f;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.z *= -1.0f;
		m_moveVelocity -= m_moveVelocity * 0.001f;
	}

	m_moveVelocity -= m_moveVelocity * 0.001f;

	if (m_moveSpeed.Length() < 1.0f)
	{
		m_moveDirection = Vector3::Zero;
		m_moveSpeed = Vector3::Zero;
		m_moveFlag = false;
	}

	
}

void Ball::Rotation()
{
	m_axisRotation = Cross(m_moveDirection, Vector3::AxisY);
	m_qRot.SetRotation(m_axisRotation, m_angle);
	m_angle -= 0.1f;
}

void Ball::PlayTrackEffect()
{
	//�O�՗p�G�t�F�N�g�Đ�����//
	//�G�t�F�N�g�g�嗦
	Vector3 efcScale = Vector3::One;
	//�g��̕�ԗ�
	float scaleRate = 0.0f;

	//�G�t�F�N�g�g�嗦���ő�ɂ���ۂ̊�l
	float rateBase = TRACKEFFECT_BASE_MAX;
	//���݂̑��x���ő�l�ɑ΂��Ăǂꂭ�炢�̊����Ȃ̂����v�Z
	float maxRate = m_moveVelocity / rateBase;

	//1.0�𒴂���Ƃ���1.0�ɂ���
	if (maxRate >= 1.0f) {
		maxRate = 1.0f;
	}

	//����ꂽ�������ԗ��ɔ��f(2�悵�Ă���)
	scaleRate = maxRate * maxRate;

	//scaleRate�̒l�ɉ����ăG�t�F�N�g�g�嗦����`�⊮����
	efcScale.Lerp(scaleRate, TRACKEFFECT_SCALE_MIN, TRACKEFFECT_SCALE_MAX);

	//���x�����l�ȏ�̂Ƃ��O�ՃG�t�F�N�g�𔭐�
	if (m_moveVelocity > TRACKEFFECT_PLAY_MIN) {
		ballTrack.Play();

		ballTrack.SetScale(efcScale);
	}

}

void Ball::Update()
{
	if (m_moveFlag == true) {
		m_lig->SetPointLightColor(m_pointLigColor);
		Move();
		Rotation();
		PlayTrackEffect();
	}
	else {
		m_lig->SetPointLightColor(COLORLESS);
	}

	Vector3 modelpos = m_position;
	modelpos.y += 60.0f;
	m_skinModelRender->SetPosition(modelpos);
	m_skinModelRender->SetRotation(m_qRot);
	m_skinModelRender->SetScale(m_scale);

	//m_lig->SetPointLighitPos(m_position);
	
	//�O�՗p�G�t�F�N�g���W���{�[���ɍ��킹��
	ballTrack.SetPosition(modelpos);
	//�O�՗p�G�t�F�N�g�̍X�V
	ballTrack.Update();

	m_lig->SetPointLighitPos(modelpos);

}