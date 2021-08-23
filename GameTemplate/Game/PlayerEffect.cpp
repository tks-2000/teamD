#include "stdafx.h"
#include "PlayerEffect.h"

namespace {
	/// @brief �G�t�F�N�g�p�萔
	//�L�b�N�G�t�F�N�g�̃t�@�C���p�X
	const char16_t* KICKEFFECT_FILEPATH = u"Assets/effect/kick.efk";
	//�L�b�N�G�t�F�N�g�����ʒu�����߂�l�B0�ɋ߂��قǃv���C���[���
	const float KICKEFFECT_POSITION_RATE = 0.9f;
	//�L�b�N�G�t�F�N�g�̊g�嗦
	const Vector3 KICKEFFECT_SCALE = { 20.0f,20.0f,20.0f };
	//�L�b�N�G�t�F�N�g�̔������x
	const float KICKEFFECT_POS_Y = 50.0f;

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
	//�s���s�\�G�t�F�N�g�̊g�嗦
	const Vector3 KNOCKOUTEFFECT_SCALE = { 15.0f,15.0f,15.0f };

	//�W���X�g�K�[�h�G�t�F�N�g�̃t�@�C���p�X
	const char16_t* JUSTGUARDEFFECT_FILEPATH = u"Assets/effect/justguard.efk";
	//�W���X�g�K�[�h�G�t�F�N�g�̊g�嗦
	const Vector3 JUSTGUARDEFFECT_SCALE = { 10.0f,10.0f,10.0f };

	//�����G�t�F�N�g�̃t�@�C���p�X
	const char16_t* KICKBUFFEFFECT_FILEPATH = u"Assets/effect/justguardBuff.efk";
	//�����G�t�F�N�g�̊g�嗦
	const Vector3 KICKBUFFEFFECT_SCALE = { 20.0f,20.0f,20.0f };
	//�����G�t�F�N�g��y���W�����ʒu�����߂邽�߂̒萔
	const float KICKBUFFEFFECT_POS_Y = 10.0f;

	//�_���[�W�񕜃G�t�F�N�g�̃t�@�C���p�X
	const char16_t* REPAIREFFECT_FILEPATH = u"Assets/effect/repair.efk";
	//�_���[�W�񕜃G�t�F�N�g�̊g�嗦
	const Vector3 REPAIREFFECT_SCALE = { 10.0f,10.0f,10.0f };
	
	//�_���[�W�G�t�F�N�g�̃t�@�C���p�X
	const char16_t* DAMAGEEFFECT_FILEPATH = u"Assets/effect/damage.efk";
	//�ŏ��̑傫��
	const Vector3 DAMAGEEFFECT_SCALE_MIN = { 5.0f,5.0f,5.0f };
	//�ő�̑傫��
	const Vector3 DAMAGEEFFECT_SCALE_MAX = { 30.0f,30.0f,30.0f };
	//�傫�����ő�ƂȂ�{�[���X�s�[�h�̏��
	const float DAMAGEEFFECT_BALLSPEED_MAX = 60.0f;
	//�傫�����ŏ��ƂȂ�{�[���X�s�[�h�̉���
	const float DAMAGEEFFECT_BALLSPEED_MIN = 0.0f;

	//���X�|�[�����̃G�t�F�N�g�̃t�@�C���p�X(�v���C���[��)
	const char16_t* RESPAWNEFFECT_FILEPATH[PLAYER_NUMBER] = { 
		{u"Assets/effect/respawn_red.efk"},
		{u"Assets/effect/respawn_blue.efk"},
		{u"Assets/effect/respawn_yellow.efk"},
		{u"Assets/effect/respawn_green.efk"}
	};
	const Vector3 RESPAWNEFFECT_SCALE = { 20.0f,20.0f,20.0f };
	const float RESPAWNEFFECT_POS_Y = 400.0f;

	//�o�[�X�g�G�t�F�N�g�̃t�@�C���p�X(�v���C���[��)
	const char16_t* BURSTEFFECT_FILEPATH[PLAYER_NUMBER] = {
		{u"Assets/effect/burst_red.efk"},
		{u"Assets/effect/burst_blue.efk"},
		{u"Assets/effect/burst_yellow.efk"},
		{u"Assets/effect/burst_green.efk"}
	};
	const Vector3 BURSTEFFECT_SCALE = { 8.0f,16.0f,8.0f };

