#include "stdafx.h"
#include "PlayerReinforcement.h"


namespace {
	/// @brief ���ȋ����̎���
	const float SELF_POWERUP_TIME = 10.0f;
	/// @brief �A�C�e���ɂ�鋭������
	const float ITEM_POWERUP_TIME = 10.0f;
}

PlayerReinforcement::PlayerReinforcement()
{
	//�������J�n����
	m_setUp = false;
	//���ȋ������Ă��Ȃ���ԂŊJ�n
	m_selfPowerUp = false;
	m_selfPowerUpCount = 0.0f;
	//�A�C�e���������Ă��Ȃ���ԂŊJ�n
	m_itemPowerUpState = enItemPowerUpNum;
	m_itemPowerUpCount = 0.0f;
}

PlayerReinforcement::~PlayerReinforcement()
{

}

bool PlayerReinforcement::Start()
{

	return true;
}

void PlayerReinforcement::Update()
{
	//�����������Ă��Ȃ�������c
	if (m_setUp == false) {
		//�������s��Ȃ�
		return;
	}

	//���ȋ����t���O�������Ă�����c
	if (m_selfPowerUp == true) {
		//���ȋ������̏������s��
		SelfPowerUp();
	}

	//�A�C�e�������t���O���ǂꂩ�����Ă�����c
	if (m_itemPowerUpState != enItemPowerUpNum) {
		//�A�C�e���������̏������s��
		ItemPowerUp();
	}
}

void PlayerReinforcement::SetPlayerNumber(const int num)
{
	//�v���C���[�̔ԍ���ݒ�
	m_playerNumber = num;
	//�ݒ肳�ꂽ�ԍ��̃f�[�^���擾
	m_plEffect = FindGO<PlayerEffect>(PLAYER_EFFECT_NAME[m_playerNumber]);
	//��������
	m_setUp = true;
}

bool PlayerReinforcement::IsKickUp() const
{
	//�L�b�N�������Ȃ�true
	if (m_itemPowerUpState == enKickUp) {
		return true;
	}
	//�����łȂ��Ȃ�false
	else {
		return false;
	}
}

bool PlayerReinforcement::IsDefenseUp() const
{
	//�h�䋭�����Ȃ�true
	if (m_itemPowerUpState == enDefenseUp) {
		return true;
	}
	//�����łȂ��Ȃ�false
	else {
		return false;
	}
}

bool PlayerReinforcement::IsSpeedUp() const
{
	//���x�������Ȃ�true
	if (m_itemPowerUpState == enSpeedUp) {
		return true;
	}
	//�����łȂ��Ȃ�false
	else {
		return false;
	}
}

void PlayerReinforcement::ChangeKickPowerUp()
{
	//�A�C�e��������Ԃ��L�b�N�͋����ɕύX
	m_itemPowerUpState = enKickUp; 
	//�A�C�e�������J�E���g��0�ɂ���
	m_itemPowerUpCount = 0.0f;
	//�A�C�e�������G�t�F�N�g���L�b�N�͋������̕��ɐݒ�
	m_plEffect->ChangeItemBuffEffect(enItemBuff_Kick);
}

void PlayerReinforcement::ChangeDefenseUp()
{
	//�A�C�e��������Ԃ�h��͋����ɕύX
	m_itemPowerUpState = enDefenseUp;
	//�A�C�e�������J�E���g��0�ɂ���
	m_itemPowerUpCount = 0.0f;
	//�A�C�e�������G�t�F�N�g��h��͋������̕��ɐݒ�
	m_plEffect->ChangeItemBuffEffect(enItemBuff_Guard);
}

void PlayerReinforcement::ChangeSpeedUp()
{
	//�A�C�e��������Ԃ𑬓x�����ɕύX
	m_itemPowerUpState = enSpeedUp;
	//�A�C�e�������J�E���g��0�ɂ���
	m_itemPowerUpCount = 0.0f;
	//�A�C�e�������G�t�F�N�g�𑬓x�������̕��ɐݒ�
	m_plEffect->ChangeItemBuffEffect(enItemBuff_Speed);
}

void PlayerReinforcement::ReinforcementRelease()
{
	//���ȋ�����Ԃ�����
	m_selfPowerUp = false;
	//�A�C�e��������Ԃ�����
	m_itemPowerUpState = enItemPowerUpNum;
}

void PlayerReinforcement::SelfPowerUp()
{
	//���ȋ������̃G�t�F�N�g���Đ�
	m_plEffect->PlayKickBuffEffect();
	//���ȋ����J�E���g��i�߂�
	m_selfPowerUpCount += g_gameTime->GetFrameDeltaTime();
	//���ȋ����J�E���g�����Ԃ𒴂�����c
	if (m_selfPowerUpCount > SELF_POWERUP_TIME) {
		//���ȋ����t���O�����ɖ߂�
		m_selfPowerUp = false;
		//���ȋ����J�E���g��0�ɂ���
		m_selfPowerUpCount = 0.0f;
	}
}

void PlayerReinforcement::ItemPowerUp()
{
	//�A�C�e���ɂ�鋭���G�t�F�N�g���Đ�
	m_plEffect->PlayItemBuffEffect();

	//�A�C�e�������J�E���g��i�߂�
	m_itemPowerUpCount += g_gameTime->GetFrameDeltaTime();

	//�A�C�e�������J�E���g�����Ԃ𒴂�����c
	if (m_itemPowerUpCount > ITEM_POWERUP_TIME) {
		//�A�C�e��������Ԃ���������
		m_itemPowerUpState = enItemPowerUpNum;
		//�A�C�e�������J�E���g��0�ɖ߂�
		m_itemPowerUpCount = 0.0f;
	}
}