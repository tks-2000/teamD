#include "stdafx.h"
#include "Player.h"

namespace {

	/// @brief �L�b�N�\�ȋ���
	const float KICK_POSSIBLE_DISTANCE = 200.0f;
	/// @brief �K�[�h�\�ȋ���
	const float GUARD_DISTANCE = 90.0f;
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
	/// @brief �W���X�g�K�[�h�\�Ȏ���
	const float POSSIBLE_JUST_GUARD_TIME = 0.01f;
	/// @brief �ʏ�̃L�b�N��
	const float NORMAL_KICK_POWER = 2.0f;
	/// @brief ������Ԃ̃L�b�N��
	const float POWERFUlL_KICK_POWER = 6.0f;
	/// @brief �X�^�~�i�̍ő�l
	const float MAX_STANIMA = 6.0f;
}

Player::Player()
{
	//�v���C���[�̏�����Ԃ�ݒ�
	m_moveVelocity = 0.9f;
	m_stamina = MAX_STANIMA;
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
	m_timer = FindGO<Timer>(TIMER_NAME);
	m_score = FindGO<Score>(SCORE_NAME);
	m_lig = FindGO<Lighting>(LIGHTING_NAME);
	m_plEffect = FindGO<PlayerEffect>(PLAYER_EFFECT_NAME);
	m_ball = FindGO<Ball>(BALL_NAME);

	m_animationClips[enAnimation_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimation_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimation_Run].Load("Assets/animData/unitychan/run.tka");

	m_animationClips[enAnimation_Idle].SetLoopFlag(true);
	m_animationClips[enAnimation_Walk].SetLoopFlag(true);
	m_animationClips[enAnimation_Run].SetLoopFlag(true);

	m_skinModelRender = NewGO<SkinModelRender>(PRIORITY);

	m_skinModelRender->InitA(UNITYCHAN_MODEL, "Assets/modelData/unityChan.tks", m_animationClips, enAnimation_Num);
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
	m_moveSpeed += g_camera3D->GetRight() * m_Lstickx;
	m_moveSpeed += g_camera3D->GetForward() * m_Lsticky;


	if (IsDash() == true) {
		m_moveVelocity = 0.95f;

		m_stamina -= g_gameTime->GetFrameDeltaTime() * FLOAT_2;

		m_anim = enAnimation_Run;
	}
	else {
		m_moveVelocity = 0.9f;
		m_stamina += g_gameTime->GetFrameDeltaTime() * FLOAT_1;
		if (m_stamina > MAX_STANIMA) {
			m_stamina = MAX_STANIMA;
		}
		m_anim = enAnimation_Walk;
	}

	m_moveSpeed *= m_moveVelocity;

	/// @brief �d�͂�������
	if (m_damage == true) {
		m_moveSpeed.y -= m_gravity / 2.0f;
	}
	else {
		m_moveSpeed.y -= m_gravity;
	}

	/// @brief �_���[�W�����ǂ����Ŗ��C�͂�ς���
	if (m_damage == false) {
		m_friction = NORMAL_FRICTION;
	}
	else {
		m_friction = DAMAGE_FRICYION;
	}
	/// @brief �ړ����x�ɖ��C�͂�������
	m_moveSpeed -= m_moveSpeed * m_friction;

	if (m_damage == false && m_guard == false && m_breakGuard == false && m_moveSpeed.x != FLOAT_0 || m_moveSpeed.z != FLOAT_0) {
		m_direction = m_moveSpeed;
		m_direction.y = FLOAT_0;
		m_direction.Normalize();
	}

	Vector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = FLOAT_0;
	/// @brief �ړ����x�����ȉ��Ŏ~�܂�
	if (moveSpeedXZ.LengthSq() < 0.1f) {
		m_moveSpeed.x = FLOAT_0;
		m_moveSpeed.z = FLOAT_0;
	}

	/// @brief �v���C���[�����������烊�X�|�[������
	if (m_position.y < FALLING_HEIGHT) {

		if (m_haveAttackedPlayer != m_myNumber) {
			m_score->AddScore(m_haveAttackedPlayer);
		}
		m_score->DebuctionScore(m_myNumber);

		ReSpawn();
	}


}

