/*!
 * @brief	エフェクト
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
	//引数の値がtrueのとき
	//再生中のエフェクトを停止する。
	if (isStopAndPlay == true) {
		EffectEngine::GetInstance()->Stop(m_handle);
		//新しく再生。
		m_handle = EffectEngine::GetInstance()->Play(m_effect);
	}
	//引数の値がfalseのとき(デフォルトはこっち)
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
