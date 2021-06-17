/*!
 * @brief	�G�t�F�N�g
 */

#include "stdafx.h"
#include "Effect.h"



Effect::Effect()
{
}
Effect::~Effect()
{
	
}

		
void Effect::Init(const char16_t* filePath)
{
	m_effect = EffectEngine::GetInstance()->LoadEffect(filePath);
	
}
void Effect::Play(const bool& isStopAndPlay)
{
	//�����̒l��true�̂Ƃ�
	//�Đ����̃G�t�F�N�g���~����B
	if (isStopAndPlay == true) {
		EffectEngine::GetInstance()->Stop(m_handle);
		//�V�����Đ��B
		m_handle = EffectEngine::GetInstance()->Play(m_effect);
	}
	//�����̒l��false�̂Ƃ�(�f�t�H���g�͂�����)
	else {
		m_handle = EffectEngine::GetInstance()->Play(m_effect);
	}

}
void Effect::Update()
{
	EffectEngine::GetInstance()->UpdateEffectWorldMatrix(
		m_handle,
		m_position,
		m_rotation,
		m_scale
	);
}
