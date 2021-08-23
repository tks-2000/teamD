#pragma once

class GameDirector;
class Player;
class Effect;

class PlayerEffect : public IGameObject
{
private:
	/// @brief プレイヤーの番号
	int m_playerNum = 0;
	//エフェクト関連//
	/// @brief ボールをキックした時のエフェクト
	Effect m_kickEffect;
	/// @brief ガード時のエフェクト
	Effect m_guardEffect;

	Vector3 m_guardEffectPos =  Vector3::Zero;
	//ガードエフェクトを一定間隔で発生させるためのカウンター
	int m_guardEffectCouter = 0;
	/// @brief ガード発生の予兆エフェクト
	Effect m_guardBeginEffect;
	/// @brief ガードブレイクエフェクト
	Effect m_guardBreakEffect;
	/// @brief シールド回復エフェクト
	Effect m_shieldRepairEffect;
	/// @brief シールドヒットエフェクト
	Effect m_shieldHitEffect;
	/// @brief ガードヒットエフェクトを一定間隔で発生させるためのカウンター
	int m_shieldHitEffectCounter = 0;
	//行動不能時エフェクト(ピヨり)
	Effect m_knockOutEffect;
	//ジャストガードエフェクト
	Effect m_justGuardEffect;
	/// @brief ジャストガード時のプレイヤー強化エフェクト
	Effect m_kickBuffEffect;
	/// @brief パワーアップ中のカウンター
	int m_powerUpCounter = 0;
	/// @brief ダメージからの回復エフェクト
	Effect m_repairEffect;
	/// @brief リスポーン時のエフェクト
	Effect m_respawnEffect;
	/// @brief ダメージエフェクト
	Effect m_damageEffect;
	/// @brief バースト時のエフェクト
	Effect m_burstEffect;
	/// @brief アイテムバフエフェクト
	Effect m_itemBuffEffect;
	/// @brief アイテムバフエフェクト再生用カウンター
	int m_itemPowerUpCounter = 0;
	/// @brief ダッシュ中のエフェクト
	Effect m_dashEffect;
	/// @brief ダッシュ中のカウンタ
	int m_dashCounter =  0;


	GameDirector* m_gameDirector = nullptr;
	Player* m_player =  nullptr;
	Ball* m_ball = nullptr;

	
	/// @brief ガード系エフェクトの共通座標
	Vector3 m_efcGuardPos = Vector3::Zero;

	/// @brief ガード予兆エフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void GuardBeginEffectUpdate();

	/// @brief ガードエフェクトの更新
	/// @param plnum 更新するプレイヤー番号
	void GuardEffectUpdate();

	/// @brief シールド回復エフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void ShieldRepairEffectUpdate();

	/// @brief 行動不能エフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void KnockOutEffectUpdate();

	/// @brief 強化エフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void KickBuffEffectUpdate();

	/// @brief ダメージ回復エフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void RepairEffectUpdate();

	/// @brief リスポーン時のエフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void RespawnEffectUpdate();

	/// @brief アイテムバフエフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void ItemBuffEffectUpdate();

	/// @brief ダッシュエフェクトの更新
	/// @param plNum 更新するプレイヤー番号
	void DashEffectUpdate();

public:
	
	PlayerEffect();
	~PlayerEffect();
	bool Start();
	void Update();

	/// @brief プレイヤーの番号を設定
	/// @param plNum 設定するプレイヤー番号
	void SetPlayerNumber(const int plNum);

	/// @brief キックエフェクトを再生
	/// @param plnum 再生するプレイヤー番号
	void PlayKickEffect();

	/// @brief ガード予兆エフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayGuardBeginEffect() { m_guardBeginEffect.Play(); }
	

	/// @brief ガードエフェクトを再生
	/// @param plnum 再生するプレイヤー番号
	void PlayGuardEffect();
	/// @brief ガードエフェクトを停止
	/// @param plnum 停止するプレイヤー番号
	void StopGuardEffect() { m_guardEffect.Stop(); }
	
	/// @brief ガードブレイクエフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayGuardBreakEffect();

	/// @brief ジャストガードエフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayJustGuardEffect();

	/// @brief シールドヒットエフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayShieldHitEffect();

	/// @brief ダメージエフェクトを再生
	/// @param plNum 
	void PlayDamageEffect();

	/// @brief バーストエフェクトを再生
	void PlayBurstEffect();

	/// @brief シールド回復エフェクトの再生
	/// @param plNum 再生するプレイヤー番号
	void PlayShieldRepairEffect() { m_shieldRepairEffect.Play(); }

	/// @brief 行動不能エフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayKnockOutEffect() { m_knockOutEffect.Play(); }

	/// @brief 行動不能エフェクトを停止
	/// @param plNum 停止するプレイヤー番号
	void StopKnockOutEffect() { m_knockOutEffect.Stop(); }
	
	/// @brief プレイヤー強化エフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayKickBuffEffect();

	/// @brief ダメージからの回復エフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayRepairEffect() { m_repairEffect.Play(); }
	
	/// @brief リスポーン時のエフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayRespawnEffect() { m_respawnEffect.Play(); }

	/// @brief アイテムバフエフェクトを再生
	/// @param plNum 再生するプレイヤー番号
	void PlayItemBuffEffect();
	
	//ファイルパスの変更
	void ChangeItemBuffEffect(ItemBuffChange buffNum);
	
	/// @brief ダッシュ中のエフェクトを再生 
	/// @param plNum 再生するプレイヤー番号
	void PlayDashEffect();

};

