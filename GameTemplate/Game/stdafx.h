#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"
#include "ExEngine.h"
#include "Game.h"
#include "Lighting.h"
#include "SkinModelRender.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Ball.h"

float DistanceToCalculation(Vector3 vec1, Vector3 vec2)
{
	Vector3 vec3 = vec1 - vec2;
	return vec3.Length();
}