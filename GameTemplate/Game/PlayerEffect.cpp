#include "stdafx.h"
#include "PlayerEffect.h"

namespace {
	/// @brief エフェクト用定数
	//キックエフェクトのファイルパス
	const char16_t* KICKEFFECT_FILEPATH = u"Assets/effect/kick.efk";
	//キックエフェクト発生位置を決める値。0に近いほどプレイヤー寄り
	const float KICKEFFECT_POSITION_RATE = 0.8f;
	//キックエフェクトの拡大率
	const Vector3 KICKEFFECT_SCALE = { 25.0f,25.0f,1.0f };

	//ガードエフェクトファイルパス
	const char16_t* GUARDEFFECT_FILEPATH = u"Assets/effect/shield.efk";
	//ガードエフェクトの拡大率(立体なのでz軸方向にも拡大している)
	const Vector3 GUARDEFFECT_SCALE = { 80.0f,80.0f,80.0f };
	//ガードエフェクト発生位置のy座標を決めるための定数
	const float GUARDEFFECT_POS_Y = 80.0f;

	//ガード予兆エフェクトのファイルパス
	const char16_t* GUARDEFFECT_BEGIN_FILEPATH = u"Assets/effect/shield_begin.efk";
	//ガード予兆エフェクトの拡大率
	const Vector3 GUARDEFFECT_BEGIN_SCALE = { 20.0f,20.0f,1.0f };

	//ガード破壊エフェクトのファイルパス
	const char16_t* GUARDEFFECT_BREAK_FILEPATH = u"Assets/effect/shieldbreak.efk";
	//ガード破壊エフェクトの拡大率
	const Vector3 GUARDEFFECT_BREAK_SCALE = { 15.0f,15.0f,15.0f };

	//シールド回復エフェクトのファイルパス
	const char16_t* GUARDEFFECT_REPAIR_FILEPATH = u"Assets/effect/shieldrepair.efk";
	//シールド回復エフェクトの拡大率
	const Vector3 GUARDEFFECT_REPAIR_SCALE = { 12.5f,12.5f,12.5f };

	//ガードヒットエフェクトのファイルパス
	const char16_t* GUARDEFFECT_HIT_FILEPATH = u"Assets/effect/shieldhit.efk";
	//ガードヒットエフェクトの拡大率
	const Vector3 GUARDEFFECT_HIT_SCALE = { 17.0f,17.0f,17.0f };
	//ガードヒットエフェクト発生の距離
	const float GUARDEFFECT_HIT_DISTANCE = 150.0f;

	//行動不能エフェクトのファイルパス
	const char16_t* KNOCKOUTEFFECT_FILEPATH = u"Assets/effect/knockout.efk";
	//行動不能エフェクトのスケール
	const Vector3 KNOCKOUTEFFECT_SCALE = { 15.0f,15.0f,15.0f };

	//ジャストガードエフェクトのファイルパス
	const char16_t* JUSTGUARDEFFECT_FILEPATH = u"Assets/effect/justguard.efk";
	//ジャストガードエフェクトのスケール
	const Vector3 JUSTGUARDEFFECT_SCALE = { 10.0f,10.0f,10.0f };

	//強化エフェクトのファイルパス
	const char16_t* KICKBUFFEFFECT_FILEPATH = u"Assets/effect/kickbuff.efk";
	//強化エフェクトのスケール
	const Vector3 KICKBUFFEFFECT_SCALE = { 20.0f,20.0f,20.0f };
	//強化エフェクトのy座標発生位置を決めるための定数
	const float KICKBUFFEFFECT_POS_Y = 10.0f;

	//ダメージ回復エフェクトのファイルパス
	const char16_t* REPAIREFFECT_FILEPATH = u"Assets/effect/repair.efk";
	//ダメージ回復エフェクトのスケール
	const Vector3 REPAIREFFECT_SCALE = { 10.0f,10.0f,10.0f };
	
	//ダメージエフェクト
	const char16_t* DAMAGEEFFECT_FILEPATH = u"Assets/effect/damage.efk";
	const Vector3 DAMAGEEFFECT_SCALE_MIN = { 5.0f,5.0f,5.0f };
	const Vector3 DAMAGEEFFECT_SCALE_MAX = { 30.0f,30.0f,30.0f };
	const float DAMAGEEFFECT_BALLSPEED_MAX = 60.0f;
	const float DAMAGEEFFECT_BALLSPEED_MIN = 0.0f;



