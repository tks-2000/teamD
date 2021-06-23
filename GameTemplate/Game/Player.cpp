#include "stdafx.h"
#include "Player.h"

namespace {
	/// @brief �G�t�F�N�g�p�萔
	//�L�b�N�G�t�F�N�g�̃t�@�C���p�X
	const char16_t* KICKEFFECT_FILEPATH = u"Assets/effect/kick.efk";					
	//�L�b�N�G�t�F�N�g�����ʒu�����߂�l�B0�ɋ߂��قǃv���C���[���
	const float KICKEFFECT_POSITION_RATE = 0.8f;
	//�L�b�N�G�t�F�N�g�̊g�嗦
	const Vector3 KICKEFFECT_SCALE = { 25.0f,25.0f,1.0f };

	//�K�[�h�G�t�F�N�g�t�@�C���p�X
	const char16_t* GUARDEFFECT_FILEPATH = u"Assets/effect/shield.efk";
	//�K�[�h�G�t�F�N�g�̊g�嗦(���̂Ȃ̂�z�������ɂ��g�債�Ă���)
	const Vector3 GUARDEFFECT_SCALE = { 80.0f,80.0f,80.0f };
	//�K�[�h�G�t�F�N�g�����ʒu��y���W�����߂邽�߂̒萔
	const float GUARDEFFECT_POS_Y = 80.0f;

	//�K�[�h�\���G�t�F�N�g�̃t�@�C���p�X
	const char16_t* GUARDEFFECT_BEGIN_FILEPATH = u"Assets/effect/shield_begin.efk";
	//�K�[�h�\���G�t�F�N�g�̊g�嗦
	const Vector3 GUARDEFFECT_BEGIN_SCALE = { 20.0f,20.0f,1.0f };
	
	//�K�[�h�j��G�t�F�N�g�̃t�@�C���p�X
	const char16_t* GUARDEFFECT_BREAK_FILEPATH = u"Assets/effect/shieldbreak.efk";
	//�K�[�h�j��G�t�F�N�g�̊g�嗦
	const Vector3 GUARDEFFECT_BREAK_SCALE = { 15.0f,15.0f,15.0f };

	//�V�[���h�񕜃G�t�F�N�g�̃t�@�C���p�X
	const char16_t* GUARDEFFECT_REPAIR_FILEPATH = u"Assets/effect/shieldrepair.efk";
	//�V�[���h�񕜃G�t�F�N�g�̊g�嗦
	const Vector3 GUARDEFFECT_REPAIR_SCALE = { 12.5f,12.5f,12.5f };

	//�K�[�h�q�b�g�G�t�F�N�g
	const char16_t* GUARDEFFECT_HIT_FILEPATH = u"Assets/effect/shieldhit.efk";
	//�K�[�h�q�b�g�G�t�F�N�g�̊g�嗦
	const Vector3 GUARDEFFECT_HIT_SCALE = { 17.0f,17.0f,17.0f };
	//�K�[�h�q�b�g�G�t�F�N�g�����̋���
	const float GUARDEFFECT_HIT_DISTANCE = 150.0f;


