#include "stdafx.h"
#include "Box.h"

namespace {
	const Vector3 SCALE = { 1.0f,1.0f,1.0f };
	const float BALL_DISTANCE = 120.0f;
}
Box::Box() {
	m_ball = FindGO<Ball>(BALL_NAME);
	//for (int plNum = 0; plNum < m_playerNum; plNum++) {
	//	m_player[plNum] = FindGO<Player>(PLAYER_NAME[plNum]);
	//}
	m_score = FindGO<Score>(SCORE_NAME);
	m_objects = FindGO<Objects>(OBJECTS_NAME);
	m_timer = FindGO<Timer>(TIMER_NAME);

	m_fall = 2;
}
Box::~Box() {
	DeleteGO(m_skinModelRender);
}
bool Box::Start() {
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/object/box.tkm");


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


	m_position = m_charaCon.Execute(m_fallSpeed, 1.0f);
	m_charaCon.SetPosition(m_position);
	//m_setPos[setPosNum] = m_position[setPosNum];
	m_skinModelRender->SetPosition(m_position);

}
void Box::ballCollider() {
	m_score->AddScore(m_ball->GetPlayerInformation());
	m_objects->SetDelFlag(m_boxNum);
	DeleteGO(this);
}
void Box::DistanceCalculation() {
	m_toBallVec = m_ball->GetPosition() - m_position;
	m_ballDistance = m_toBallVec.Length();
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
