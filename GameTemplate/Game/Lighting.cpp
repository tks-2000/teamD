#include "stdafx.h"
#include "Lighting.h"
#include "math.h"

Lighting::Lighting()
{
	InitDirectionLight();
	
	for (int spotLigNo = 0; spotLigNo < SPOT_LIGHT_SUM; spotLigNo++) {
		InitSpotLight(spotLigNo);
		
	}
	for (int pointLigNo = 0; pointLigNo < POINT_LIGHT_SUM; pointLigNo++) {
		InitPointLight(pointLigNo);
	}
	InitHemiSphereLight();

	//���_�̈ʒu
	m_light.eyePos = g_camera3D->GetPosition();

	//����
	m_light.ambientlight.x = 0.3f;
	m_light.ambientlight.y = 0.3f;
	m_light.ambientlight.z = 0.3f;
}

Lighting::~Lighting()
{

}

bool Lighting::Start()
{

	return true;
}

void Lighting::Update()
{
	for (int spLigNum = 0; spLigNum < SPOT_LIGHT_SUM; spLigNum++) {
		if (m_spLigBlink[spLigNum] == true) {
			SpotLightBlinking(spLigNum);
		}
	}
	for (int ptLigNum = 0; ptLigNum < POINT_LIGHT_SUM; ptLigNum++) {
		if (m_ptLigBlink[ptLigNum] == true) {
			PointLightBlinking(ptLigNum);
		}
	}

	RotationDirectionLight();
}

void Lighting::InitDirectionLight()
{
	//�f�B���N�V�������C�g�̕���
	m_light.directionLight.direction.x = 0.0f;
	m_light.directionLight.direction.y = 1.0f;
	m_light.directionLight.direction.z = -1.0f;
	//���K������
	m_light.directionLight.direction.Normalize();

	//�f�B���N�V�������C�g�̃J���[
	m_light.directionLight.color.x = 0.5f;
	m_light.directionLight.color.y = 0.5f;
	m_light.directionLight.color.z = 0.5f;
}

void Lighting::RotationDirectionLight()
{
	
	Quaternion qRot;
	
	qRot.SetRotationDegY(0.5f);

	
	qRot.Apply(m_light.directionLight.direction);
}

void Lighting::InitPointLight(int num)
{
	//�|�C���g���C�g�̍��W
	m_light.pointLight[num].position.x = 0.0f;
	m_light.pointLight[num].position.y = 0.0f;
	m_light.pointLight[num].position.z = 0.0f;

	//�|�C���g���C�g�̃J���[
	m_light.pointLight[num].color.x = 0.0f;
	m_light.pointLight[num].color.y = 0.0f;
	m_light.pointLight[num].color.z = 0.0f;

	//�|�C���g���C�g�̉e���͈�
	m_light.pointLight[num].Range = 0.0f;
}

void Lighting::MovePointLight()
{
	//���X�e�B�b�N���͂Ń|�C���g���C�g�̍��W�𑀍�
	/*m_light.pointLight.position.x -= g_pad[1]->GetLStickXF();
	if (g_pad[0]->IsPress(enButtonB)) {
		m_light.pointLight.position.y += g_pad[1]->GetLStickYF();
	}
	else {
		m_light.pointLight.position.z -= g_pad[1]->GetLStickYF();
	}
	if (g_pad[0]->IsPress(enButtonA)) {
		m_light.pointLight.position = Vector3::Zero;
	}*/
}
void Lighting::SetPointLightBlinking(int num, float time, float interval)
{
	if (m_ptLigBlink[num] == false) {
		m_ptLigBlink[num] = true;
		m_ptLigBlinkTime[num] = time;
		m_ptLigBlinkInterval[num] = interval;
		m_ptLigColor[num] = m_light.pointLight[num].color;
	}
}

void Lighting::PointLightBlinking(int num)
{
	m_ptLigBlinkTime[num] -= g_gameTime->GetFrameDeltaTime();
	m_ptLigBlinkSwitchingTime[num] += g_gameTime->GetFrameDeltaTime();
	if (m_ptLigBlinkTime[num] <= FLOAT_0) {
		m_ptLigBlink[num] = false;
		m_light.pointLight[num].color = m_ptLigColor[num];
		m_ptLigBlinkSwitchingTime[num] = FLOAT_0;
	}
	else {
		if (m_ptLigBlinkSwitchingTime[num] >= m_ptLigBlinkInterval[num]) {
			if (m_ptLigLit[num] == true) {
				m_light.pointLight[num].color = COLORLESS;
				m_ptLigLit[num] = false;
			}
			else {
				m_light.pointLight[num].color = m_ptLigColor[num];
				m_ptLigLit[num] = true;
			}
			m_ptLigBlinkSwitchingTime[num] = FLOAT_0;
		}
	}
}

