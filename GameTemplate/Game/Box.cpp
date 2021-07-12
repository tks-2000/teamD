#include "stdafx.h"
#include "Box.h"

namespace {
	const Vector3 SCALE = { 1.0f,1.0f,1.0f };
	const float BALL_DISTANCE = 100.0f;
	const float PLAYER_DISTANCE = 120.0f;
	const float PLAYER_REPEL = 5.0f;
	const float OPEN_TIME = 75.0f;
	const float FALL = 2.0f;
	const float BOX_FALL_YPOS = 60.0f;
	const float CHARACON_SCALE = 40.0f;
	
	//消滅時に出る煙のエフェクトファイルパス
	const char16_t* SMOKEEFFECT_FILEPATH = u"Assets/effect/smoke.efk";
	const float SMOKEEFFECT_OFFSET_Y = 20.0f;
	const Vector3 SMOKEEFFECT_SCALE = { 30.0f,30.0f,30.0f };

}
Box::Box() {
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_playerNum = m_gameDirector->GetPlayerNum();

	m_ball = FindGO<Ball>(BALL_NAME);
	for (int plNum = 0; plNum < m_playerNum; plNum++) {
		m_player[plNum] = FindGO<Player>(PLAYER_NAME[plNum]);
	}
	m_score = FindGO<Score>(SCORE_NAME);
	m_objects = FindGO<Objects>(OBJECTS_NAME);
	m_timer = FindGO<Timer>(TIMER_NAME);

	m_fall = FALL;
}
Box::~Box() {
	DeleteGO(m_skinModelRender);
}
bool Box::Start() {
	m_animationClips[enAnimation_Close].Load("Assets/animData/box/close.tka");
	m_animationClips[enAnimation_Close].SetLoopFlag(false);
	m_animationClips[enAnimation_Open].Load("Assets/animData/box/open.tka");
	m_animationClips[enAnimation_Open].SetLoopFlag(false);

	m_skinModelRender = NewGO<SkinModelRender>(0);
	//m_skinModelRender->Init("Assets/modelData/object/box.tkm");
	m_skinModelRender->InitA(
		"Assets/modelData/object/box2.tkm", 
		"Assets/modelData/object/box2.tks",
		enModelUpAxisZ,
		m_animationClips,
		enAnimation_Num,
		true
	);

	m_skinModelRender->PlayAnimation(enAnimation_Close, 1.0f);



	m_charaCon.Init(CHARACON_SCALE, CHARACON_SCALE, m_position);

	m_skinModelRender->SetPosition(m_position);

	//初期角度を変える処理
	m_rot.SetRotationDeg(Vector3::AxisY, 45.0f);
	m_skinModelRender->SetRotation(m_rot);

	return true;
}
void Box::Update() {
	DistanceCalculation();


	if (m_position.y > BOX_FALL_YPOS) {
		m_fallSpeed.y -= m_fall;
	}
	else {
		if (m_ballDistance < BALL_DISTANCE /*&& !m_timer->IsCountDown()*/) {
			ballCollider();
		}
	}
	for (int plNum = 0; plNum < m_playerNum; plNum++) {
		if (m_position.y > BOX_FALL_YPOS && m_playerDistance[plNum] < PLAYER_DISTANCE) {
			/// @brief ボールと自分の位置から吹き飛ばされる方向を決める
			Vector3 repulsiveForce = m_player[plNum]->GetPosition() - m_position;
			repulsiveForce.y = FLOAT_0;
			repulsiveForce.Normalize();

			repulsiveForce *= m_fall * PLAYER_REPEL;
			m_player[plNum]->SetMoveSpeed(repulsiveForce * PLAYER_REPEL);

		}
	}

	if (m_openFlag == true) {
		m_openTime++;
	}
	if (m_openTime >= OPEN_TIME) {
		
		//消滅時の煙を出すエフェクト処理
		Vector3 efcPos = m_position;
		efcPos.y += SMOKEEFFECT_OFFSET_Y;
		Effect smokeEffect;
		smokeEffect.Init(SMOKEEFFECT_FILEPATH);
		smokeEffect.Play();
		smokeEffect.SetPosition(efcPos);
		smokeEffect.SetScale(SMOKEEFFECT_SCALE);
		smokeEffect.Update();

		m_score->AddScore(m_ball->GetPlayerInformation());
		m_objects->SetDelFlag(m_boxNum);
		DeleteGO(this);
	}


	if (m_openFlag == false) {
		m_position = m_charaCon.Execute(m_fallSpeed, 1.0f);
	}
	else if(m_isReflect == false){
		//ボールの反射
		BallBound();
		//キャラコンを逃がす処理
		m_charaCon.RemoveRigidBoby();
	}

	//m_charaCon.SetPosition(m_position);
	//m_setPos[setPosNum] = m_position[setPosNum];
	m_skinModelRender->SetPosition(m_position);

}
void Box::ballCollider() {
	m_openFlag = true;
	m_objects->SetBoxOpen(m_boxNum);
	m_skinModelRender->PlayAnimation(enAnimation_Open, 1.0f);
}

void Box::BallBound()
{
	m_isReflect = true;

	Vector3 toBallDir = m_ball->GetPosition() - m_position;
	toBallDir.y = ZeroF;
	toBallDir.Normalize();
	
	m_ball->SetMoveDirection(toBallDir);

}

void Box::DistanceCalculation() {
	m_toBallVec = m_ball->GetPosition() - m_position;
	m_ballDistance = m_toBallVec.Length();
	for (int plNum = 0; plNum < m_playerNum; plNum++) {
		m_toPlayerVec[plNum] = m_player[plNum]->GetPosition() - m_position;
		m_playerDistance[plNum] = m_toPlayerVec[plNum].Length();
	}

	//m_toBallVec.y = FLOAT_0;
	//m_toBallVec.Normalize();
}
void Box::SetBoxPos(Vector3 pos,int num)
{
	m_setPos = pos;
	m_setNum = num;

	m_position = m_setPos;
	m_boxNum = m_setNum;

}
