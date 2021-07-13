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
	
	//���Ŏ��ɏo�鉌�̃G�t�F�N�g�t�@�C���p�X
	const char16_t* SMOKEEFFECT_FILEPATH = u"Assets/effect/smoke.efk";
	//�Đ����x�̃I�t�Z�b�g��
	const float SMOKEEFFECT_OFFSET_Y = 20.0f;
	//�X�P�[��
	const Vector3 SMOKEEFFECT_SCALE = { 30.0f,30.0f,30.0f };
	
	//�{�b�N�X���J���Ƃ��ɏo��G�t�F�N�g�̃t�@�C���p�X
	const char16_t* OPENEFFECT_FILEPATH = u"Assets/effect/boxopen.efk";
	//�Đ����x�̃I�t�Z�b�g��
	const float OPENEFFECT_OFFSET_Y = 100.0f;
	//�X�P�[��
	const Vector3 OPENEFFECT_SCALE = { 20.0f,20.0f,20.0f };

}
Box::Box() {

	//���G�t�F�N�g�̏�����
	m_smokeEffect.Init(SMOKEEFFECT_FILEPATH);
	//�{�b�N�X���J���G�t�F�N�g�̏�����
	m_openEffect.Init(OPENEFFECT_FILEPATH);


	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);
	m_playerNum = m_gameDirector->GetPlayerNum();

	m_ball = FindGO<Ball>(BALL_NAME);
	for (int plNum = 0; plNum < m_playerNum; plNum++) {
		m_player[plNum] = FindGO<Player>(PLAYER_NAME[plNum]);
	}
	m_score = FindGO<Score>(SCORE_NAME);
	m_objects = FindGO<Objects>(OBJECTS_NAME);
	m_timer = FindGO<Timer>(TIMER_NAME);
	m_se = FindGO<Se>(SE_NAME);
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

	//�����p�x��ς��鏈��
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
		if (m_ballDistance < BALL_DISTANCE && m_openFlag == false/*&& !m_timer->IsCountDown()*/) {
			ballCollider();
			m_se->PlayBoxCollideSe();
		}
	}
	for (int plNum = 0; plNum < m_playerNum; plNum++) {
		if (m_position.y > BOX_FALL_YPOS && m_playerDistance[plNum] < PLAYER_DISTANCE) {
			/// @brief �{�[���Ǝ����̈ʒu���琁����΂������������߂�
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
		
		//���Ŏ��̉����o���G�t�F�N�g����
		Vector3 efcPos = m_position;
		efcPos.y += SMOKEEFFECT_OFFSET_Y;

		m_smokeEffect.Play();
		m_smokeEffect.SetPosition(efcPos);
		m_smokeEffect.SetScale(SMOKEEFFECT_SCALE);
		m_smokeEffect.Update();

		m_score->AddScore(m_ball->GetPlayerInformation());
		m_objects->SetDelFlag(m_boxNum);
		DeleteGO(this);
	}


	if (m_openFlag == false) {
		m_position = m_charaCon.Execute(m_fallSpeed, 1.0f);
	}
	else if(m_isReflect == false){
		//�{�[���̔���
		BallBound();
		//�L�����R���𓦂�������
		m_charaCon.RemoveRigidBoby();
	}

	//m_charaCon.SetPosition(m_position);
	//m_setPos[setPosNum] = m_position[setPosNum];
	m_skinModelRender->SetPosition(m_position);

}
void Box::ballCollider() {
	//�����J���G�t�F�N�g�Đ�����
	if (m_openFlag == false) {

		Vector3 efcPos = Vector3::Zero;
		efcPos = m_position;
		efcPos.y += OPENEFFECT_OFFSET_Y;

		m_openEffect.Play();
		m_openEffect.SetPosition(efcPos);
		m_openEffect.SetScale(OPENEFFECT_SCALE);
		m_openEffect.Update();
	}
	
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
