#pragma once
#include "SpriteRender.h"

class SpriteRender;

class SceneChange : public IGameObject
{
private:
	SpriteRender* m_transparencySprite = nullptr;
	float m_fadeRate = 0.0f;

public:
	SceneChange();
	~SceneChange();
	bool Start();
	void Update();

	/// @brief �V�[���̐؂�ւ����t�F�[�h�ōs��
	/// @param TorF true�ŉ�ʂ����邭�Ȃ� false�ŉ�ʂ��Â��Ȃ�
	void TransparencyChange(bool TorF);

	/// @brief ��ʂ����S�ɖ��邭�Ȃ������H
	/// @return true�Ŋ��� false�Ŗ�����
	bool TransparencyChangeStart() { return m_transparencySprite->IsTransparent(); }

	/// @brief ��ʂ����S�ɈÂ��Ȃ������H
	/// @return true�Ŋ��� false�Ŗ�����
	bool TransparencyChangeEnd() { return m_transparencySprite->IsOpacity(); }
};