void Lighting::ResetPointLight()
{
	for (int ptLig = 0; ptLig < POINT_LIGHT_SUM; ptLig++) {
		InitPointLight(ptLig);
	}
}

void Lighting::InitSpotLight(int num)
{
	//�X�|�b�g���C�g�̍��W
	m_light.spotLight[num].position.x = 0.0f;
	m_light.spotLight[num].position.y = 1000.0f;
	m_light.spotLight[num].position.z = 0.0f;

	//�X�|�b�g���C�g�̃J���[
	m_light.spotLight[num].color.x = 0.0f;
	m_light.spotLight[num].color.y = 0.0f;
	m_light.spotLight[num].color.z = 0.0f;

	//�X�|�b�g���C�g�̕���
	m_light.spotLight[num].direction.x = 0.0f;
	m_light.spotLight[num].direction.y = -1.0f;
	m_light.spotLight[num].direction.z = 0.0f;
	//���K������B
	m_light.spotLight[num].direction.Normalize();

	//�ˏo�͈͂�ݒ�
	m_light.spotLight[num].Range = 300.0f;

	//�ˏo�p�x��ݒ�
	m_light.spotLight[num].angle = Math::DegToRad(10.0f);
}

void Lighting::MoveSpotLight(int num)
{
	//���X�e�B�b�N���͂ŃX�|�b�g���C�g�̍��W�𑀍�
	m_light.spotLight[num].position.x -= g_pad[1]->GetLStickXF();
	if (g_pad[0]->IsPress(enButtonB)) {
		m_light.spotLight[num].position.y += g_pad[1]->GetLStickYF();
	}
	else {
		m_light.spotLight[num].position.z -= g_pad[1]->GetLStickYF();
	}
	if (g_pad[0]->IsPress(enButtonA)) {
		m_light.spotLight[num].position = Vector3::Zero;
	}
}

void Lighting::SetSpotLightBlinking(int num, float time, float interval) {
	m_spLigBlink[num] = true;
	m_spLigBlinkTime[num] = time;
	m_spLigBlinkInterval[num] = interval;
	m_spLigColor[num] = m_light.spotLight[num].color;
}

void Lighting::SpotLightBlinking(int num) {
	m_spLigBlinkTime[num] -= g_gameTime->GetFrameDeltaTime();
	m_spLigBlinkSwitchingTime[num] += g_gameTime->GetFrameDeltaTime();
	if (m_spLigBlinkTime[num] <= FLOAT_0) {
		m_spLigBlink[num] = false;
		m_light.spotLight[num].color = m_spLigColor[num];
		m_spLigBlinkSwitchingTime[num] = FLOAT_0;
	}
	else {
		if (m_spLigBlinkSwitchingTime[num] >= m_spLigBlinkInterval[num]) {
			if (m_spLigLit[num] == true) {
				m_light.spotLight[num].color = COLORLESS;
				m_spLigLit[num] = false;
			}
			else {
				m_light.spotLight[num].color = m_spLigColor[num];
				m_spLigLit[num]=true;
			}
			m_spLigBlinkSwitchingTime[num] = FLOAT_0;
		}
	}
}

void Lighting::RotationSpotLight(int num)
{
	//�E�X�e�B�b�N���͂ŃX�|�b�g���C�g�̕����𑀍�
	Quaternion qRotY;
	qRotY.SetRotationY(g_pad[num]->GetRStickXF() * 0.01f);
	qRotY.Apply(m_light.spotLight[num].direction);
	Vector3 rotAxis;
	rotAxis.Cross(g_vec3AxisY, m_light.spotLight[num].direction);
	Quaternion qRotX;
	qRotX.SetRotation(rotAxis,-g_pad[1]->GetRStickYF() * 0.01f);
	qRotX.Apply(m_light.spotLight[num].direction);
}

void Lighting::ResetSpotLight()
{
	for (int spotLigNo = 0; spotLigNo < SPOT_LIGHT_SUM; spotLigNo++) {
		InitSpotLight(spotLigNo);
	}
}

void Lighting::InitHemiSphereLight()
{
	//�n�ʂ̏Ƃ�Ԃ��J���[
	m_light.hemiSphereLight.groundColor.x = 0.1f;
	m_light.hemiSphereLight.groundColor.y = 0.1f;
	m_light.hemiSphereLight.groundColor.z = 0.1f;

	//�V�����C�g�̃J���[
	m_light.hemiSphereLight.skyColor.x = -0.3f;
	m_light.hemiSphereLight.skyColor.y = -0.3f;
	m_light.hemiSphereLight.skyColor.z = -0.3f;

	//�n�ʂ̖@����ݒ�
	m_light.hemiSphereLight.groundNormal.x = 0.0f;
	m_light.hemiSphereLight.groundNormal.y = 1.0f;
	m_light.hemiSphereLight.groundNormal.z = 0.0f;

}