	//リスポーン時のエフェクトのファイルパス(プレイヤー別)
	const char16_t* RESPAWNEFFECT_FILEPATH[4] = { 
		{u"Assets/effect/respawn_red.efk"},
		{u"Assets/effect/respawn_blue.efk"},
		{u"Assets/effect/respawn_yellow.efk"},
		{u"Assets/effect/respawn_green.efk"}
	};
	const Vector3 RESPAWNEFFECT_SCALE = { 20.0f,20.0f,20.0f };
	const float RESPAWNEFFECT_OFFSET_Y = 400.0f;

}

PlayerEffect::PlayerEffect()
{
	/// @brief プレイヤーの人数を調べてその数だけエフェクトを用意する
	m_gameDirector = FindGO<GameDirector>(GAME_DIRECTOR_NAME);

	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		//キック時のエフェクトを初期化
		m_kickEffect[plNum].Init(KICKEFFECT_FILEPATH);
		//ガード時のエフェクトを初期化
		m_guardEffect[plNum].Init(GUARDEFFECT_FILEPATH);
		//ガード予兆エフェクトを初期化
		m_guardBeginEffect[plNum].Init(GUARDEFFECT_BEGIN_FILEPATH);
		//ガード破壊のエフェクトを初期化
		m_guardBreakEffect[plNum].Init(GUARDEFFECT_BREAK_FILEPATH);
		//シールド回復のエフェクトを初期化
		m_shieldRepairEffect[plNum].Init(GUARDEFFECT_REPAIR_FILEPATH);
		//ガードヒットエフェクトを初期化
		m_shieldHitEffect[plNum].Init(GUARDEFFECT_HIT_FILEPATH);
		//行動不能エフェクトを初期化
		m_knockOutEffect[plNum].Init(KNOCKOUTEFFECT_FILEPATH);
		//ジャストガードエフェクトを初期化
		m_justGuardEffect[plNum].Init(JUSTGUARDEFFECT_FILEPATH);
		//強化エフェクトを初期化
		m_kickBuffEffect[plNum].Init(KICKBUFFEFFECT_FILEPATH);
		//ダメージ回復エフェクトを初期化
		m_repairEffect[plNum].Init(REPAIREFFECT_FILEPATH);
		//ダメージエフェクトを初期化
		m_damageEffect[plNum].Init(DAMAGEEFFECT_FILEPATH);

		//プレイヤー別エフェクトの初期化
		//リスポーン時のエフェクトを初期化
		m_respawnEffect[plNum].Init(RESPAWNEFFECT_FILEPATH[plNum]);

	}
}

PlayerEffect::~PlayerEffect()
{

}

bool PlayerEffect::Start()
{
	/// @brief プレイヤーとボールの情報を入手する 
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_player[plNum] = FindGO<Player>(PLAYER_NAME[plNum]);
	}
	m_ball = FindGO<Ball>(BALL_NAME);

	return true;
}

void PlayerEffect::PlayKickEffect(int plNum)
{
	/// @brief プレイヤーとボールの位置からエフェクトの再生位置と角度を決める 
	Vector3 toBallDir = m_player[plNum]->GetToBallVec();
	Quaternion efcRot = Quaternion::Identity;
	efcRot.SetRotation(Vector3::AxisY, atan2(toBallDir.x, toBallDir.z));
	Vector3 efcPos = Vector3::Zero;
	efcPos.Lerp(KICKEFFECT_POSITION_RATE, m_player[plNum]->GetPosition(), m_ball->GetPosition());

	m_kickEffect[plNum].Play();
	m_kickEffect[plNum].SetPosition(efcPos);
	m_kickEffect[plNum].SetRotation(efcRot);
	m_kickEffect[plNum].SetScale(KICKEFFECT_SCALE);
	m_kickEffect[plNum].Update();
}

void PlayerEffect::PlayGuardBreakEffect(int plNum)
{
	m_guardBreakEffect[plNum].Play();
	m_guardBreakEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_guardBreakEffect[plNum].SetScale(GUARDEFFECT_BREAK_SCALE);
	m_guardBreakEffect[plNum].Update();
}

void PlayerEffect::PlayJustGuardEffect(int plNum)
{
	Vector3 efcPos = m_player[plNum]->GetPosition();
	efcPos.y += GUARDEFFECT_POS_Y;
	m_justGuardEffect[plNum].Play();
	m_justGuardEffect[plNum].SetPosition(efcPos);
	m_justGuardEffect[plNum].SetScale(JUSTGUARDEFFECT_SCALE);
	m_justGuardEffect[plNum].Update();
}

