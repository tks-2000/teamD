#include "stdafx.h"
#include "PlayerEffect.h"

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

	//�K�[�h�q�b�g�G�t�F�N�g�̃t�@�C���p�X
	const char16_t* GUARDEFFECT_HIT_FILEPATH = u"Assets/effect/shieldhit.efk";
	//�K�[�h�q�b�g�G�t�F�N�g�̊g�嗦
	const Vector3 GUARDEFFECT_HIT_SCALE = { 17.0f,17.0f,17.0f };
	//�K�[�h�q�b�g�G�t�F�N�g�����̋���
	const float GUARDEFFECT_HIT_DISTANCE = 150.0f;

	//�s���s�\�G�t�F�N�g�̃t�@�C���p�X
	const char16_t* KNOCKOUTEFFECT_FILEPATH = u"Assets/effect/knockout.efk";
	//�s���s�\�G�t�F�N�g�̃X�P�[��
	const Vector3 KNOCKOUTEFFECT_SCALE = { 15.0f,15.0f,15.0f };

	//�W���X�g�K�[�h�G�t�F�N�g�̃t�@�C���p�X
	const char16_t* JUSTGUARDEFFECT_FILEPATH = u"Assets/effect/justguard.efk";
	//�W���X�g�K�[�h�G�t�F�N�g�̃X�P�[��
	const Vector3 JUSTGUARDEFFECT_SCALE = { 10.0f,10.0f,10.0f };

	//�����G�t�F�N�g�̃t�@�C���p�X
	const char16_t* KICKBUFFEFFECT_FILEPATH = u"Assets/effect/kickbuff.efk";
	//�����G�t�F�N�g�̃X�P�[��
	const Vector3 KICKBUFFEFFECT_SCALE = { 20.0f,20.0f,20.0f };
	//�����G�t�F�N�g��y���W�����ʒu�����߂邽�߂̒萔
	const float KICKBUFFEFFECT_POS_Y = 10.0f;

	//�_���[�W�񕜃G�t�F�N�g�̃t�@�C���p�X
	const char16_t* REPAIREFFECT_FILEPATH = u"Assets/effect/repair.efk";
	//�_���[�W�񕜃G�t�F�N�g�̃X�P�[��
	const Vector3 REPAIREFFECT_SCALE = { 10.0f,10.0f,10.0f };
	
	//�_���[�W�G�t�F�N�g
	const char16_t* DAMAGEEFFECT_FILEPATH = u"Assets/effect/damage.efk";
	const Vector3 DAMAGEEFFECT_SCALE_MIN = { 5.0f,5.0f,5.0f };
	const Vector3 DAMAGEEFFECT_SCALE_MAX = { 30.0f,30.0f,30.0f };
	const float DAMAGEEFFECT_BALLSPEED_MAX = 60.0f;
	const float DAMAGEEFFECT_BALLSPEED_MIN = 0.0f;

	
	


	//���X�|�[�����̃G�t�F�N�g�̃t�@�C���p�X(�v���C���[��)
	const char16_t* RESPAWNEFFECT_FILEPATH[PLAYER_NUMBER] = { 
		{u"Assets/effect/respawn_red.efk"},
		{u"Assets/effect/respawn_blue.efk"},
		{u"Assets/effect/respawn_yellow.efk"},
		{u"Assets/effect/respawn_green.efk"}
	};
	const Vector3 RESPAWNEFFECT_SCALE = { 20.0f,20.0f,20.0f };
	const float RESPAWNEFFECT_OFFSET_Y = 400.0f;

	//�o�[�X�g�G�t�F�N�g�̃t�@�C���p�X(�v���C���[��)
	const char16_t* BURSTEFFECT_FILEPATH[PLAYER_NUMBER] = {
		{u"Assets/effect/burst_red.efk"},
		{u"Assets/effect/burst_blue.efk"},
		{u"Assets/effect/burst_yellow.efk"},
		{u"Assets/effect/burst_green.efk"}
	};
	const Vector3 BURSTEFFECT_SCALE = { 5.0f,5.0f,5.0f };

}

