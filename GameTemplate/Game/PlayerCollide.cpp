#include "stdafx.h"
#include "PlayerCollide.h"

namespace {
	/// @brief �{�[���ɐڐG���锻��
	const float COLLIDE_RATE = 0.0f;
	/// @brief �{�[���ɐڐG���鋗��
	const float COLLIDE_DISTANCE = 80.0f;
	/// @brief �������ɐ�����Ԑ���
	const float BLOW_AWAY_RATE = 2.0f;
	/// @brief �c�����ɐ�����Ԑ���
	const float BLOW_AWAY_HEIGHT_RATE = 1.0f;
	/// @brief �A�C�e����������Ƃ��̐�����Ԑ���
	const float DECREASE_BLOW_AWAY_RATE = 1.0f;
	/// @brief �����悭�������������ɂȂ�{�[���̑��x
	const float STRONG_HIT = 20.0f;
	/// @brief �W���X�g�K�[�h�\�Ȏ���
	const float POSSIBLE_JUST_GUARD_TIME = 0.01f;
}

PlayerCollide::PlayerCollide()
{

}

PlayerCollide::~PlayerCollide()
{

}

bool PlayerCollide::Start()
{
	m_ball = FindGO<Ball>(BALL_NAME);
	m_score = FindGO<Score>(SCORE_NAME);
	m_se = FindGO<Se>(SE_NAME);
	return true;
}

void PlayerCollide::Update()
{
	//���������܂ŏ������s��Ȃ�
	if (m_setUp == false) {
		return;
	}

	//��Ԃɂ���ĕω�����p�����[�^�[������
	DetermineParameters();
	//�{�[���Ƃ̋������v�Z
	ToBallVectorCalculation();
	//�{�[���������Ă��鎞�Ƀ{�[���Ƃ̋������ڐG����܂ŋ߂Â�����c
	if (m_ball->IsMove() == true && m_ballDistance < COLLIDE_DISTANCE) {
		//�K�[�h���Ȃ�c
		if (m_plAction->IsGuard() == true) {
			//�K�[�h���̂Ԃ��鏈�����s��
			GuardCollide();
		}
		//�K�[�h���Ă��Ȃ��Ȃ�c
		else {
			//�{�[���ƂԂ��鏈�����s��
			BallCollide();
		}
	}
	//�{�[���������Ă��Ȃ��E�ڐG����ɂȂ�Ȃ�������c
	else {
		//�G��Ă��Ȃ���ԂɕύX
		m_guradHit = false;
	}
}

void PlayerCollide::SetPlayerNumber(const int plNum)
{
	//�����̃v���C���[�ԍ�������
	m_playerNum = plNum;
	//�����Ɠ����v���C���[�ԍ��̃f�[�^�����
	m_player = FindGO<Player>(PLAYER_NAME[m_playerNum]);
	m_plAction = FindGO<PlayerAction>(PLAYER_ACTION_NAME[m_playerNum]);
	m_plMove = FindGO<PlayerMove>(PLAYER_MOVE_NAME[m_playerNum]);
	m_plEffect = FindGO<PlayerEffect>(PLAYER_EFFECT_NAME[m_playerNum]);
	m_plReinforcement = FindGO<PlayerReinforcement>(PLAYER_REINFORCEMENT_NAME[m_playerNum]);
	//��������
	m_setUp = true;
}

void PlayerCollide::DetermineParameters()
{
	//�v���C���[���h�䋭����Ԃ�������c
	if (m_plReinforcement->IsDefenseUp() == true) {
		//������Ԑ�����h�䋭����Ԓ��̐����ɂ���
		m_blowAwayRate = DECREASE_BLOW_AWAY_RATE;
	}
	//�v���C���[���h�䋭����ԂłȂ��ꍇ�c
	else {
		//������Ԑ�����ʏ펞�̐����ɂ���
		m_blowAwayRate = BLOW_AWAY_RATE;
	}
}

void PlayerCollide::ToBallVectorCalculation()
{
	//�{�[���̍��W���玩���̍��W�������Ď�������{�[���Ɍ������ĐL�т�x�N�g�����v�Z����
	m_toBallVec = m_ball->GetPosition() - m_player->GetPosition();
	//�{�[���Ƃ̋����������Ōv�Z����
	BallDistanceCalculation();
	//�c����������
	m_toBallVec.y = 0.0f;
	//���K������
	m_toBallVec.Normalize();
}

void PlayerCollide::BallDistanceCalculation()
{
	//�{�[���Ɍ������ĐL�т�x�N�g�����璷�����擾����
	m_ballDistance = m_toBallVec.Length();
}