	/// @brief �L�b�N�\�ȋ���
	const float KICK_POSSIBLE_DISTANCE = 200.0f;
	/// @brief �K�[�h�\�ȋ���
	const float GUARD_DISTANCE = 120.0f;
	/// @brief �{�[���ƐڐG���鋗��
	const float COLLIDE_DISTANCE = 80.0f;
	/// @brief ���������ɂȂ鍂��
	const float FALLING_HEIGHT = -1000.0f;
	/// @brief 1P�̏����ʒu
	const Vector3 PLAYER1_STARTPOS = { -600.0f,200.0f,600.0f };
	/// @brief 2P�̏����ʒu
	const Vector3 PLAYER2_STARTPOS = { 600.0f,200.0f,600.0f };
	/// @brief 3P�̏����ʒu
	const Vector3 PLAYER3_STARTPOS = { -600.0f,200.0f,-600.0f };
	/// @brief 4P�̏����ʒu
	const Vector3 PLAYER4_STARTPOS = { 600.0f,200.0f,-600.0f };
	/// @brief �X�|�b�g���C�g�̍���
	const float SPOT_LIGHT_HEIGHT = 800.0f;
	/// @brief �v���C���[�̔��a
	const float PLAYER_RADIUS = 20.0f;
	/// @brief �v���C���[�̍���
	const float PLAYER_HEIGHT = 50.0f;
	/// @brief �ʏ펞�̖��C��
	const float NORMAL_FRICTION = 0.01f;
	/// @brief �_���[�W���̖��C��
	const float DAMAGE_FRICYION = 0.001f;
	/// @brief �_���[�W���󂯂ĕ��A����̂ɂ����鎞��
	const float DAMAGE_RETURN_TIME = 100.0f;
	/// @brief �v���C���[���f���̕\���D��x
	const int PRIORITY = 1;
	/// @brief �v���C���[�̃��X�|�[�����̖��G����
	const float MUTEKI_TIME = 150.0f;
	/// @brief ���X�|�[�����̖��G���Ԃ̏�����
	const float TIME_ZERO = 0.0f;
	/// @brief �X�R�A�̉��Z���l
	const int SCORE_ADD = 100;
	/// @brief �X�R�A�̌��Z���l
	const int SCORE_PULL = -100;
	/// @brief �L�b�N�̃N�[���^�C��
	const int KICK_COOLTIME = 20;
}

Player::Player()
{

	//�v���C���[�̏�����Ԃ�ݒ�
	//�L�b�N���̃G�t�F�N�g��������
	m_kickEffect.Init(KICKEFFECT_FILEPATH);
	//�K�[�h���̃G�t�F�N�g��������
	m_guardEffect.Init(GUARDEFFECT_FILEPATH);
	//�K�[�h�\���G�t�F�N�g��������
	m_guardBeginEffect.Init(GUARDEFFECT_BEGIN_FILEPATH);
	//�K�[�h�j��̃G�t�F�N�g��������
	m_guardBreakEffect.Init(GUARDEFFECT_BREAK_FILEPATH);
	//�V�[���h�񕜂̃G�t�F�N�g��������
	m_shieldRepairEffect.Init(GUARDEFFECT_REPAIR_FILEPATH);
	//�K�[�h�q�b�g�G�t�F�N�g��������
	m_shieldHitEffect.Init(GUARDEFFECT_HIT_FILEPATH);

	

	m_moveVelocity = 0.9f;
	m_kickPower = 5.0f;
	m_gravity = 5.0f;
	m_charaCon.Init(PLAYER_RADIUS, PLAYER_HEIGHT, m_position);
}

Player::~Player()
{
	//�v���C���[���f�����폜
	DeleteGO(m_skinModelRender);
}

bool Player::Start()
{
	//�K�v�ȃf�[�^���擾
	m_lig = FindGO<Lighting>(LIGHTING_NAME);
	m_ball = FindGO<Ball>(BALL_NAME);

	m_animationClips[enAnimation_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimation_Walk].Load("Assets/animData/walk.tka");

	m_animationClips[enAnimation_Idle].SetLoopFlag(true);
	m_animationClips[enAnimation_Walk].SetLoopFlag(true);

	m_skinModelRender = NewGO<SkinModelRender>(PRIORITY);

	m_skinModelRender->InitA(UNITYCHAN_MODEL,"Assets/modelData/unityChan.tks",m_animationClips,enAnimation_Num);
	m_skinModelRender->PlayAnimation(enAnimation_Idle, 1.0f);

	
	m_ui = FindGO<GameUI>(GAME_UI_NAME);

	return true;
}

void Player::SetPlayerNumber(int num)
{
	//�󂯎�����ԍ��ɉ����Ď�������P����ݒ肷��
	m_myNumber = num;
	switch (num)
	{
	case 0: {
		m_playerColor = RED;
		m_startPos = PLAYER1_STARTPOS;
		
	}break;
	case 1: {
		m_playerColor = BLUE;
		m_startPos = PLAYER2_STARTPOS;
	}break;
	case 2: {
		m_playerColor = YELLOW;
		m_startPos = PLAYER3_STARTPOS;
	}break;
	case 3: {
		m_playerColor = GREEN;
		m_startPos = PLAYER4_STARTPOS;
	}break;
	}
	m_position = m_startPos;
	m_charaCon.SetPosition(m_position);
	
	m_lig->SetSpotLightColor(m_myNumber, m_playerColor);
	
}

