#include "stdafx.h"
#include "Ball.h"

namespace
{
	//軌跡エフェクト関係
	const char16_t* TRACKEFFECT_PL01_FILEPATH = u"Assets/effect/balltrack.efk";	//軌跡エフェクトのファイルパス
	const Vector3 TRACKEFFECT_SCALE_MAX = { 30.0f,30.0f,1.0f };				//エフェクトの最大サイズ
	const Vector3 TRACKEFFECT_SCALE_MIN = { 3.0f,3.0f,1.0f };					//エフェクトの最小サイズ	
	const float TRACKEFFECT_BASE_MAX = 30.0f;									//補間率を決めるための最大基準値
	const float TRACKEFFECT_PLAY_MIN = 10.0f;									//軌跡を表示し始める速度
}

Ball::Ball()
{

	//軌跡用エフェクトのロード
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
	m_moveSpeed = m_moveDirection * m_moveVelocity;
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
	//軌跡用エフェクト再生処理//
	//エフェクト拡大率
	Vector3 efcScale = Vector3::One;
	//拡大の補間率
	float scaleRate = 0.0f;

	//エフェクト拡大率を最大にする際の基準値
	float rateBase = TRACKEFFECT_BASE_MAX;
	//現在の速度が最大値に対してどれくらいの割合なのかを計算
	float maxRate = m_moveVelocity / rateBase;

	//1.0を超えるときは1.0にする
	if (maxRate >= 1.0f) {
		maxRate = 1.0f;
	}

	//得られた割合を補間率に反映(2乗している)
	scaleRate = maxRate * maxRate;

	//scaleRateの値に応じてエフェクト拡大率を線形補完する
	efcScale.Lerp(scaleRate, TRACKEFFECT_SCALE_MIN, TRACKEFFECT_SCALE_MAX);

	//速度が一定値以上のとき軌跡エフェクトを発生
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
	
	//軌跡用エフェクト座標をボールに合わせる
	ballTrack.SetPosition(m_position);
	//軌跡用エフェクトの更新
	ballTrack.Update();

	m_lig->SetPointLighitPos(modelpos);

}