	//�A�C�e���o�t�G�t�F�N�g�̃t�@�C���p�X
	const char16_t* ITEMBUFFEFFECT_FILEPATH[ITEM_NUMBER] = {
		{u"Assets/effect/itembuff_attackup.efk"},
		{u"Assets/effect/itembuff_guardup.efk"},
		{u"Assets/effect/itembuff_speedup.efk"}
	};
	const Vector3 ITEMBUFFEFFECT_SCALE = { 10.0f,10.0f,10.0f };
	const float ITEMBUFFEFFECT_POS_Y = 20.0f;

	//�_�b�V���G�t�F�N�g�̃t�@�C���p�X
	const char16_t* DASHEFFECT_FILEPATH = { u"Assets/effect/dash.efk" };
	//�_�b�V���G�t�F�N�g�̊g�嗦
	const Vector3 DASHEFFECT_SCALE = { 10.0f,10.0f,10.0f };
	//�_�b�V���G�t�F�N�g��Y���W
	const float DASHEFFECT_POS_Y = 50.0f;

}

PlayerEffect::PlayerEffect()
{
	/// @brief �v���C���[�̐l���𒲂ׂĂ��̐������G�t�F�N�g��p�ӂ���
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);


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
	//�s���s�\�G�t�F�N�g��������
	m_knockOutEffect.Init(KNOCKOUTEFFECT_FILEPATH);
	//�W���X�g�K�[�h�G�t�F�N�g��������
	m_justGuardEffect.Init(JUSTGUARDEFFECT_FILEPATH);
	//�����G�t�F�N�g��������
	m_kickBuffEffect.Init(KICKBUFFEFFECT_FILEPATH);
	//�_���[�W�񕜃G�t�F�N�g��������
	m_repairEffect.Init(REPAIREFFECT_FILEPATH);
	//�_���[�W�G�t�F�N�g��������
	m_damageEffect.Init(DAMAGEEFFECT_FILEPATH);
	//�o�t�G�t�F�N�g��������
	m_itemBuffEffect.Init(ITEMBUFFEFFECT_FILEPATH[0]);
	//�_�b�V���G�t�F�N�g��������
	m_dashEffect.Init(DASHEFFECT_FILEPATH);




}

PlayerEffect::~PlayerEffect()
{

}

bool PlayerEffect::Start()
{
	/// @brief �v���C���[�ƃ{�[���̏�����肷�� 
	m_ball = FindGO<Ball>(BALL_NAME);

	

	return true;
}

void PlayerEffect::SetPlayerNumber(const int plNum)
{
	m_playerNum = plNum;
	m_player = FindGO<Player>(PLAYER_NAME[plNum]);
	//�ȉ��A�v���C���[��(�F��������Ă���)�G�t�F�N�g�̏�����
	//���X�|�[�����̃G�t�F�N�g��������
	m_respawnEffect.Init(RESPAWNEFFECT_FILEPATH[plNum]);
	//�o�[�X�g�G�t�F�N�g��������
	m_burstEffect.Init(BURSTEFFECT_FILEPATH[plNum]);
}

void PlayerEffect::PlayKickEffect()
{
	/// @brief �v���C���[�ƃ{�[���̈ʒu����G�t�F�N�g�̍Đ��ʒu�Ɗp�x�����߂� 
	Vector3 toBallDir = m_player->GetToBallVec();
	//�v���C���[�̌����Ă���������擾
	Vector3 plDir = m_player->GetDirection();
	//�����ʒu�����߂邽�߂̃x�N�g��
	Vector3 efcPos = Vector3::Zero;
	//���������߂邽�߂̃N�H�[�^�j�I��
	Quaternion efcRot = Quaternion::Identity;
	//�v���C���[�̌����Ă����������G�t�F�N�g�̊p�x��ݒ肷��
	efcRot.SetRotation(Vector3::AxisY, atan2(plDir.x, plDir.z));
	//�G�t�F�N�g�����ʒu���{�[���Ǝ��g�̋����̊Ԃɐݒ肷��
	efcPos.Lerp(KICKEFFECT_POSITION_RATE, m_player->GetPosition(), m_ball->GetPosition());
	//�����ʒu��������ɂ��炷
	efcPos.y += KICKEFFECT_POS_Y;

	m_kickEffect.Play();
	m_kickEffect.SetPosition(efcPos);
	m_kickEffect.SetRotation(efcRot);
	m_kickEffect.SetScale(KICKEFFECT_SCALE);
	m_kickEffect.Update();
}

