#include "stdafx.h"
#include "PlayerCollide.h"

namespace {
	/// @brief ボールに接触する判定
	const float COLLIDE_RATE = 0.0f;
	/// @brief ボールに接触する距離
	const float COLLIDE_DISTANCE = 80.0f;
	/// @brief 横方向に吹き飛ぶ勢い
	const float BLOW_AWAY_RATE = 2.0f;
	/// @brief 縦方向に吹き飛ぶ勢い
	const float BLOW_AWAY_HEIGHT_RATE = 1.0f;
	/// @brief アイテムを取ったときの吹き飛ぶ勢い
	const float DECREASE_BLOW_AWAY_RATE = 1.0f;
	/// @brief 勢いよく当たった扱いになるボールの速度
	const float STRONG_HIT = 20.0f;
	/// @brief ジャストガード可能な時間
	const float POSSIBLE_JUST_GUARD_TIME = 0.01f;
}

PlayerCollide::PlayerCollide()
{

}

PlayerCollide::~PlayerCollide()
{

}

bool PlayerCollide::Start()
{
	m_ball = FindGO<Ball>(BALL_NAME);
	m_score = FindGO<Score>(SCORE_NAME);
	m_se = FindGO<Se>(SE_NAME);
	return true;
}

void PlayerCollide::Update()
{
	//準備完了まで処理を行わない
	if (m_setUp == false) {
		return;
	}

	//状態によって変化するパラメーターを決定
	DetermineParameters();
	//ボールとの距離を計算
	ToBallVectorCalculation();
	//ボールが動いている時にボールとの距離が接触判定まで近づいたら…
	if (m_ball->IsMove() == true && m_ballDistance < COLLIDE_DISTANCE) {
		//ガード中なら…
		if (m_plAction->IsGuard() == true) {
			//ガード中のぶつかる処理を行う
			GuardCollide();
		}
		//ガードしていないなら…
		else {
			//ボールとぶつかる処理を行う
			BallCollide();
		}
	}
	//ボールが動いていない・接触判定にならなかったら…
	else {
		//触れていない状態に変更
		m_guradHit = false;
	}
}

void PlayerCollide::SetPlayerNumber(const int plNum)
{
	//自分のプレイヤー番号を決定
	m_playerNum = plNum;
	//自分と同じプレイヤー番号のデータを入手
	m_player = FindGO<Player>(PLAYER_NAME[m_playerNum]);
	m_plAction = FindGO<PlayerAction>(PLAYER_ACTION_NAME[m_playerNum]);
	m_plMove = FindGO<PlayerMove>(PLAYER_MOVE_NAME[m_playerNum]);
	m_plEffect = FindGO<PlayerEffect>(PLAYER_EFFECT_NAME[m_playerNum]);
	m_plReinforcement = FindGO<PlayerReinforcement>(PLAYER_REINFORCEMENT_NAME[m_playerNum]);
	//準備完了
	m_setUp = true;
}

void PlayerCollide::DetermineParameters()
{
	//プレイヤーが防御強化状態だったら…
	if (m_plReinforcement->IsDefenseUp() == true) {
		//吹き飛ぶ勢いを防御強化状態中の勢いにする
		m_blowAwayRate = DECREASE_BLOW_AWAY_RATE;
	}
	//プレイヤーが防御強化状態でない場合…
	else {
		//吹き飛ぶ勢いを通常時の勢いにする
		m_blowAwayRate = BLOW_AWAY_RATE;
	}
}

void PlayerCollide::ToBallVectorCalculation()
{
	//ボールの座標から自分の座標を引いて自分からボールに向かって伸びるベクトルを計算する
	m_toBallVec = m_ball->GetPosition() - m_player->GetPosition();
	//ボールとの距離もここで計算する
	BallDistanceCalculation();
	//縦方向を消す
	m_toBallVec.y = 0.0f;
	//正規化する
	m_toBallVec.Normalize();
}

void PlayerCollide::BallDistanceCalculation()
{
	//ボールに向かって伸びるベクトルから長さを取得する
	m_ballDistance = m_toBallVec.Length();
}

