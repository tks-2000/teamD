#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"
#include "ExEngine.h"
#include "SoundEngine.h"
#include "SoundSource.h"
#include "Bgm.h"
#include "Se.h"
#include "Title.h"
#include "Menu.h"
#include "Game.h"
#include "GameDirector.h"
#include "SceneChange.h"
#include "Timer.h"
#include "GameUI.h"
#include "Score.h"
#include "Lighting.h"
#include "SkinModelRender.h"
#include "SpriteRender.h"
#include "FontRender.h"
#include "Player.h"
#include "PlayerAction.h"
#include "PlayerCollide.h"
#include "PlayerEffect.h"
#include "PlayerMove.h"
#include "PlayerReinforcement.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Ball.h"
#include "Objects.h"
#include "Box.h"
#include "Item.h"
#include "Sky.h"
#include "Result.h"

class FontRender;
class GameDirector;
class Menu;

namespace {

	const int MAX_PLAYER_NUM = 4;
	const int MIN_PLAYER_NUM = 1;

	const float FLOAT_0 = 0.0f;
	const float FLOAT_1 = 1.0f;
	const float FLOAT_2 = 2.0f;
	const float FLOAT_01 = 0.1f;
	const float FLOAT_MINUS_1 = -1.0f;

	const Vector3 RED = { 3.0f,1.0f,1.0f };
	const Vector3 GREEN = { 1.0f,3.0,1.0f };
	const Vector3 BLUE = { 1.0f,1.0f,3.0f };
	const Vector3 YELLOW = { 2.0f,2.0f,1.0f };
	const Vector3 WHITE = { 2.0f,2.0f,2.0f };
	const Vector3 COLORLESS = { 0.0f,0.0f,0.0f };

	const Vector3 HEMISPHERE_LIGHT_SKYCOLOR_START = { 0.3f,0.3f,0.3f };
	const Vector3 HEMISPHERE_LIGHT_SKYCOLOR_HALF = { 0.5f,0.1f,0.1f };
	const Vector3 HEMISPHERE_LIGHT_SKYCOLOR_END = { -0.7f,-0.7f,0.1f };

	const Vector3 HEMISPHERE_LIGHT_GROUNDCOLOR_START = { 0.3f,0.3f,0.3f };
	const Vector3 HEMISPHERE_LIGHT_GROUNDCOLOR_HALF = { 0.5f,0.1f,0.1f };
	const Vector3 HEMISPHERE_LIGHT_GROUNDCOLOR_END = { -0.7f,-0.7f,0.1f };

	const Vector3 HEMISPHERE_LIGHT_SKYCOLOR_SP_START = { 0.1f,-0.7f,0.1f };
	const Vector3 HEMISPHERE_LIGHT_SKYCOLOR_SP_HALF = { -0.5f,-0.5f,-0.5f };
	const Vector3 HEMISPHERE_LIGHT_SKYCOLOR_SP_END = { -0.1f,-0.5f,-0.5f };

	const Vector3 HEMISPHERE_LIGHT_GROUNDCOLOR_SP_START = { -0.5f,-1.0f,-0.5f };
	const Vector3 HEMISPHERE_LIGHT_GROUNDCOLOR_SP_HALF = { -2.0f,-2.0f,-2.0f };
	const Vector3 HEMISPHERE_LIGHT_GROUNDCOLOR_SP_END = { 0.7f,-0.7f,-0.7f };

	const int PRIORITY_VERYLOW = 0;
	const int PRIORITY_LOW = 1;
	const int PRIORITY_NORMAL = 2;
	const int PRIORITY_HIGH = 3;
	const int PRIORITY_VERYHIGH = 4;

	const char* TITLE_NAME = "Title";
	const char* GAME_DIRECTOR_NAME = "GameDirector";
	const char* SCENE_CHANGE_NAME = "SceneChange";
	const char* MENU_NAME = "Menu";
	const char* GAME_NAME = "Game";
	const char* TIMER_NAME = "Timer";
	const char* GAME_UI_NAME = "GameUI";
	const char* SCORE_NAME = "Score";
	const char* LIGHTING_NAME = "Lighting";
	const char* PLAYER_NAME[MAX_PLAYER_NUM] = { "Player1","Player2","Player3","Player4" };
	const char* PLAYER_ACTION_NAME[MAX_PLAYER_NUM] = { "PlayerAction1","PlayerAction2","PlayerAction3","PlayerAction4" };
	const char* PLAYER_COLLID_NAME[MAX_PLAYER_NUM] = { "PlayerCollide1","PlayerCollide2","PlayerCollide3","PlayerCollide4" };
	const char* PLAYER_EFFECT_NAME[MAX_PLAYER_NUM] = { "PlayerEffect1","PlayerEffect2" ,"PlayerEffect3" ,"PlayerEffect4" };
	const char* PLAYER_MOVE_NAME[MAX_PLAYER_NUM] = { "PlayerMove1","PlayerMove2","PlayerMove3","PlayerMove4" };
	const char* PLAYER_REINFORCEMENT_NAME[MAX_PLAYER_NUM] = { "PlayerReinforcement1","PlayerReinforcement2","PlayerReinforcement3","PlayerReinforcement4" };
	const char* GAME_CAMERA_NAME = "GameCamera";
	const char* BACK_GROUND_NAME = "BackGround";
	const char* BALL_NAME = "Ball";
	const char* SKY_NAME = "Sky";
	const char* OBJECTS_NAME = "Objects";
	const char* BOX_NAME = "Box";
	const char* ITEM_NAME = "Item";
	const char* RESULT_NAME = "Result";
	const char* BGM_NAME = "Bgm";
	const char* SE_NAME = "Se";

	const char* UNITYCHAN_MODEL = "Assets/modelData/unityChan.tkm";

	//ユニティちゃんモデルごとのファイルパス
	const char* UNITYCHAN_MULTI_FILEPATH[4] =
	{	{"Assets/modelData/utc_red.tkm"},		//1p 赤
		{"Assets/modelData/utc_blue.tkm"},		//2p 青
		{"Assets/modelData/utc_yellow.tkm"},	//3p 黄
		{"Assets/modelData/utc_green.tkm"}		//4p 緑
	};
}