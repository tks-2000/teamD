#include "stdafx.h"
#include "Box.h"

namespace {
	const Vector3 SCALE = { 1.0f,1.0f,1.0f };
	const float BALL_DISTANCE = 120.0f;
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



	m_skinModelRender->SetPosition(m_position);

	m_charaCon.Init(40.0f, 40.0f, m_position);


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
			/// @brief ƒ{[ƒ‹‚ÆŽ©•ª‚ÌˆÊ’u‚©‚ç‚«”ò‚Î‚³‚ê‚é•ûŒü‚ðŒˆ‚ß‚é
			Vector3 repulsiveForce = m_player[plNum]->GetPosition() - m_position;
			repulsiveForce.y = FLOAT_0;
			repulsiveForce.Normalize();

			repulsiveForce *= m_fall * PLAYER_REPEL;
			m_player[plNum]->SetMoveSpeed(repulsiveForce * PLAYER_REPEL);

		}
	}


	m_position = m_charaCon.Execute(m_fallSpeed, 1.0f);
	m_charaCon.SetPosition(m_position);
	//m_setPos[setPosNum] = m_position[setPosNum];
	m_skinModelRender->SetPosition(m_position);

}
void Box::ballCollider() {
	m_score->AddScore(m_ball->GetPlayerInformation());
	//m_objects->SetDelFlag(m_boxNum);
	m_skinModelRender->PlayAnimation(enAnimation_Open, 1.0f);
	
	//DeleteGO(this);
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
