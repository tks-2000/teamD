#include "stdafx.h"
#include "Ball.h"

namespace
{
	//軌跡エフェクト関係
	const char16_t* TRACKEFFECT_PL01_FILEPATH = u"Assets/effect/balltrack_low.efk";	//軌跡エフェクトのファイルパス
	//ボールがどのプレイヤーのものかを表すための色
	const char16_t* TRACKEFFECT_MULTIPLE_FILEPATH[PLAYER_NUMBER] = 
	{
		{u"Assets/effect/balltrack_red.efk"},		//1p 赤
		{u"Assets/effect/balltrack_blue.efk"},		//2p 青
		{u"Assets/effect/balltrack_yellow.efk"},	//3p 黄
		{u"Assets/effect/balltrack_green.efk"}		//4p 緑
	};

	//軌跡エフェクトのファイルパス
	const Vector3 TRACKEFFECT_SCALE_MAX = { 60.0f,60.0f,1.0f };					//エフェクトの最大サイズ
	const Vector3 TRACKEFFECT_SCALE_MIN = { 3.0f,3.0f,1.0f };					//エフェクトの最小サイズ	
	const float TRACKEFFECT_BASE_MAX = 40.0f;									//補間率を決めるための最大基準値
	const float TRACKEFFECT_PLAY_MIN = 10.0f;									//軌跡を表示し始める速度
	const int TRACKEFFECT_LERP_POW = 1;											//この値が大きくなるとボールの速度低下時に軌跡エフェクトが小さくなりやすい

	//反射エフェクト関係
	const char16_t* REFLECTEFFECT_FILEPATH = u"Assets/effect/ballreflect.efk";
	const Vector3 REFLECTEFFECT_SCALE = { 20.0f,20.0f,20.0f };

	const float REFLECTE_DISTANCE = 500.0f;

}

Ball::Ball()
{
	//軌跡用エフェクトの初期化
	m_ballTrack.Init(TRACKEFFECT_PL01_FILEPATH);
	//反射エフェクトの初期化
	m_reflectEffect.Init(REFLECTEFFECT_FILEPATH);

	m_position.y += 50.0f;

	m_moveFlag = true;
	m_position.y = 1000.0f;
	m_friction = 0.002f;

	//m_scale = { 0.5f,0.5f,0.5f };
	m_gravity = 1.0f;
}

Ball::~Ball()
{
	DeleteGO(m_skinModelRender);
}

bool Ball::Start()
{
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_lig = FindGO<Lighting>("Lighting");
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/sphere/sphere.tkm", m_lig->GetLightAddress());
	m_position.y += 40.0f;
	m_charaCon.Init(40.0f, 40.0f, m_position);
	
	return true;
}

void Ball::Move()
{
	m_moveSpeed.x = m_moveDirection.x * m_moveVelocity;
	m_moveSpeed.z = m_moveDirection.z * m_moveVelocity;

	m_moveSpeed.y -= m_gravity;

	m_position = m_charaCon.Execute(m_moveSpeed,1.0f);

	//壁で反射する処理
	if (m_position.x > REFLECTE_DISTANCE) {
		m_position.x = REFLECTE_DISTANCE;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.x *= -1.0f;
		m_moveVelocity -= m_moveVelocity * m_friction;

		PlayReflectEffect(REFLECTE_DISTANCE, 80.0f, m_position.z, 90.0f);
		m_se->PlayReflectSe();

	}
	if (m_position.x < -REFLECTE_DISTANCE) {
		m_position.x = -REFLECTE_DISTANCE;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.x *= -1.0f;
		m_moveVelocity -= m_moveVelocity * m_friction;

		PlayReflectEffect(-REFLECTE_DISTANCE, 80.0f, m_position.z, -90.0f);
		m_se->PlayReflectSe();

	}
	if (m_position.z > REFLECTE_DISTANCE) {
		m_position.z = REFLECTE_DISTANCE;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.z *= -1.0f;
		m_moveVelocity -= m_moveVelocity * m_friction;

		PlayReflectEffect(m_position.x, 80.0f, REFLECTE_DISTANCE, 180.0f);
		m_se->PlayReflectSe();

	}
	if (m_position.z < -REFLECTE_DISTANCE) {
		m_position.z = -REFLECTE_DISTANCE;
		m_charaCon.SetPosition(m_position);
		m_moveDirection.z *= -1.0f;
		m_moveVelocity -= m_moveVelocity * m_friction;

		PlayReflectEffect(m_position.x, 80.0f, -REFLECTE_DISTANCE, 0.0f);
		m_se->PlayReflectSe();

	}

	m_moveVelocity -= pow(m_moveVelocity * m_friction,1.5);

	if (m_moveSpeed.Length() < 1.0f || m_gameDirector->IsMainGame() == false)
	{
		m_moveDirection = Vector3::Zero;
		m_moveSpeed = Vector3::Zero;
		m_moveVelocity = FLOAT_0;
		m_moveFlag = false;
	}

	
}