PlayerEffect::PlayerEffect()
{
	/// @brief �v���C���[�̐l���𒲂ׂĂ��̐������G�t�F�N�g��p�ӂ���
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);

	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		//�L�b�N���̃G�t�F�N�g��������
		m_kickEffect[plNum].Init(KICKEFFECT_FILEPATH);
		//�K�[�h���̃G�t�F�N�g��������
		m_guardEffect[plNum].Init(GUARDEFFECT_FILEPATH);
		//�K�[�h�\���G�t�F�N�g��������
		m_guardBeginEffect[plNum].Init(GUARDEFFECT_BEGIN_FILEPATH);
		//�K�[�h�j��̃G�t�F�N�g��������
		m_guardBreakEffect[plNum].Init(GUARDEFFECT_BREAK_FILEPATH);
		//�V�[���h�񕜂̃G�t�F�N�g��������
		m_shieldRepairEffect[plNum].Init(GUARDEFFECT_REPAIR_FILEPATH);
		//�K�[�h�q�b�g�G�t�F�N�g��������
		m_shieldHitEffect[plNum].Init(GUARDEFFECT_HIT_FILEPATH);
		//�s���s�\�G�t�F�N�g��������
		m_knockOutEffect[plNum].Init(KNOCKOUTEFFECT_FILEPATH);
		//�W���X�g�K�[�h�G�t�F�N�g��������
		m_justGuardEffect[plNum].Init(JUSTGUARDEFFECT_FILEPATH);
		//�����G�t�F�N�g��������
		m_kickBuffEffect[plNum].Init(KICKBUFFEFFECT_FILEPATH);
		//�_���[�W�񕜃G�t�F�N�g��������
		m_repairEffect[plNum].Init(REPAIREFFECT_FILEPATH);
		//�_���[�W�G�t�F�N�g��������
		m_damageEffect[plNum].Init(DAMAGEEFFECT_FILEPATH);

		//�v���C���[�ʃG�t�F�N�g�̏�����
		//���X�|�[�����̃G�t�F�N�g��������
		m_respawnEffect[plNum].Init(RESPAWNEFFECT_FILEPATH[plNum]);
		//�o�[�X�g�G�t�F�N�g��������
		m_burstEffect[plNum].Init(BURSTEFFECT_FILEPATH[plNum]);

	}
}

PlayerEffect::~PlayerEffect()
{

}

bool PlayerEffect::Start()
{
	/// @brief �v���C���[�ƃ{�[���̏�����肷�� 
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_player[plNum] = FindGO<Player>(PLAYER_NAME[plNum]);
	}
	m_ball = FindGO<Ball>(BALL_NAME);

	return true;
}

void PlayerEffect::PlayKickEffect(int plNum)
{
	/// @brief �v���C���[�ƃ{�[���̈ʒu����G�t�F�N�g�̍Đ��ʒu�Ɗp�x�����߂� 
	Vector3 toBallDir = m_player[plNum]->GetToBallVec();
	Quaternion efcRot = Quaternion::Identity;
	efcRot.SetRotation(Vector3::AxisY, atan2(toBallDir.x, toBallDir.z));
	Vector3 efcPos = Vector3::Zero;
	efcPos.Lerp(KICKEFFECT_POSITION_RATE, m_player[plNum]->GetPosition(), m_ball->GetPosition());

	m_kickEffect[plNum].Play();
	m_kickEffect[plNum].SetPosition(efcPos);
	m_kickEffect[plNum].SetRotation(efcRot);
	m_kickEffect[plNum].SetScale(KICKEFFECT_SCALE);
	m_kickEffect[plNum].Update();
}

void PlayerEffect::PlayGuardBreakEffect(int plNum)
{
	m_guardBreakEffect[plNum].Play();
	m_guardBreakEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_guardBreakEffect[plNum].SetScale(GUARDEFFECT_BREAK_SCALE);
	m_guardBreakEffect[plNum].Update();
}

void PlayerEffect::PlayJustGuardEffect(int plNum)
{
	Vector3 efcPos = m_player[plNum]->GetPosition();
	efcPos.y += GUARDEFFECT_POS_Y;
	m_justGuardEffect[plNum].Play();
	m_justGuardEffect[plNum].SetPosition(efcPos);
	m_justGuardEffect[plNum].SetScale(JUSTGUARDEFFECT_SCALE);
	m_justGuardEffect[plNum].Update();
}

void PlayerEffect::PlayShieldHitEffect(int plNum)
{
	/// @brief �v���C���[�ƃ{�[���̈ʒu����G�t�F�N�g�̍Đ��ʒu�Ɗp�x�����߂� 
	Vector3 toBallDir = m_player[plNum]->GetToBallVec();
	Quaternion efcRot = Quaternion::Identity;
	efcRot.SetRotation(Vector3::AxisY, atan2(toBallDir.x, toBallDir.z));
	Vector3 efcPos = Vector3::Zero;
	efcPos.Lerp(0.5f, m_player[plNum]->GetPosition(), m_ball->GetPosition());
	efcPos.y += GUARDEFFECT_POS_Y;

	m_shieldHitEffect[plNum].Play();
	m_shieldHitEffect[plNum].SetPosition(efcPos);
	m_shieldHitEffect[plNum].SetRotation(efcRot);
	m_shieldHitEffect[plNum].SetScale(GUARDEFFECT_HIT_SCALE);
	m_shieldHitEffect[plNum].Update();
}