void PlayerCollide::BallCollide()
{
	//ボールへのベクトルとボールの向きで当たる角度を決める
	float matchRate = Dot(m_ball->GetMoveDirection(), m_toBallVec);
	//ボールが動いていない・接触判定にならなかった場合…
	if (m_ball->IsMove() == false || matchRate > COLLIDE_RATE) {
		//処理を終了する
		return;
	}

	//ボールと自分の位置から吹き飛ばされる方向を決める
	Vector3 repulsiveForce = m_player->GetPosition() - m_ball->GetPosition();
	//縦方向の成分を消す
	repulsiveForce.y = 0.0f;
	//正規化して方向ベクトルにする
	repulsiveForce.Normalize();
	//ボールの移動方向を吹き飛ぶ方向と逆向きに設定する
	m_ball->SetMoveDirection(repulsiveForce * -1.0f);

	//プレイヤーが死亡時の無敵時間中の場合…
	if (m_player->IsDie() == true) {
		//ダメージを受けなかったときのSEを鳴らす
		m_se->PlayNoDamageCollideSe();
		//処理を終了する
		return;
	}

	//吹き飛ぶ勢いを乗算して移動量を決める
	repulsiveForce *= m_ball->GetVelocity() * m_blowAwayRate;

	//縦方向は別に計算する
	repulsiveForce.y = m_ball->GetVelocity() * BLOW_AWAY_HEIGHT_RATE;

	//移動速度に吹き飛ぶ勢いを設定する
	m_plMove->SetMoveSpeed(repulsiveForce * 2.0f);

	//ダメージエフェクトを再生
	m_plEffect->PlayDamageEffect();

	//ガードブレイク中の場合…
	if (m_plAction->IsGuardBreak() == true) {
		//行動不能エフェクトを消す
		m_plEffect->StopKnockOutEffect();
		//行動不能SEも消す
		m_se->StopStanSe(m_playerNum);
	}
	//ダメージ中でない場合…
	if (m_player->IsDamage() == false) {
		//行動不能エフェクトを再生
		m_plEffect->PlayKnockOutEffect();
		//行動不能SEを鳴らす
		m_se->PlayStanSe(m_playerNum);
	}

	//プレイヤーをダメージ中に設定する
	m_player->SetDamage();

	//ボールの速度が強く当たった扱いのになる速度を超えていたら…
	if (m_ball->GetVelocity() > STRONG_HIT) {
		//強く当たったSEを鳴らす
		m_se->PlayStrongCollideSe();
	}
	//ボールの速度が強く当たった扱いのになる速度を超えていなかったら…
	else {
		//弱く当たったSEを鳴らす
		m_se->PlayWeakCollideSe();
	}

	//ボールの番号から攻撃してきたプレイヤーの番号を記憶する
	m_player->SetHaveAttackedPlayer(m_ball->GetPlayerInformation());

	//攻撃してきたプレイヤーが自分ではない場合…
	if (m_player->GetHaveAttackedPlayer() != m_playerNum) {
		//攻撃してきたプレイヤーにスコアを加算する
		m_score->AddScore200(m_player->GetHaveAttackedPlayer());
	}
}

void PlayerCollide::GuardCollide()
{
	//ガード中に接触していない場合…
	if (m_guradHit == false) {
		//ガードヒットエフェクトの発生
		m_plEffect->PlayShieldHitEffect();
		//ガードヒットSEを再生
		m_se->PlayShieldHitSe();
		//接触した状態に変更
		m_guradHit = true;
	}

	//ガード時間がジャストガード判定時間内ならジャストガード発動
	if (m_plAction->GetGuardTime() < POSSIBLE_JUST_GUARD_TIME) {
		//ボールを完全に停止
		m_ball->SetVelocity(0.0f);

		//ジャストガードエフェクトの再生
		m_plEffect->PlayJustGuardEffect();
		//SEを鳴らす
		m_se->PlayJustGuardSe();
		//プレイヤーを強化状態に変更
		m_plReinforcement->ChangeSelfPowerUp();
	}
	//ジャストガード判定にならなかったら…
	else {
		//ボールの勢いに応じてガード耐久値を減らす
		float shieldDamage = m_ball->GetVelocity() * m_plAction->GetGuradDecreaseValue() * 10.0f;
		m_plAction->SetGuardDamage(shieldDamage);

		//ガード耐久力が0より多かったら…
		if (m_plAction->GetGuardDurability() > 0.0f) {
			//ボールの勢いに応じてノックバックする。
			Vector3 repulsiveForce = m_toBallVec * -1.0f;
			repulsiveForce.Normalize();
			repulsiveForce *= m_ball->GetVelocity();
			repulsiveForce.y = m_ball->GetVelocity() * 0.1f;
			m_plMove->SetMoveSpeed(repulsiveForce);

			//ボールは逆向きに跳ね返る
			m_ball->SetVelocity(m_ball->GetVelocity() / 2.0f);
			m_ball->SetMoveDirection(repulsiveForce * -1.0f);
		}
	}
}