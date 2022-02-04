#include "stdafx.h"
#include "Player.h"

namespace {
	/// @brief 落下扱いになる高さ
	const float FALLING_HEIGHT = -3000.0f;
	/// @brief バーストエフェクトを再生する判定を行う高さ
	const float BURST_HEIGHT = -500.0f;
	/// @brief 1Pの初期位置
	const Vector3 PLAYER1_STARTPOS = { -400.0f,500.0f,400.0f };
	/// @brief 2Pの初期位置
	const Vector3 PLAYER2_STARTPOS = { 400.0f,500.0f,400.0f };
	/// @brief 3Pの初期位置
	const Vector3 PLAYER3_STARTPOS = { -400.0f,500.0f,-400.0f };
	/// @brief 4Pの初期位置
	const Vector3 PLAYER4_STARTPOS = { 400.0f,500.0f,-400.0f };
	/// @brief ポイントライトの高さ
	const float POINT_LIGHT_HEIGHT = 50.0f;
	/// @brief プレイヤーの半径
	const float PLAYER_RADIUS = 20.0f;
	/// @brief プレイヤーの高さ
	const float PLAYER_HEIGHT = 50.0f;
	/// @brief ダメージを受けて復帰するのにかかる時間
	const float DAMAGE_RETURN_TIME = 100.0f;
	/// @brief プレイヤーモデルの表示優先度
	const int PRIORITY = 1;
	/// @brief プレイヤーのリスポーン時の無敵時間
	const float MUTEKI_TIME = 3.0f;
	/// @brief リスポーン時の無敵時間の初期化
	const float TIME_ZERO = 0.0f;
	/// @brief スコアの加算数値
	const int SCORE_ADD = 100;
	/// @brief スコアの減算数値
	const int SCORE_PULL = -100;
	/// @brief キックのクールタイム
	const int KICK_COOLTIME = 20;
	
	/// @brief アイテムによる強化時間
	const float ITEM_POWERUP_TIME = 10.0f;
	/// @brief 勢いよく当たった扱いになるボールの速度
	const float STRONG_HIT = 20.0f;
	/// @brief リスポーンコマンドを押し続けて発動するまでの時間
	const float RESPAWN_TIME = 5.0f;
}

Player::Player()
{
	

	//プレイヤーの初期状態を設定
	m_setUp = false;
	m_gravity = 5.0f;
	m_charaCon.Init(PLAYER_RADIUS, PLAYER_HEIGHT, m_position);
}

Player::~Player()
{
	//プレイヤーモデルを削除
	DeleteGO(m_skinModelRender);
	if (m_setUp == true) {
		DeleteGO(m_plAction);
		DeleteGO(m_plCollide);
		DeleteGO(m_plEffect);
		DeleteGO(m_plMove);
		DeleteGO(m_plReinforcement);
	}
}

bool Player::Start()
{
	//必要なデータを取得
	m_timer = FindGO<Timer>(TIMER_NAME);
	m_score = FindGO<Score>(SCORE_NAME);
	m_lig = FindGO<Lighting>(LIGHTING_NAME);
	//m_plEffect = FindGO<PlayerEffect>(PLAYER_EFFECT_NAME);
	m_ball = FindGO<Ball>(BALL_NAME);
	m_se = FindGO<Se>(SE_NAME);

	m_animationClips[enAnimation_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimation_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimation_Run].Load("Assets/animData/unitychan/run.tka");

	m_animationClips[enAnimation_Idle].SetLoopFlag(true);
	m_animationClips[enAnimation_Walk].SetLoopFlag(true);
	m_animationClips[enAnimation_Run].SetLoopFlag(true);

	m_skinModelRender = NewGO<SkinModelRender>(PRIORITY);

	/*m_skinModelRender->InitA(UNITYCHAN_MODEL, "Assets/modelData/unityChan.tks", m_animationClips, enAnimation_Num);
	m_skinModelRender->PlayAnimation(enAnimation_Idle, 1.0f);*/


	m_ui = FindGO<GameUI>(GAME_UI_NAME);

	return true;
}

