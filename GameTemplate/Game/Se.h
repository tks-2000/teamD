#pragma once

class CSoundSource;
class GameDirector;

const int PLNUM = 4;

class Se : public IGameObject
{
private:
	float m_seVolume = 1.0f;

	CSoundSource* m_stanSe[PLNUM] = { nullptr };

	GameDirector* m_gameDirector = nullptr;

public:
	Se();
	~Se();
	bool Start();
	void Update();

	//コマンド選択
	void PlaySelectKeySe();
	//コマンド決定
	void PlayPressKeySe();
	//試合開始のカウント
	void PlayCountDownSe();
	//試合終了
	void PlayEndSe();
	//キック時
	void PlayKickSe();
	//強化時キック
	void PlayPoweredKickSe();
	//シールド展開
	void PlayGuardStartSe();
	//シールド解除
	void PlayGuardEndSe();
	//ジャストガード
	void PlayJustGuardSe();
	//シールド回復
	void PlayShieldRepairSe();
	//シールド時ヒット
	void PlayShieldHitSe();
	//シールドブレイク
	void PlayBreakSe();
	//壁反射
	void PlayReflectSe();
	//ボールに衝突(弱)
	void PlayWeakCollideSe();
	//ボールに衝突(強)
	void PlayStrongCollideSe();
	//ボールに衝突(無敵)
	void PlayNoDamageCollideSe();
	//箱に衝突
	void PlayBoxCollideSe();
	//箱が開く
	void PlayBoxOpenSe();
	//行動不能
	void PlayStanSe(int plNum);
	//行動不能停止
	void StopStanSe(int plNum) { m_stanSe[plNum]->Stop(); }
	//スタミナ切れ
	void PlayStaminaOverSe();
	//スタミナ回復
	void PlayStaminaRecoverySe();
	//アイテム入手
	void PlayItemGetSe();
	//撃破
	void PlayDefeatSe();
	//リスポーン
	void PlayReSpawnSe();
	//順位表示
	void PlayRankingSe();
	//歓声
	void PlayCheersSe();
	//箱の落下
	void PlayFallSe();
};

