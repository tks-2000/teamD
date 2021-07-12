#pragma once

class FontRender;
class GameDirector;
class Score;
class Effect;

const int SELECT_COMMAND_NUM = 3;

class Result : public IGameObject
{
private:
	int m_selectNum = 0;
	FontRender* m_arrowFont = nullptr;
	Vector2 m_arrowFontPos = Vector2::Zero;
	FontRender* m_selectFont[SELECT_COMMAND_NUM] = { nullptr };
	FontRender* m_rankingFont[PLAYER_NUMBER] = { nullptr };
	FontRender* m_playerNameFont[PLAYER_NUMBER] = { nullptr };
	bool m_playerFontSet[PLAYER_NUMBER] = { false };
	bool m_moveFlag[PLAYER_NUMBER] = { false };
	bool m_moveEndFlag = false;
	Vector2 m_plFontPos[PLAYER_NUMBER] = { Vector2::Zero,Vector2::Zero ,Vector2::Zero ,Vector2::Zero };
	Vector2 m_movePos[PLAYER_NUMBER] = { Vector2::Zero,Vector2::Zero ,Vector2::Zero ,Vector2::Zero };
	GameDirector* m_gameDirector = nullptr;
	Score* m_score = nullptr;
	int m_moveOrder[PLAYER_NUMBER] = { 0 };
	int m_decrease = 0;

	//紙吹雪エフェクト(吹きあがるタイプ)
	Effect m_kamifubukiEffect[2];
	Quaternion m_kamifubukiEffectRotation[2] = { Quaternion::Identity };
	bool m_kamifubukiEffectPlayFlag = false;
	//紙吹雪エフェクト(落ちるタイプ)
	Effect m_kamifubukiFallEffect;

	void PlayerFontMove(int num);

	void SelectCommandNewGO();
public:
	Result();
	~Result();
	bool Start();
	void Update();
	bool IsMoveEnd() { return m_moveEndFlag; }

	int GetSelectCommand() { return m_selectNum; }
};

