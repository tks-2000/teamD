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

	/// @brief シーンの切り替えをフェードで行う
	/// @param TorF trueで画面が明るくなる falseで画面が暗くなる
	void TransparencyChange(bool TorF);

	/// @brief 画面が完全に明るくなったか？
	/// @return trueで完了 falseで未完了
	bool TransparencyChangeStart() { return m_transparencySprite->IsTransparent(); }

	/// @brief 画面が完全に暗くなったか？
	/// @return trueで完了 falseで未完了
	bool TransparencyChangeEnd() { return m_transparencySprite->IsOpacity(); }
};