void Player::Move()
{
	/// @brief �X�e�B�b�N���͂ŃJ���������Ɉړ�
	m_moveSpeed += g_camera3D->GetRight()* m_Lstickx;
	m_moveSpeed += g_camera3D->GetForward()* m_Lsticky;
	
	/// @brief �d�͂�������
	m_moveSpeed.y -= m_gravity;
	
	
	/// @brief �_���[�W�����ǂ����Ŗ��C�͂�ς���
	if (m_damage == false) {
		m_friction = NORMAL_FRICTION;
	}
	else {
		m_friction = DAMAGE_FRICYION;
	}
	/// @brief �ړ����x�ɖ��C�͂�������
	m_moveSpeed -= m_moveSpeed * m_friction;

	if (m_damage == false && m_guard == false && m_moveSpeed.x != FLOAT_0 || m_moveSpeed.z != FLOAT_0) {
		m_direction = m_moveSpeed;
	}
	
	m_moveSpeed *= m_moveVelocity;

	Vector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	if (moveSpeedXZ.LengthSq() < 0.1f) {
		m_moveSpeed.x = FLOAT_0;
		m_moveSpeed.z = FLOAT_0;
 	}

	/// @brief �v���C���[�����������烊�X�|�[������
	if (m_position.y < FALLING_HEIGHT) {
		/// @brief ���X�|�[�����ɃX�R�A�̌��Z
		m_ui->AddScore(m_myNumber, SCORE_PULL);
		/// @brief �G��|�����Ƃ��Ƀ{�[�����R�����v���C���[�ɃX�R�A�̉��Z
		m_ui->AddScore(GetKillerPlayerNumber(),SCORE_ADD);
		ReSpawn();
	}
	
	
}

void Player::Rotation()
{
	/// @brief �_���[�W���A�K�[�h���A�����Ă��Ȃ��Ƃ��͉�]���Ȃ�
	if (m_damage == true || m_guard == true || m_moveSpeed.x == FLOAT_0 && m_moveSpeed.z == FLOAT_0) {
		m_anim = enAnimation_Idle;
		return;
	}
	m_qRot.SetRotation(Vector3::AxisY, atan2(m_moveSpeed.x, m_moveSpeed.z));
	m_anim = enAnimation_Walk;
}

void Player::IsKick()
{
	/// @brief �{�[���Ƃ̋��������ȉ��̎��̂ݔ���
	if (m_ballDistance < KICK_POSSIBLE_DISTANCE) {
		m_direction.Normalize();
		float matchRate = Dot(m_direction, m_toBallVec);
		if (matchRate > 0.7f) {
			m_kickFlag = true;
		}
		else {
			m_kickFlag = false;
		}
	}
	else {
		m_kickFlag = false;
	}
}

void Player::KickBall()
{
	/// @brief �{�[���ɃL�b�N�����ƃL�b�N�͂�`���ē�����
	m_ball->SetMoveDirection(m_direction);
	m_ball->Acceleration(m_kickPower);
	/// @brief �{�[���ɏR�����v���C���[�̐F�Ɛ�����`����
	m_ball->SetBallLightColor(m_playerColor);
	m_ball->SetPlayerInformation(m_myNumber);

	m_ball->MoveStart();


}