void PlayerEffect::PlayShieldHitEffect(int plNum)
{
	/// @brief プレイヤーとボールの位置からエフェクトの再生位置と角度を決める 
	Vector3 toBallDir = m_player[plNum]->GetToBallVec();
	Quaternion efcRot = Quaternion::Identity;
	efcRot.SetRotation(Vector3::AxisY, atan2(toBallDir.x, toBallDir.z));
	Vector3 efcPos = Vector3::Zero;
	efcPos.Lerp(0.5f, m_player[plNum]->GetPosition(), m_ball->GetPosition());
	efcPos.y += GUARDEFFECT_POS_Y;

	m_shieldHitEffect[plNum].Play();
	m_shieldHitEffect[plNum].SetPosition(efcPos);
	m_shieldHitEffect[plNum].SetRotation(efcRot);
	m_shieldHitEffect[plNum].SetScale(GUARDEFFECT_HIT_SCALE);
	m_shieldHitEffect[plNum].Update();
}

void PlayerEffect::PlayDamageEffect(int plNum)
{
	Vector3 efcScale = Vector3::Zero;

	//最大値に対する現在のスピードの割合を計算
	float speedRate = m_ball->GetVelocity() / DAMAGEEFFECT_BALLSPEED_MAX;

	//1.0を超えるときに1.0にする
	if (speedRate > 1.0f) {
		speedRate = 1.0f;
	}

	//得られた割合から拡大率を線形補完
	efcScale.Lerp(speedRate, DAMAGEEFFECT_SCALE_MIN, DAMAGEEFFECT_SCALE_MAX);

	m_damageEffect[plNum].Play();
	m_damageEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_damageEffect[plNum].SetScale(efcScale);
	m_damageEffect[plNum].Update();
}

void PlayerEffect::GuardBeginEffectUpdate(int plNum)
{
	m_guardBeginEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_guardBeginEffect[plNum].SetScale(GUARDEFFECT_BEGIN_SCALE);
	m_guardBeginEffect[plNum].Update();
}

void PlayerEffect::GuardEffectUpdate(int plNum)
{
	m_guardEffectPos[plNum] = m_efcGuardPos[plNum];
	m_guardEffect[plNum].SetPosition(m_guardEffectPos[plNum]);
	m_guardEffect[plNum].SetScale(GUARDEFFECT_SCALE);
	m_guardEffect[plNum].Update();
}

void PlayerEffect::ShieldRepairEffectUpdate(int plNum)
{
	m_shieldRepairEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_shieldRepairEffect[plNum].SetScale(GUARDEFFECT_REPAIR_SCALE);
	m_shieldRepairEffect[plNum].Update();
}

void PlayerEffect::KnockOutEffectUpdate(int plNum)
{
	m_knockOutEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_knockOutEffect[plNum].SetScale(KNOCKOUTEFFECT_SCALE);
	m_knockOutEffect[plNum].Update();
}

void PlayerEffect::KickBuffEffectUpdate(int plNum)
{
	Vector3 efcPos = m_player[plNum]->GetPosition();
	efcPos.y += KICKBUFFEFFECT_POS_Y;

	m_kickBuffEffect[plNum].SetPosition(efcPos);
	m_kickBuffEffect[plNum].SetScale(KICKBUFFEFFECT_SCALE);
	m_kickBuffEffect[plNum].Update();
}

void PlayerEffect::RepairEffectUpdate(int plNum)
{
	m_repairEffect[plNum].SetPosition(m_efcGuardPos[plNum]);
	m_repairEffect[plNum].SetScale(REPAIREFFECT_SCALE);
	m_repairEffect[plNum].Update();
}

void PlayerEffect::RespawnEffectUpdate(int plNum)
{

	Vector3 efcPos = m_player[plNum]->GetRespawnPoint();
	efcPos.y -= RESPAWNEFFECT_OFFSET_Y;
	m_respawnEffect[plNum].SetPosition(efcPos);
	m_respawnEffect[plNum].SetScale(RESPAWNEFFECT_SCALE);
	m_respawnEffect[plNum].Update();
}

void PlayerEffect::Update()
{
	/// @brief 更新が必要なエフェクトをすべて更新する
	for (int plNum = 0; plNum < m_gameDirector->GetPlayerNum(); plNum++) {
		m_efcGuardPos[plNum] = m_player[plNum]->GetPosition();
		m_efcGuardPos[plNum].y += GUARDEFFECT_POS_Y;
		GuardBeginEffectUpdate(plNum);
		GuardEffectUpdate(plNum);
		ShieldRepairEffectUpdate(plNum);
		KnockOutEffectUpdate(plNum);
		KickBuffEffectUpdate(plNum);
		RepairEffectUpdate(plNum);
		RespawnEffectUpdate(plNum);
	}
}