void Player::SetPlayerNumber(int num)
{

	//受け取った番号に応じて自分が何Pかを設定する
	m_myNumber = num;
	switch (num)
	{
	case enPlayer1: {
		m_playerColor = RED;			//プレイヤーのカラーを赤にする。
		m_startPos = PLAYER1_STARTPOS;	//プレイヤーの座標を初期値にする。
		m_skinModelRender->InitA(UNITYCHAN_MULTI_FILEPATH[num], "Assets/modelData/unityChan.tks", enModelUpAxisY, m_animationClips, enAnimation_Num,false);
	}break;
	case enPlayer2: {
		m_playerColor = BLUE;
		m_startPos = PLAYER2_STARTPOS;
		m_skinModelRender->InitA(UNITYCHAN_MULTI_FILEPATH[num], "Assets/modelData/unityChan.tks", enModelUpAxisY, m_animationClips, enAnimation_Num,false);
	}break;
	case enPlayer3: {
		m_playerColor = YELLOW;
		m_startPos = PLAYER3_STARTPOS;
		m_skinModelRender->InitA(UNITYCHAN_MULTI_FILEPATH[num], "Assets/modelData/unityChan.tks", enModelUpAxisY, m_animationClips, enAnimation_Num,false);
	}break;
	case enPlayer4: {
		m_playerColor = GREEN;
		m_startPos = PLAYER4_STARTPOS;
		m_skinModelRender->InitA(UNITYCHAN_MULTI_FILEPATH[num], "Assets/modelData/unityChan.tks", enModelUpAxisY, m_animationClips, enAnimation_Num,false);
	}break;
	}
	m_position = m_startPos;
	m_charaCon.SetPosition(m_position);

	m_lig->SetPointLightColor(m_myNumber, m_playerColor);
	m_lig->SetPointLightRange(m_myNumber, 500.0f);

	m_plAction = NewGO<PlayerAction>(PRIORITY_VERYLOW, PLAYER_ACTION_NAME[m_myNumber]);
	m_plCollide = NewGO<PlayerCollide>(PRIORITY_VERYLOW, PLAYER_COLLID_NAME[m_myNumber]);
	m_plEffect = NewGO<PlayerEffect>(PRIORITY_VERYLOW, PLAYER_EFFECT_NAME[m_myNumber]);
	m_plMove = NewGO<PlayerMove>(PRIORITY_VERYLOW, PLAYER_MOVE_NAME[m_myNumber]);
	m_plReinforcement = NewGO<PlayerReinforcement>(PRIORITY_VERYLOW, PLAYER_REINFORCEMENT_NAME[m_myNumber]);

	m_plAction->SetPlayerNumber(m_myNumber);
	m_plCollide->SetPlayerNumber(m_myNumber);
	m_plEffect->SetPlayerNumber(m_myNumber);
	m_plMove->SetPlayerNumber(m_myNumber);
	m_plReinforcement->SetPlayerNumber(m_myNumber);

	m_skinModelRender->PlayAnimation(enAnimation_Idle, 1.0f);
	m_setUp = true;
}

void Player::ReSpawn() {
	//スタート位置にリスポーンさせる
	m_position = m_startPos;
	m_charaCon.SetPosition(m_position);
	m_damage = false;
	m_damageTime = 0.0f;
	m_breakGuard = false;
	m_mutekiTime = MUTEKI_TIME;
	m_lig->SetPointLightBlinking(m_myNumber, m_mutekiTime, 0.07f);
	m_dieFlag = true;

	//リスポーン時のエフェクトを再生
	m_plEffect->PlayRespawnEffect();
	m_plEffect->StopKnockOutEffect();
	m_se->PlayReSpawnSe();
	m_plReinforcement->ReinforcementRelease();

}

void Player::Muteki()
{
	m_mutekiTime -= g_gameTime->GetFrameDeltaTime();
	//リスポーン時に少しの間ボールに当たらなくなる
	if (m_mutekiTime <= TIME_ZERO) {
		m_dieFlag = false;
		m_burstFlag = false;
	}
}

void Player::Animation()
{
	switch (m_anim)
	{
	case enAnimation_Idle: {
		m_skinModelRender->PlayAnimation(enAnimation_Idle, 0.2f);
	}break;
	case enAnimation_Walk: {
		m_skinModelRender->PlayAnimation(enAnimation_Walk, 0.2f);
	}break;
	case enAnimation_Run: {
		m_skinModelRender->PlayAnimation(enAnimation_Run, 0.2f);
	}break;
	default:
		break;
	}
}

void Player::SetItemChangeState()
{
	//各フラグが前フレームと変化なしだったら処理しない
	if (m_kickUp == m_kickUpPrevFrame &&
		m_guardUp == m_guardUpPrevFrame &&
		m_speedUp == m_speedUpPrevFrame) {

		return;
	}

	//各フラグが1つでも前フレームと変化していたら処理に移行
	if (m_kickUp == true && m_kickUpPrevFrame == false) {
		m_itemBuffChageState = enItemBuff_Kick;
		m_plEffect->ChangeItemBuffEffect(m_itemBuffChageState);
	}
	if (m_guardUp == true && m_guardUpPrevFrame == false) {
		m_itemBuffChageState = enItemBuff_Guard;
		m_plEffect->ChangeItemBuffEffect(m_itemBuffChageState);
	}
	if (m_speedUp == true && m_speedUpPrevFrame == false) {
		m_itemBuffChageState = enItemBuff_Speed;
		m_plEffect->ChangeItemBuffEffect(m_itemBuffChageState);
	}

}