void Player::BallCollide()
{
	/// @brief �{�[���Ǝ����̈ʒu���琁����΂������������߂�
	Vector3 repulsiveForce = m_position - m_ball->GetPosition();
	repulsiveForce.y = FLOAT_0;
	repulsiveForce.Normalize();
	if (m_ball->IsMove() == true) {
		repulsiveForce *= m_ball->GetVelocity() * FLOAT_2;
		repulsiveForce.y = m_ball->GetVelocity() * FLOAT_1;
		m_moveSpeed = repulsiveForce * FLOAT_2;
		m_ball->SetMoveDirection(repulsiveForce * FLOAT_MINUS_1);
		m_damage = true;
		/// @brief �R�����v���C���[�ȊO�ɓ�����A���X�|�[��������Ȃ����ɃX�R�A�̉��Z
		if (m_myNumber != m_ball->GetPlayerInformation() && m_dieFlag == false) {
			m_ui->AddScore(m_ball->GetPlayerInformation(), SCORE_ADD);
			SetKillerPlayerNumber(m_myNumber);
		}
	}
	
}

void Player::Guard()
{
	/// @brief �K�[�h���͈ړ����x��������
	m_moveSpeed.x /= FLOAT_2;
	m_moveSpeed.z /= FLOAT_2;
	
	if (m_ballDistance < GUARD_DISTANCE) {

		/// @brief �{�[���̐����ɉ����đϋv�l�����炷
		float shieldDamage = 10.0f * (m_ball->GetVelocity() / 4.0f);
		m_guardDurability -= shieldDamage;
		if (m_guardDurability <= 0.0f)
		{
			m_guardDurability = 0.0f;
			m_breakGuard = true;
			return;
		}

		Vector3 repulsiveForce = m_position - m_ball->GetPosition();
		repulsiveForce.Normalize();
		repulsiveForce *= m_ball->GetVelocity();
		repulsiveForce.y = m_ball->GetVelocity() * FLOAT_01;
		m_moveSpeed += repulsiveForce;
		m_ball->SetVelocity(m_ball->GetVelocity() / FLOAT_2);
		m_ball->SetMoveDirection(repulsiveForce * FLOAT_MINUS_1);
		
		
	}
	/// @brief �K�[�h���͑ϋv�l(guardDurability)�����葱����
	m_guardDurability -= 0.555f;
	if (m_guardDurability <= 0.0f) {
		m_guardDurability = 0.0f;
		m_breakGuard = true;
	}

	if (m_ballDistance < GUARDEFFECT_HIT_DISTANCE && m_ball->IsMove() == true) {
		//�K�[�h�q�b�g�G�t�F�N�g�̔���
		m_shieldHitEffectCounter++;
		if (m_shieldHitEffectCounter % 30 == 1) {

			//�G�t�F�N�g�����ʒu�����߂邽�߂̃x�N�g��
			Vector3 shieldHitPos = Vector3::Zero;

			float shieldHitAngle = 0.0f;

			//���g����{�[���ւ̃x�N�g��
			Vector3 toBallDirection = m_ball->GetPosition() - m_position;
			//y������0�ɂ���
			toBallDirection.y = 0.0f;
			//���K��
			toBallDirection.Normalize();

			//�G�t�F�N�g�̌��������߂邽�߂̃N�H�[�^�j�I��
			Quaternion shieldHitRot = Quaternion::Identity;

			//���g����{�[���ւ̃x�N�g����x,z��������p�x���o��
			shieldHitAngle = atan2f(toBallDirection.x, toBallDirection.z);

			shieldHitRot.SetRotation(Vector3::AxisY, shieldHitAngle);

			//���g�ƃ{�[���̊ԂɃG�t�F�N�g�𔭐�������
			shieldHitPos.Lerp(0.5f, m_position, m_ball->GetPosition());
			//�v���C���[��y���W������Ə�ɔ���
			shieldHitPos.y += 80.0f;

			m_shieldHitEffect.Play();
			m_shieldHitEffect.SetPosition(shieldHitPos);
			m_shieldHitEffect.SetRotation(shieldHitRot);
			m_shieldHitEffect.SetScale(GUARDEFFECT_HIT_SCALE);
			m_shieldHitEffect.Update();
		}
	}

}

void Player::ReSpawn() {
	/// @brief �X�^�[�g�ʒu�Ƀ��X�|�[��������
	m_position = m_startPos;
	m_charaCon.SetPosition(m_position);
	
	
	m_dieFlag = true;
	

}

