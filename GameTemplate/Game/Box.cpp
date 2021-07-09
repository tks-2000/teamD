#include "stdafx.h"
#include "Box.h"

namespace {
	const Vector3 SCALE = { 1.0f,1.0f,1.0f };
	const float BALL_DISTANCE = 100.0f;
	const float PLAYER_DISTANCE = 120.0f;
	const float PLAYER_REPEL = 5.0f;
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

	m_fall = 2;
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



	m_charaCon.Init(40.0f, 40.0f, m_position);

	m_skinModelRender->SetPosition(m_position);

	//初期角度を変える処理
	m_rot.SetRotationDeg(Vector3::AxisY, 45.0f);
	m_skinModelRender->SetRotation(m_rot);

	return true;
}
void Box::Update() {
	DistanceCalculation();


	if (m_position.y > 50) {
		m_fallSpeed.y -= m_fall;
	}
	if (m_ballDistance < BALL_DISTANCE /*&& !m_timer->IsCountDown()*/) {
		ballCollider();
	}
	for (int plNum = 0; plNum < m_playerNum; plNum++) {
		if (m_position.y > 50 && m_playerDistance[plNum] < PLAYER_DISTANCE) {
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
	if (m_openTime >= 45) {
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
	m_skinModelRender->PlayAnimation(enAnimation_Open, 1.0f);
}

void Box::BallBound()
{
	m_isReflect = true;

	Vector3 toBallDir = m_ball->GetPosition() - m_position;
	toBallDir.y = 0.0f;
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