void Player::Rotation()
{
	/// @brief �_���[�W���A�K�[�h���A�����Ă��Ȃ��Ƃ��͉�]���Ȃ�
	if (m_damage == true || m_guard == true || m_breakGuard == true || m_moveSpeed.x == FLOAT_0 && m_moveSpeed.z == FLOAT_0) {
		m_anim = enAnimation_Idle;
		return;
	}
	m_qRot.SetRotation(Vector3::AxisY, atan2(m_direction.x, m_direction.z));

}

void Player::IsKick()
{
	/// @brief �{�[���Ƃ̋��������ȉ��̎��̂ݔ���
	if (m_ballDistance < KICK_POSSIBLE_DISTANCE) {
		/// @brief �v���C���[�̌����ƃ{�[���ւ̃x�N�g���̓��ςŏR���p�x�𐧌�
		float matchRate = Dot(m_direction, m_toBallVec);
		if (matchRate > 0.0f) {
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

bool Player::IsDash()
{
	if (m_dash == true && m_guard == false && g_pad[m_myNumber]->IsPress(enButtonRB1)) {
		if (m_Lstickx != FLOAT_0 || m_Lsticky != FLOAT_0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void Player::BallCollide()
{
	/// @brief �{�[���ւ̃x�N�g���ƃ{�[���̌����œ�����p�x�����߂�
	float matchRate = Dot(m_ball->GetMoveDirection(), m_toBallVec);
	if (m_ball->IsMove() == false || m_guard == true || matchRate > 0.0f) {
		return;
	}


	/// @brief �{�[���Ǝ����̈ʒu���琁����΂������������߂�
	Vector3 repulsiveForce = m_position - m_ball->GetPosition();
	repulsiveForce.y = FLOAT_0;
	repulsiveForce.Normalize();

	repulsiveForce *= m_ball->GetVelocity() * FLOAT_2;
	repulsiveForce.y = m_ball->GetVelocity() * 1.5f;
	m_moveSpeed = repulsiveForce * FLOAT_2;
	m_ball->SetMoveDirection(repulsiveForce * FLOAT_MINUS_1);


	if (m_breakGuard == true) {
		m_plEffect->StopKnockOutEffect(m_myNumber);
	}
	if (m_damage == false) {
		m_plEffect->PlayKnockOutEffect(m_myNumber);
	}

	m_damage = true;

	/// @brief �U�����Ă����v���C���[�̔ԍ����L������
	m_haveAttackedPlayer = m_ball->GetPlayerInformation();

	if (m_haveAttackedPlayer != m_myNumber && m_dieFlag == false) {
		m_score->AddScore(m_haveAttackedPlayer);
	}
}

void Player::Guard()
{
	/// @brief �K�[�h���͈ړ����x��������
	m_moveSpeed.x /= FLOAT_2;
	m_moveSpeed.z /= FLOAT_2;

	/// @brief �K�[�h���͑ϋv�l(guardDurability)�����葱����
	m_guardDurability -= 0.555f;

	//�V�[���h�G�t�F�N�g��������//
		//�J�E���^�[�ɒl�����Z
	m_guardEffectCouter += 1;
	//�K��t���[�����ɃG�t�F�N�g�𔭐�
	if (m_guardEffectCouter % 20 == 1 &&
		m_breakGuard == false &&
		m_damage == false) {
		m_plEffect->PlayGuardEffect(m_myNumber);
	}

	/// @brief �W���X�g�K�[�h���莞�Ԃ�i�߂�
	m_justGuardTime += g_gameTime->GetFrameDeltaTime() * FLOAT_01;

	/// @brief �K�[�h�ϋv�l�������Ȃ�����
	if (m_guardDurability <= 0.0f) {
		/// @brief �K�[�h�u���C�N����
		m_guardDurability = 0.0f;
		m_breakGuard = true;
		m_plEffect->StopGuardEffect(m_myNumber);
		m_plEffect->PlayGuardBreakEffect(m_myNumber);
		m_plEffect->PlayKnockOutEffect(m_myNumber);
	}

	/// @brief �{�[���������Ă��Ȃ���΃K�[�h������s��Ȃ�
	if (m_ball->IsMove() == false) {
		return;
	}

	/// @brief �ڐG������
	if (m_ballDistance < GUARD_DISTANCE) {
		/// @brief ��x���ڐG���Ă��Ȃ��ꍇ
		if (m_shieldHit == false) {

			//�K�[�h�q�b�g�G�t�F�N�g�̔���
			m_plEffect->PlayShieldHitEffect(m_myNumber);
			m_shieldHit = true;

		}
		/// @brief �W���X�g�K�[�h���莞�ԓ��Ȃ�W���X�g�K�[�h����
		if (m_justGuardTime < POSSIBLE_JUST_GUARD_TIME) {
			m_ball->SetVelocity(FLOAT_0);

			/// @brief �W���X�g�K�[�h�G�t�F�N�g�̍Đ�
			m_plEffect->PlayJustGuardEffect(m_myNumber);
			m_kickPowerUp = true;
		}
		else {
			/// @brief �{�[���̐����ɉ����đϋv�l�����炷
			float shieldDamage = m_ball->GetVelocity() * 4.0f;
			m_guardDurability -= shieldDamage;
			/// @brief �K�[�h�u���C�N�����ꍇ
			if (m_guardDurability <= 0.0f)
			{
				/// @brief �K�[�h�G�t�F�N�g�������ăK�[�h�u���C�N�G�t�F�N�g���Đ�����
				m_plEffect->StopGuardEffect(m_myNumber);
				m_plEffect->PlayGuardBreakEffect(m_myNumber);
				m_plEffect->PlayKnockOutEffect(m_myNumber);
				m_guardDurability = 0.0f;
				m_breakGuard = true;
				return;
			}

			/// @brief �{�[���̐����ɉ����ăm�b�N�o�b�N����B
			Vector3 repulsiveForce = m_toBallVec * FLOAT_MINUS_1;
			repulsiveForce.Normalize();
			repulsiveForce *= m_ball->GetVelocity();
			repulsiveForce.y = m_ball->GetVelocity() * FLOAT_01;
			m_moveSpeed += repulsiveForce;
			m_ball->SetVelocity(m_ball->GetVelocity() / FLOAT_2);
			m_ball->SetMoveDirection(repulsiveForce * FLOAT_MINUS_1);
		}

	}
	else {
		/// @brief �ڐG���Ă��Ȃ�
		m_shieldHit = false;
	}
}

void Player::ReSpawn() {
	/// @brief �X�^�[�g�ʒu�Ƀ��X�|�[��������
	m_position = m_startPos;
	m_charaCon.SetPosition(m_position);
	m_damage = false;
	m_damageTime = FLOAT_0;
	m_breakGuard = false;
	m_guardDurability = 100.0f;
	m_plEffect->StopKnockOutEffect(m_myNumber);

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
	case enAnimation_Run: {
		m_skinModelRender->PlayAnimation(enAnimation_Run, 0.2f);
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

	if (m_timer->IsTimerExecution() == false) {
		m_Lstickx = FLOAT_0;
		m_Lsticky = FLOAT_0;
	}

	/// @brief �_���[�W���̓X�e�B�b�N���͂��󂯕t���Ȃ�
	if (m_damage == true) {
		m_Lstickx = FLOAT_0;
		m_Lsticky = FLOAT_0;
		m_damageTime += FLOAT_1;
	}
	if (m_damageTime > DAMAGE_RETURN_TIME) {
		m_damageTime = FLOAT_0;
		if (m_breakGuard == false) {
			m_plEffect->StopKnockOutEffect(m_myNumber);
		}
		if (m_breakGuard != true) {
			m_plEffect->PlayRepairEffect(m_myNumber);
		}
		m_damage = false;
	}

	if (m_breakGuard == true)
	{
		m_Lstickx = FLOAT_0;
		m_Lsticky = FLOAT_0;
	}

	if (m_stamina < FLOAT_0) {
		m_dash = false;
	}

	if (m_dash == false && m_stamina >= MAX_STANIMA) {
		m_dash = true;
	}

	BallDistanceCalculation();
	Move();
	Rotation();
	IsKick();

	/// @brief �L�b�N�N�[���^�C��
	if (m_kickCooling == true)
	{
		m_kickCooler += 1;
		if (m_kickCooler == KICK_COOLTIME) {
			m_kickCooling = false;
			m_kickCooler = 0;
		}
	}

	if (m_kickPowerUp == true) {
		m_kickPower = POWERFUlL_KICK_POWER;
		m_powerUpTime += g_gameTime->GetFrameDeltaTime() * FLOAT_1;
	}
	else
	{
		m_powerUpTime = FLOAT_0;
		m_kickPower = NORMAL_KICK_POWER;
	}
	if (m_powerUpTime > FLOAT_2) {
		m_kickPowerUp = false;
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

	if (m_kickFlag == true && m_readyKick == true && m_timer->IsTimerExecution() == true) {
		if (g_pad[m_myNumber]->IsTrigger(enButtonA)) {


			m_plEffect->PlayKickEffect(m_myNumber);


		}
	}

	if (g_pad[m_myNumber]->IsTrigger(enButtonA)) {
		m_kickCooling = true;
	}
	/// @brief ��K�[�h���A�K�[�h�ϋv�l����
	if (m_guard == false) {
		m_guardDurability += 0.555f;
		m_justGuardTime = 0.0f;
	}
	/// @brief �ēW�J�\�܂�
	if (m_guardDurability >= 100.0f && m_breakGuard == true)
	{
		m_breakGuard = false;
		if (m_damage == false) {
			m_plEffect->StopKnockOutEffect(m_myNumber);
		}
		m_plEffect->PlayShieldRepairEffect(m_myNumber);

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
	if (g_pad[m_myNumber]->IsPress(enButtonLB1) && m_breakGuard == false && m_damage == false) {
		m_guard = true;
	}
	else {
		m_guard = false;
		m_guardEffectCouter = 0;
	}

	/// @brief �K�[�h�\�Ȃ�K�[�h�̏���
	if (m_guard == true && m_breakGuard == false && m_timer->IsTimerExecution() == true) {


		Guard();
	}

	//�{�^�����������K�[�h�u���C�N���Ă��Ȃ��Ƃ��Ɏ��s
	if (g_pad[m_myNumber]->IsTrigger(enButtonLB1) &&
		m_breakGuard == false &&
		m_damage == false &&
		m_timer->IsTimerExecution() == true) {
		//m_guardBeginEffect.Play();
		m_plEffect->PlayGuardBeginEffect(m_myNumber);
	}

	if (m_dieFlag == true) {
		Muteki();
	}

	//�p���[�A�b�v�G�t�F�N�g�̍Đ�
	if (m_kickPowerUp == true) {
		m_powerUpCounter += 1;
		if (m_powerUpCounter % 25 == 1) {
			m_plEffect->PlayKickBuffEffect(m_myNumber);
		}
	}
	else {
		m_powerUpCounter = 0.0f;
	}


	/// @brief �����ɓ�����X�|�b�g���C�g�̈ʒu�ƕ�����ݒ�
	Vector3 pos = m_position;
	pos.y = SPOT_LIGHT_HEIGHT;
	m_lig->SetSpotLightPos(m_myNumber, pos);

	Vector3 dir = m_position - m_lig->GetSpotLightPos(m_myNumber);
	m_lig->SetSpotLightDirection(m_myNumber, dir);

	/// @brief �L�����N�^�[�R���g���[���[�ō��W�����߂�
	m_position = m_charaCon.Execute(m_moveSpeed, FLOAT_1);

	/// @brief ���f���ɍ��W�Ɖ�]��`����
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_qRot);

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
	m_toBallVec.y = FLOAT_0;
	m_toBallVec.Normalize();
}