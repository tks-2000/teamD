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
	/// @brief ジャストガード時のプレイヤー強化エフェクト
	Effect m_kickBuffEffect[PLAYER_NUMBER];
	/// @brief ダメージからの回復エフェクト
	Effect m_repairEffect[PLAYER_NUMBER];
	/// @brief リスポーン時のエフェクト
	Effect m_respawnEffect[PLAYER_NUMBER];
	/// @brief ダメージエフェクト
	Effect m_damageEffect[PLAYER_NUMBER];
	/// @brief バースト時のエフェクト
	Effect m_burstEffect[PLAYER_NUMBER];
	/// @brief アイテムバフエフェクト
	Effect m_itemBuffEffect[PLAYER_NUMBER];
	/// @brief ダッシュ中のエフェクト
	Effect m_dashEffect[PLAYER_NUMBER];


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

	/// @brief 強化エフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void KickBuffEffectUpdate(int plNum);

	/// @brief ダメージ回復エフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void RepairEffectUpdate(int plNum);

	/// @brief リスポーン時のエフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void RespawnEffectUpdate(int plNum);

	/// @brief アイテムバフエフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void ItemBuffEffectUpdate(int plNum);

	/// @brief ダッシュエフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void DashEffectUpdate(int plNum);

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

	/// @brief ダメージエフェクトを再生
	/// @param plNum 
	void PlayDamageEffect(int plNum);

	/// @brief バーストエフェクトを再生
	void PlayBurstEffect(int plNum);

	/// @brief シールド回復エフェクトの再生
	/// @param plNum 再生するプレイヤー番号
	void PlayShieldRepairEffect(int plNum) { m_shieldRepairEffect[plNum].Play(); }

	/// @brief 行動不能エフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayKnockOutEffect(int plNum) { m_knockOutEffect[plNum].Play(); }

	/// @brief 行動不能エフェクトを停止
	/// @param plNum 停止するプレイヤー番号
	void StopKnockOutEffect(int plNum) { m_knockOutEffect[plNum].Stop(); }
	
	/// @brief プレイヤー強化エフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayKickBuffEffect(int plNum) { m_kickBuffEffect[plNum].Play(); }

	/// @brief ダメージからの回復エフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayRepairEffect(int plNum) { m_repairEffect[plNum].Play(); }
	
	/// @brief リスポーン時のエフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayRespawnEffect(int plNum) { m_respawnEffect[plNum].Play(); }

	/// @brief アイテムバフエフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayItemBuffEffect(int plNum) { m_itemBuffEffect[plNum].Play(); }
	
	//ファイルパスの変更
	void ChangeItemBuffEffect(int plNum, ItemBuffChange buffNum);
	
	/// @brief ダッシュ中のエフェクトを再生 
	/// @param plNum 再生するプレイヤー番号
	void PlayDashEffect(int plNum) { m_dashEffect[plNum].Play(); }

};