void Player::Muteki()
{
	m_mutekiTime++;
	/// @brief ���X�|�[�����ɏ����̊ԃ{�[���ɓ�����Ȃ��Ȃ�
	if (m_mutekiTime == MUTEKI_TIME) {
		m_dieFlag = false;
		m_mutekiTime = TIME_ZERO;
	}
}

void Player::Animation()
{
	switch (m_anim)
	{
	case enAnimation_Idle: {
		m_skinModelRender->PlayAnimation(enAnimation_Idle, 0.2f);
	}break;
	case enAnimation_Walk: {
		m_skinModelRender->PlayAnimation(enAnimation_Walk, 0.2f);
	}break;
	default:
		break;
	}
}

void Player::Update()
{

	/// @brief �X�e�B�b�N���͂��󂯎��
	m_Lstickx = g_pad[m_myNumber]->GetLStickXF();
	m_Lsticky = g_pad[m_myNumber]->GetLStickYF();

	/// @brief �_���[�W���̓X�e�B�b�N���͂��󂯕t���Ȃ�
	if (m_damage == true) {
		m_Lstickx = FLOAT_0;
		m_Lsticky = FLOAT_0;
		m_damageTime += FLOAT_1;
	}
	if (m_damageTime > DAMAGE_RETURN_TIME) {
		m_damageTime = FLOAT_1;
		m_damage = false;
	}
	if (m_breakGuard == true)
	{
		m_Lstickx = FLOAT_0;
		m_Lsticky = FLOAT_0;
		m_damageTime += FLOAT_1;
	}

	BallDistanceCalculation();
	Move();
	Rotation();
	IsKick();
	
	m_kickFlag = true;
	/// @brief �L�b�N�N�[���^�C��
	if (m_kickCooling == true)
	{
		m_kickCooler += 1;
		if (m_kickCooler == KICK_COOLTIME) {
			m_kickCooling = false;
			m_kickCooler = 0;
		}
	}

	/// @brief �L�b�N�̕s�𕪊�
	if (m_damage == true || m_guard == true || m_breakGuard == true || m_kickCooling == true)
	{
		//�L�b�N�s��
		m_readyKick = false;
	}
	else {
		//�L�b�N��
		m_readyKick = true;
	}

	if (m_kickFlag == true && m_readyKick == true) {
		if (g_pad[m_myNumber]->IsTrigger(enButtonA)) {

			//�L�b�N�G�t�F�N�g�Đ�����//
			
			//�G�t�F�N�g�����ʒu�����߂邽�߂̃x�N�g��
			Vector3 efcPos = Vector3::Zero;
			
			//�v���C���[���W�ƃ{�[�����W����`�⊮���A�����ʒu������
			//��ԗ���0�ɋ߂���΃v���C���[���A1�ɋ߂���΃{�[�����ɔ�������
			efcPos.Lerp(KICKEFFECT_POSITION_RATE, m_position, m_ball->GetPosition());

			m_kickEffect.Play();
			m_kickEffect.SetPosition(efcPos);
			m_kickEffect.SetRotation(m_qRot);
			m_kickEffect.SetScale(KICKEFFECT_SCALE);
			//�L�b�N�������̍��W��ێ��������̂ł����ōX�V
			m_kickEffect.Update();

			KickBall();
		}
	}

	if (g_pad[m_myNumber]->IsTrigger(enButtonA)) {
		m_kickCooling = true;
	}
	/// @brief ��K�[�h���A�K�[�h�ϋv�l����
	if (m_guard == false) {
		m_guardDurability += 0.555f;
	}
	/// @brief �ēW�J�\�܂�
	if (m_guardDurability >= 100.0f && m_breakGuard == true)
	{
		m_breakGuard = false;
		
	}
	/// @brief �K�[�h�ϋv�l��100����ɂȂ�Ȃ��悤�ɂ���z
	if (m_guardDurability >= 100.0f)
	{
		m_guardDurability = 100.0f;
	}
	
	/// @brief �{�[���Ƃ̋��������ȉ��Ő������
	if (m_breakGuard == true) {
		if (m_ballDistance < GUARD_DISTANCE && m_dieFlag == false) {
			BallCollide();
		}
	}
	else {
		if (m_ballDistance < COLLIDE_DISTANCE && m_dieFlag == false) {
			BallCollide();
		}
	}
	/// @brief LB1�������Ă���ԃK�[�h
	if (g_pad[m_myNumber]->IsPress(enButtonLB1) && m_breakGuard == false) {
		m_guard = true;
	}
	else {
		m_guard = false;
		m_guardEffectCouter = 0;
		m_shieldHitEffectCounter = 0;
	}

	/// @brief �K�[�h�\�Ȃ�K�[�h�̏���
	if (m_guard == true && m_breakGuard == false) {
		Guard();
		
		//�V�[���h�G�t�F�N�g��������//
		//�J�E���^�[�ɒl�����Z
		m_guardEffectCouter += 1;
		//�K��t���[�����ɃG�t�F�N�g�𔭐�
		if (m_guardEffectCouter % 20 == 1) {
			m_guardEffect.Play();
		}
	}

	//�K�[�h�u���C�N�G�t�F�N�g��������
	if (m_breakGuardPrevFrame == false) {
		if (m_breakGuard == true) {
			m_guardBreakEffect.Play();
			Vector3 breakPos = m_position;
			breakPos.y += 80.0f;

			m_guardBreakEffect.SetPosition(breakPos);
			m_guardBreakEffect.SetScale(GUARDEFFECT_BREAK_SCALE);
			m_guardBreakEffect.Update();
			
		}
	}
	//�V�[���h�񕜃G�t�F�N�g��������
	if (m_breakGuardPrevFrame == true) {
		if (m_breakGuard == false) {
			m_shieldRepairEffect.Play();
		}
	}


	//�K�[�h�J�n���̃G�t�F�N�g��������
	//�{�^�����������K�[�h�u���C�N���Ă��Ȃ��Ƃ��Ɏ��s
	if (g_pad[m_myNumber]->IsTrigger(enButtonLB1) && m_breakGuard == false) {
		m_guardBeginEffect.Play();
	}

	if (m_dieFlag == true) {
		Muteki();
	}

	/// @brief �����ɓ�����X�|�b�g���C�g�̈ʒu�ƕ�����ݒ�
	Vector3 pos = m_position;
	pos.y = SPOT_LIGHT_HEIGHT;
	m_lig->SetSpotLightPos(m_myNumber, pos);

	Vector3 dir = m_position - m_lig->GetSpotLightPos(m_myNumber);
	m_lig->SetSpotLightDirection(m_myNumber,dir);

	/// @brief �L�����N�^�[�R���g���[���[�ō��W�����߂�
	m_position = m_charaCon.Execute(m_moveSpeed, FLOAT_1);
	

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_qRot);


	//�K�[�h�G�t�F�N�g�̍X�V
	Vector3 efcGuardPos = m_position;
	//�v���C���[���W��肿����Ə�ɂ���
	efcGuardPos.y += GUARDEFFECT_POS_Y;
	m_guardEffect.SetPosition(efcGuardPos);
	m_guardEffect.SetScale(GUARDEFFECT_SCALE);
	m_guardEffect.Update();
	
	//�K�[�h�\���G�t�F�N�g�̍X�V
	m_guardBeginEffect.SetPosition(efcGuardPos);
	m_guardBeginEffect.SetScale(GUARDEFFECT_BEGIN_SCALE);
	m_guardBeginEffect.Update();
	
	//�V�[���h�񕜃G�t�F�N�g�̍X�V
	m_shieldRepairEffect.SetPosition(efcGuardPos);
	m_shieldRepairEffect.SetScale(GUARDEFFECT_REPAIR_SCALE);
	m_shieldRepairEffect.Update();	

	//���t���[���̃K�[�h�u���C�N��Ԃ��L�^
	m_breakGuardPrevFrame = m_breakGuard;

	/// @brief �A�j���[�V����
	Animation();

	if (g_pad[m_myNumber]->IsTrigger(enButtonStart)) {
		ReSpawn();
	}
}

void Player::BallDistanceCalculation()
{
	m_toBallVec = m_ball->GetPosition() - m_position;
	m_ballDistance = m_toBallVec.Length();
}