#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"
#include "ExEngine.h"
//#include "Title.h"
#include "Menu.h"
#include "Game.h"
#include "GameDirector.h"
#include "Timer.h"
#include "GameUI.h"
#include "Score.h"
#include "Lighting.h"
#include "SkinModelRender.h"
#include "SpriteRender.h"
#include "FontRender.h"
#include "Player.h"
#include "PlayerEffect.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Ball.h"
#include "Objects.h"
#include "Box.h"
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

	const Vector3 RED = { 5.0f,0.0f,0.0f };
	const Vector3 GREEN = { 0.0f,5.0f,0.0f };
	const Vector3 BLUE = { 0.0f,0.0f,5.0f };
	const Vector3 YELLOW = { 5.0f,5.0f,0.0f };
	const Vector3 COLORLESS = { 0.0f,0.0f,0.0f };

	const char* TITLE_NAME = "Title";
	const char* GAME_DIRECTOR_NAME = "GameDirector";
	const char* MENU_NAME = "Menu";
	const char* GAME_NAME = "Game";
	const char* TIMER_NAME = "Timer";
	const char* GAME_UI_NAME = "GameUI";
	const char* SCORE_NAME = "Score";
	const char* LIGHTING_NAME = "Lighting";
	const char* PLAYER_NAME[MAX_PLAYER_NUM] = { "Player1","Player2","Player3","Player4" };
	const char* PLAYER_EFFECT_NAME = "PlayerEffect";
	const char* GAME_CAMERA_NAME = "GameCamera";
	const char* BACK_GROUND_NAME = "BackGround";
	const char* BALL_NAME = "Ball";
	const char* OBJECTS_NAME = "Objects";
	const char* BOX_NAME = "Box";
	const char* RESULT_NAME = "Result";

	const char* UNITYCHAN_MODEL = "Assets/modelData/unityChan.tkm";
}