void PlayerEffect::PlayGuardEffect() {
	m_guardEffectCouter += 1;
	if (m_guardEffectCouter % 20 == 1) {
		m_guardEffect.Play();
	}
}

void PlayerEffect::PlayGuardBreakEffect()
{
	m_guardBreakEffect.Play();
	m_guardBreakEffect.SetPosition(m_efcGuardPos);
	m_guardBreakEffect.SetScale(GUARDEFFECT_BREAK_SCALE);
	m_guardBreakEffect.Update();
}

void PlayerEffect::PlayJustGuardEffect()
{
	Vector3 efcPos = m_player->GetPosition();
	efcPos.y += GUARDEFFECT_POS_Y;
	m_justGuardEffect.Play();
	m_justGuardEffect.SetPosition(efcPos);
	m_justGuardEffect.SetScale(JUSTGUARDEFFECT_SCALE);
	m_justGuardEffect.Update();
}

void PlayerEffect::PlayShieldHitEffect()
{
	/// @brief �v���C���[�ƃ{�[���̈ʒu����G�t�F�N�g�̍Đ��ʒu�Ɗp�x�����߂� 
	Vector3 toBallDir = m_player->GetToBallVec();
	Quaternion efcRot = Quaternion::Identity;
	efcRot.SetRotation(Vector3::AxisY, atan2(toBallDir.x, toBallDir.z));
	Vector3 efcPos = Vector3::Zero;
	efcPos.Lerp(0.5f, m_player->GetPosition(), m_ball->GetPosition());
	efcPos.y += GUARDEFFECT_POS_Y;

	m_shieldHitEffect.Play();
	m_shieldHitEffect.SetPosition(efcPos);
	m_shieldHitEffect.SetRotation(efcRot);
	m_shieldHitEffect.SetScale(GUARDEFFECT_HIT_SCALE);
	m_shieldHitEffect.Update();
}

void PlayerEffect::PlayDamageEffect()
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

	m_damageEffect.Play();
	m_damageEffect.SetPosition(m_efcGuardPos);
	m_damageEffect.SetScale(efcScale);
	m_damageEffect.Update();
}

void PlayerEffect::PlayBurstEffect()
{
	Vector3 efcPos = Vector3::Zero;
	efcPos = m_player->GetPosition();

	m_burstEffect.Play();
	m_burstEffect.SetPosition(efcPos);
	m_burstEffect.SetScale(BURSTEFFECT_SCALE);
	m_burstEffect.Update();
}

void PlayerEffect::PlayKickBuffEffect()
{
	m_powerUpCounter += 1;
	if (m_powerUpCounter % 20 == 0) {
		m_kickBuffEffect.Play();
	}
}

void PlayerEffect::PlayItemBuffEffect()
{
	m_itemPowerUpCounter += 1;
	if (m_itemPowerUpCounter % 25 == 0) {
		m_itemBuffEffect.Play();
	}
}

void PlayerEffect::PlayDashEffect()
{
	m_dashCounter += 1;
	if (m_dashCounter % 25 == 0) {
		m_dashEffect.Play();
	}
}

void PlayerEffect::GuardBeginEffectUpdate()
{
	m_guardBeginEffect.SetPosition(m_efcGuardPos);
	m_guardBeginEffect.SetScale(GUARDEFFECT_BEGIN_SCALE);
	m_guardBeginEffect.Update();
}

void PlayerEffect::GuardEffectUpdate()
{
	m_guardEffectPos = m_efcGuardPos;
	m_guardEffect.SetPosition(m_guardEffectPos);
	m_guardEffect.SetScale(GUARDEFFECT_SCALE);
	m_guardEffect.Update();
}