void Ball::Rotation()
{
	m_axisRotation = Cross(m_moveDirection, Vector3::AxisY);
	m_qRot.SetRotation(m_axisRotation, m_angle);
	m_angle -= GetVelocity() * 0.1f / 5.5f;
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

	//得られた割合を補間率に反映(累乗している)
	for (int pow = 1; pow < TRACKEFFECT_LERP_POW; pow++) {
		maxRate *= maxRate;
	}
	scaleRate = maxRate;

	//scaleRateの値に応じてエフェクト拡大率を線形補完する
	efcScale.Lerp(scaleRate, TRACKEFFECT_SCALE_MIN, TRACKEFFECT_SCALE_MAX);

	//速度が一定値以上のとき軌跡エフェクトを発生
	if (m_moveVelocity > TRACKEFFECT_PLAY_MIN) {
		m_ballTrack.Play();
		m_ballTrack.SetScale(efcScale);
	}

}

void Ball::ChangeTrackEffect()
{
	//最後にキックしたプレイヤーに対応したカラーのエフェクトで初期化
	m_ballTrack.Init(TRACKEFFECT_MULTIPLE_FILEPATH[m_playerNum]);
}

void Ball::PlayReflectEffect
	(const float& posX, 
	const float& posY, 
	const float& posZ,
	const float& angleH)
{
	//反射エフェクトの発生
	m_reflectEffect.Play();
	Vector3 reflectPos = m_position;
	reflectPos.x = posX;
	reflectPos.y = posY;
	reflectPos.z = posZ;

	Quaternion reflectRot = Quaternion::Identity;
	reflectRot.SetRotationDeg(Vector3::AxisY, angleH);
	m_reflectEffect.SetPosition(reflectPos);
	m_reflectEffect.SetScale(REFLECTEFFECT_SCALE);
	m_reflectEffect.SetRotation(reflectRot);
	m_reflectEffect.Update();
}

void Ball::Update()
{
	//軌跡用エフェクトの変更処理
	if (m_playerNumPrevFrame != m_playerNum) {
		ChangeTrackEffect();
	}

	if (m_moveFlag == true) {
		m_lig->SetPointLightColor(4,m_pointLigColor);
		m_lig->SetPointLightRange(4, 1000.0f);
		Move();
		Rotation();
		PlayTrackEffect();
		
	}
	else {
		m_lig->SetPointLightColor(4,COLORLESS);
		m_playerNum = 4;
	}

	Vector3 modelpos = m_position;
	modelpos.y += 60.0f;
	m_skinModelRender->SetPosition(modelpos);
	m_skinModelRender->SetRotation(m_qRot);
	m_skinModelRender->SetScale(m_scale);

	m_lig->SetPointLighitPos(4,m_position);
	
	//軌跡用エフェクト座標をボールに合わせる
	m_ballTrack.SetPosition(modelpos);
	//軌跡用エフェクトの更新
	m_ballTrack.Update();

	m_lig->SetPointLighitPos(4,modelpos);

	//現フレームのプレイヤーナンバーを記録
	if (m_playerNumPrevFrame != m_playerNum) {
		m_playerNumPrevFrame = m_playerNum;
	}

}