void PlayerEffect::PlayDamageEffect(int plNum)
{
	Vector3 efcScale = Vector3::Zero;

	//�ő�l�ɑ΂��錻�݂̃X�s�[�h�̊������v�Z
	float speedRate = m_ball->GetVelocity() / DAMAGEEFFECT_BALLSPEED_MAX;

	//1.0�𒴂���Ƃ���1.0�ɂ���
	if (speedRate > 1.0f) {
		speedRate = 1.0f;
	}

	//����ꂽ��������g�嗦����`�⊮
	efcScale.Lerp(speedRate, DAMAGEEFFECT_SCALE_MIN, DAMAGEEFFECT_SCALE_MAX);

	m_damageEffect[plNum].Play();
	m_damageEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_damageEffect[plNum].SetScale(efcScale);
	m_damageEffect[plNum].Update();
}

void PlayerEffect::PlayBurstEffect(int plNum)
{
	Vector3 efcPos = Vector3::Zero;
	efcPos = m_player[plNum]->GetPosition();

	m_burstEffect[plNum].Play();
	m_burstEffect[plNum].SetPosition(efcPos);
	m_burstEffect[plNum].SetScale(BURSTEFFECT_SCALE);
	m_burstEffect[plNum].Update();
}

void PlayerEffect::GuardBeginEffectUpdate(int plNum)
{
	m_guardBeginEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_guardBeginEffect[plNum].SetScale(GUARDEFFECT_BEGIN_SCALE);
	m_guardBeginEffect[plNum].Update();
}

void PlayerEffect::GuardEffectUpdate(int plNum)
{
	m_guardEffectPos[plNum] = m_efcGuardPos[plNum];
	m_guardEffect[plNum].SetPosition(m_guardEffectPos[plNum]);
	m_guardEffect[plNum].SetScale(GUARDEFFECT_SCALE);
	m_guardEffect[plNum].Update();
}

void PlayerEffect::ShieldRepairEffectUpdate(int plNum)
{
	m_shieldRepairEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_shieldRepairEffect[plNum].SetScale(GUARDEFFECT_REPAIR_SCALE);
	m_shieldRepairEffect[plNum].Update();
}

void PlayerEffect::KnockOutEffectUpdate(int plNum)
{
	m_knockOutEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_knockOutEffect[plNum].SetScale(KNOCKOUTEFFECT_SCALE);
	m_knockOutEffect[plNum].Update();
}

void PlayerEffect::KickBuffEffectUpdate(int plNum)
{
	Vector3 efcPos = m_player[plNum]->GetPosition();
	efcPos.y += KICKBUFFEFFECT_POS_Y;

	m_kickBuffEffect[plNum].SetPosition(efcPos);
	m_kickBuffEffect[plNum].SetScale(KICKBUFFEFFECT_SCALE);
	m_kickBuffEffect[plNum].Update();
}

void PlayerEffect::RepairEffectUpdate(int plNum)
{
	m_repairEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_repairEffect[plNum].SetScale(REPAIREFFECT_SCALE);
	m_repairEffect[plNum].Update();
}

void PlayerEffect::RespawnEffectUpdate(int plNum)
{

	Vector3 efcPos = m_player[plNum]->GetRespawnPoint();
	efcPos.y -= RESPAWNEFFECT_OFFSET_Y;
	m_respawnEffect[plNum].SetPosition(efcPos);
	m_respawnEffect[plNum].SetScale(RESPAWNEFFECT_SCALE);
	m_respawnEffect[plNum].Update();
}

void PlayerEffect::Update()
{
	/// @brief �X�V���K�v�ȃG�t�F�N�g�����ׂčX�V����
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_efcGuardPos[plNum] = m_player[plNum]->GetPosition();
		m_efcGuardPos[plNum].y += GUARDEFFECT_POS_Y;
		GuardBeginEffectUpdate(plNum);
		GuardEffectUpdate(plNum);
		ShieldRepairEffectUpdate(plNum);
		KnockOutEffectUpdate(plNum);
		KickBuffEffectUpdate(plNum);
		RepairEffectUpdate(plNum);
		RespawnEffectUpdate(plNum);
	}
}