void PlayerCollide::BallCollide()
{
	//�{�[���ւ̃x�N�g���ƃ{�[���̌����œ�����p�x�����߂�
	float matchRate = Dot(m_ball->GetMoveDirection(), m_toBallVec);
	//�{�[���������Ă��Ȃ��E�ڐG����ɂȂ�Ȃ������ꍇ�c
	if (m_ball->IsMove() == false || matchRate > COLLIDE_RATE) {
		//�������I������
		return;
	}

	//�{�[���Ǝ����̈ʒu���琁����΂������������߂�
	Vector3 repulsiveForce = m_player->GetPosition() - m_ball->GetPosition();
	//�c�����̐���������
	repulsiveForce.y = 0.0f;
	//���K�����ĕ����x�N�g���ɂ���
	repulsiveForce.Normalize();
	//�{�[���̈ړ������𐁂���ԕ����Ƌt�����ɐݒ肷��
	m_ball->SetMoveDirection(repulsiveForce * -1.0f);

	//�v���C���[�����S���̖��G���Ԓ��̏ꍇ�c
	if (m_player->IsDie() == true) {
		//�_���[�W���󂯂Ȃ������Ƃ���SE��炷
		m_se->PlayNoDamageCollideSe();
		//�������I������
		return;
	}

	//������Ԑ�������Z���Ĉړ��ʂ����߂�
	repulsiveForce *= m_ball->GetVelocity() * m_blowAwayRate;

	//�c�����͕ʂɌv�Z����
	repulsiveForce.y = m_ball->GetVelocity() * BLOW_AWAY_HEIGHT_RATE;

	//�ړ����x�ɐ�����Ԑ�����ݒ肷��
	m_plMove->SetMoveSpeed(repulsiveForce * 2.0f);

	//�_���[�W�G�t�F�N�g���Đ�
	m_plEffect->PlayDamageEffect();

	//�K�[�h�u���C�N���̏ꍇ�c
	if (m_plAction->IsGuardBreak() == true) {
		//�s���s�\�G�t�F�N�g������
		m_plEffect->StopKnockOutEffect();
		//�s���s�\SE������
		m_se->StopStanSe(m_playerNum);
	}
	//�_���[�W���łȂ��ꍇ�c
	if (m_player->IsDamage() == false) {
		//�s���s�\�G�t�F�N�g���Đ�
		m_plEffect->PlayKnockOutEffect();
		//�s���s�\SE��炷
		m_se->PlayStanSe(m_playerNum);
	}

	//�v���C���[���_���[�W���ɐݒ肷��
	m_player->SetDamage();

	//�{�[���̑��x�������������������̂ɂȂ鑬�x�𒴂��Ă�����c
	if (m_ball->GetVelocity() > STRONG_HIT) {
		//������������SE��炷
		m_se->PlayStrongCollideSe();
	}
	//�{�[���̑��x�������������������̂ɂȂ鑬�x�𒴂��Ă��Ȃ�������c
	else {
		//�キ��������SE��炷
		m_se->PlayWeakCollideSe();
	}

	//�{�[���̔ԍ�����U�����Ă����v���C���[�̔ԍ����L������
	m_player->SetHaveAttackedPlayer(m_ball->GetPlayerInformation());

	//�U�����Ă����v���C���[�������ł͂Ȃ��ꍇ�c
	if (m_player->GetHaveAttackedPlayer() != m_playerNum) {
		//�U�����Ă����v���C���[�ɃX�R�A�����Z����
		m_score->AddScore200(m_player->GetHaveAttackedPlayer());
	}
}

void PlayerCollide::GuardCollide()
{
	//�K�[�h���ɐڐG���Ă��Ȃ��ꍇ�c
	if (m_guradHit == false) {
		//�K�[�h�q�b�g�G�t�F�N�g�̔���
		m_plEffect->PlayShieldHitEffect();
		//�K�[�h�q�b�gSE���Đ�
		m_se->PlayShieldHitSe();
		//�ڐG������ԂɕύX
		m_guradHit = true;
	}

	//�K�[�h���Ԃ��W���X�g�K�[�h���莞�ԓ��Ȃ�W���X�g�K�[�h����
	if (m_plAction->GetGuardTime() < POSSIBLE_JUST_GUARD_TIME) {
		//�{�[�������S�ɒ�~
		m_ball->SetVelocity(0.0f);

		//�W���X�g�K�[�h�G�t�F�N�g�̍Đ�
		m_plEffect->PlayJustGuardEffect();
		//SE��炷
		m_se->PlayJustGuardSe();
		//�v���C���[��������ԂɕύX
		m_plReinforcement->ChangeSelfPowerUp();
	}
	//�W���X�g�K�[�h����ɂȂ�Ȃ�������c
	else {
		//�{�[���̐����ɉ����ăK�[�h�ϋv�l�����炷
		float shieldDamage = m_ball->GetVelocity() * m_plAction->GetGuradDecreaseValue() * 10.0f;
		m_plAction->SetGuardDamage(shieldDamage);

		//�K�[�h�ϋv�͂�0��葽��������c
		if (m_plAction->GetGuardDurability() > 0.0f) {
			//�{�[���̐����ɉ����ăm�b�N�o�b�N����B
			Vector3 repulsiveForce = m_toBallVec * -1.0f;
			repulsiveForce.Normalize();
			repulsiveForce *= m_ball->GetVelocity();
			repulsiveForce.y = m_ball->GetVelocity() * 0.1f;
			m_plMove->SetMoveSpeed(repulsiveForce);

			//�{�[���͋t�����ɒ��˕Ԃ�
			m_ball->SetVelocity(m_ball->GetVelocity() / 2.0f);
			m_ball->SetMoveDirection(repulsiveForce * -1.0f);
		}
	}
}