void PlayerEffect::ShieldRepairEffectUpdate()
{
	m_shieldRepairEffect.SetPosition(m_efcGuardPos);
	m_shieldRepairEffect.SetScale(GUARDEFFECT_REPAIR_SCALE);
	m_shieldRepairEffect.Update();
}

void PlayerEffect::KnockOutEffectUpdate()
{
	m_knockOutEffect.SetPosition(m_efcGuardPos);
	m_knockOutEffect.SetScale(KNOCKOUTEFFECT_SCALE);
	m_knockOutEffect.Update();
}

void PlayerEffect::KickBuffEffectUpdate()
{
	Vector3 efcPos = m_player->GetPosition();
	efcPos.y += KICKBUFFEFFECT_POS_Y;

	m_kickBuffEffect.SetPosition(efcPos);
	m_kickBuffEffect.SetScale(KICKBUFFEFFECT_SCALE);
	m_kickBuffEffect.Update();
}

void PlayerEffect::RepairEffectUpdate()
{
	m_repairEffect.SetPosition(m_efcGuardPos);
	m_repairEffect.SetScale(REPAIREFFECT_SCALE);
	m_repairEffect.Update();
}

void PlayerEffect::RespawnEffectUpdate()
{

	Vector3 efcPos = m_player->GetRespawnPoint();
	efcPos.y -= RESPAWNEFFECT_POS_Y;
	
	m_respawnEffect.SetPosition(efcPos);
	m_respawnEffect.SetScale(RESPAWNEFFECT_SCALE);
	m_respawnEffect.Update();
}

void PlayerEffect::ItemBuffEffectUpdate()
{
	Vector3 efcPos = m_player->GetPosition();
	efcPos.y += ITEMBUFFEFFECT_POS_Y;
	
	m_itemBuffEffect.SetPosition(efcPos);
	m_itemBuffEffect.SetScale(ITEMBUFFEFFECT_SCALE);
	m_itemBuffEffect.Update();
}

void PlayerEffect::DashEffectUpdate()
{
	//�v���C���[���W���擾
	Vector3 efcPos = m_player->GetPosition();
	//����������ɂ��炷
	efcPos.y += DASHEFFECT_POS_Y;
	//�v���C���[�̌������擾
	Vector3 efcDir = m_player->GetDirection();
	//�p�x�����߂邽�߂̃N�H�[�^�j�I����ݒ�
	Quaternion efcRot = Quaternion::Identity;
	//�擾�����v���C���[�̌�������p�x������
	efcRot.SetRotation(Vector3::AxisY,atan2(efcDir.x,efcDir.z) );

	m_dashEffect.SetPosition(efcPos);
	m_dashEffect.SetRotation(efcRot);
	m_dashEffect.SetScale(DASHEFFECT_SCALE);
	m_dashEffect.Update();
}


void PlayerEffect::ChangeItemBuffEffect(ItemBuffChange buffNum)
{
	switch (buffNum) {
		case enItemBuff_Kick: {
			m_itemBuffEffect.Init(ITEMBUFFEFFECT_FILEPATH[enItemBuff_Kick]);
		}break;
		case enItemBuff_Guard: {
			m_itemBuffEffect.Init(ITEMBUFFEFFECT_FILEPATH[enItemBuff_Guard]);
		}break;
		case enItemBuff_Speed: {
			m_itemBuffEffect.Init(ITEMBUFFEFFECT_FILEPATH[enItemBuff_Speed]);
		}break;
	}
}

void PlayerEffect::Update()
{
	/// @brief �X�V���K�v�ȃG�t�F�N�g�����ׂčX�V����
	//��Ƀv���C���[�ɒǐ����Ăق����A������傫�����ς���Ăق����Ȃǂ̃G�t�F�N�g�͂����ōX�V

	m_efcGuardPos = m_player->GetPosition();
	m_efcGuardPos.y += GUARDEFFECT_POS_Y;
	GuardBeginEffectUpdate();
	GuardEffectUpdate();
	ShieldRepairEffectUpdate();
	KnockOutEffectUpdate();
	KickBuffEffectUpdate();
	RepairEffectUpdate();
	RespawnEffectUpdate();
	ItemBuffEffectUpdate();
	DashEffectUpdate();

}