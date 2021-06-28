#pragma once

class GameDirector;
class Player;
class Effect;

class PlayerEffect : public IGameObject
{
private:
	//エフェクト関連//
	/// @brief ボールをキックした時のエフェクト
	Effect m_kickEffect[PLAYER_NUMBER];
	/// @brief ガード時のエフェクト
	Effect m_guardEffect[PLAYER_NUMBER];
	Vector3 m_guardEffectPos[PLAYER_NUMBER] = { Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero };
	//ガードエフェクトを一定間隔で発生させるためのカウンター
	int m_guardEffectCouter = 0;
	/// @brief ガード発生の予兆エフェクト
	Effect m_guardBeginEffect[PLAYER_NUMBER];
	/// @brief ガードブレイクエフェクト
	Effect m_guardBreakEffect[PLAYER_NUMBER];
	/// @brief シールド回復エフェクト
	Effect m_shieldRepairEffect[PLAYER_NUMBER];
	/// @brief シールドヒットエフェクト
	Effect m_shieldHitEffect[PLAYER_NUMBER];
	/// @brief ガードヒットエフェクトを一定間隔で発生させるためのカウンター
	int m_shieldHitEffectCounter = 0;
	//行動不能時エフェクト(ピヨり)
	Effect m_knockOutEffect[PLAYER_NUMBER];
	//ジャストガードエフェクト
	Effect m_justGuardEffect[PLAYER_NUMBER];

	GameDirector* m_gameDirector = nullptr;
	Player* m_player[PLAYER_NUMBER] = { nullptr };
	Ball* m_ball = nullptr;

	/// @brief ガード系エフェクトの共通座標
	Vector3 m_efcGuardPos[PLAYER_NUMBER] = { { Vector3::Zero },{ Vector3::Zero },{ Vector3::Zero },{ Vector3::Zero } };

	/// @brief ガード予兆エフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void GuardBeginEffectUpdate(int plNum);

	/// @brief ガードエフェクトの更新
	/// @param plnum 更新するプレイヤー番号
	void GuardEffectUpdate(int plNum);

	/// @brief シールド回復エフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void ShieldRepairEffectUpdate(int plNum);

	/// @brief 行動不能エフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void KnockOutEffectUpdate(int plNum);


public:
	
	PlayerEffect();
	~PlayerEffect();
	bool Start();
	void Update();
	/// @brief キックエフェクトを再生
	/// @param plnum 再生するプレイヤー番号
	void PlayKickEffect(int plNum);

	/// @brief ガード予兆エフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayGuardBeginEffect(int plNum) { m_guardBeginEffect[plNum].Play(); }
	

	/// @brief ガードエフェクトを再生
	/// @param plnum 再生するプレイヤー番号
	void PlayGuardEffect(int plNum) { m_guardEffect[plNum].Play(); }
	/// @brief ガードエフェクトを停止
	/// @param plnum 停止するプレイヤー番号
	void StopGuardEffect(int plNum) { m_guardEffect[plNum].Stop(); }
	
	/// @brief ガードブレイクエフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayGuardBreakEffect(int plNum);

	/// @brief ジャストガードエフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayJustGuardEffect(int plNum);

	/// @brief シールドヒットエフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayShieldHitEffect(int plNum);

	/// @brief シールド回復エフェクトの再生
	/// @param plNum 再生するプレイヤー番号
	void PlayShieldRepairEffect(int plNum) { m_shieldRepairEffect[plNum].Play(); }

	/// @brief 行動不能エフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayKnockOutEffect(int plNum) { m_knockOutEffect[plNum].Play(); }

	/// @brief 行動不能エフェクトを停止
	/// @param plNum 停止するプレイヤー番号
	void StopKnockOutEffect(int plNum) { m_knockOutEffect[plNum].Stop(); }
};

