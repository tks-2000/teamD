#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"
#include "ExEngine.h"
//#include "Title.h"
#include "Game.h"
#include "Lighting.h"
#include "SkinModelRender.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Ball.h"

namespace {
	const Vector3 RED = { 5.0f,0.0f,0.0f };
	const Vector3 GREEN = { 0.0f,5.0f,0.0f };
	const Vector3 BLUE = { 0.0f,0.0f,5.0f };
	const Vector3 YELLOW = { 5.0f,5.0f,0.0f };
	const Vector3 COLORLESS = { 0.0f,0.0f,0.0f };
}