void Player::RecordFlags()
{
	//現フレームのバースト状況を記録
	if (m_burstFlagPrevFrame != m_burstFlag) {
		m_burstFlagPrevFrame = m_burstFlag;
	}

	//アイテムパワーアップフラグ各種の記録
	if (m_kickUpPrevFrame != m_kickUp) {
		m_kickUpPrevFrame = m_kickUp;
	}
	
	if (m_guardUpPrevFrame != m_guardUp) {
		m_guardUpPrevFrame = m_guardUp;
	}

	if (m_speedUpPrevFrame != m_speedUp) {
		m_speedUpPrevFrame = m_speedUp;
	}

}

void Player::Update()
{
	if (m_setUp == false) {
		return;
	}
	//アイテムを取ったら自身のバフ状況を変更
	SetItemChangeState();
	
	//アイテムバフエフェクトの再生処理
	if (m_kickUp == true ||
		m_guardUp == true ||
		m_speedUp == true) {

		
		m_plEffect->PlayItemBuffEffect();
		
	}

	m_stamina = m_plMove->GetStamina();
	m_guardDurability = m_plAction->GetGuardDurability();
	

	//ダメージ中はスティック入力を受け付けない
	if (m_damage == true) {
		m_Lstickx = 0.0f;
		m_Lsticky = 0.0f;
		m_damageTime += 1.0f;
	}
	if (m_damageTime > DAMAGE_RETURN_TIME) {
		m_damageTime = 0.0f;
		if (m_breakGuard == false) {
			m_plEffect->StopKnockOutEffect();
			m_se->StopStanSe(m_myNumber);
		}
		if (m_breakGuard != true) {
			m_plEffect->PlayRepairEffect();
		}
		m_damage = false;
	}

	if (m_breakGuard == true)
	{
		m_Lstickx = 0.0f;
		m_Lsticky = 0.0f;
	}

	/// @brief キッククールタイム
	if (m_kickCooling == true)
	{
		m_kickCooler += 1;
		if (m_kickCooler == KICK_COOLTIME) {
			m_kickCooling = false;
			m_kickCooler = 0;
		}
	}


	if (m_dieFlag == true) {
		Muteki();
	}

	//パワーアップエフェクトの再生
	if (m_powerUp == true) {

		m_plEffect->PlayKickBuffEffect();

	}
	else {
		m_powerUpCounter = 0.0f;
	}

	if (m_itemPowerUp == true) {
		m_itemPowerUpTime += g_gameTime->GetFrameDeltaTime();
	}
	else {
		m_kickUp = false;
		m_guardUp = false;
		m_speedUp = false;
	}
	if (m_itemPowerUpTime > ITEM_POWERUP_TIME) {
		m_itemPowerUp = false;
	}

	//自分のポイントライトの位置と方向を設定
	Vector3 pos = m_position;
	pos.y = POINT_LIGHT_HEIGHT;
	m_lig->SetPointLighitPos(m_myNumber, pos);

	/*Vector3 dir = m_position - m_lig->GetSpotLightPos(m_myNumber);
	m_lig->SetSpotLightDirection(m_myNumber, dir);*/

	//キャラクターコントローラーで座標を決める
	//m_position = m_charaCon.Execute(m_moveSpeed, 1.0f);

	
	
	/// @brief モデルに座標と回転を伝える
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_qRot);

	//アニメーション
	Animation();

	//現フレームのフラグ状態を記録
	RecordFlags();
	//プレイヤーが落下したらリスポーンする
	if (m_position.y < FALLING_HEIGHT) {

		if (m_haveAttackedPlayer != m_myNumber) {
			m_score->AddScore500(m_haveAttackedPlayer);
			m_score->DeclineScore(m_myNumber);
		}
		else {
			m_score->HalfScore(m_myNumber);
		}

		ReSpawn();
	}

	//バースト処理
	if (m_position.y < BURST_HEIGHT) {
		m_burstFlag = true;

		if (m_burstFlag == true && m_burstFlagPrevFrame == false) {
			if (m_damage == true || m_breakGuard == true) {
				m_plEffect->StopKnockOutEffect();
				m_se->StopStanSe(m_myNumber);
			}
			m_plEffect->PlayBurstEffect();
			m_se->PlayDefeatSe();
		}
	}

	if (g_pad[m_myNumber]->IsPress(enButtonStart) && m_damage == false) {
		m_reSpawnTime += g_gameTime->GetFrameDeltaTime();
	}
	else {
		m_reSpawnTime = FLOAT_0;
	}
	if (m_reSpawnTime > RESPAWN_TIME) {
		ReSpawn();
		m_reSpawnTime = FLOAT_0;
	}
}