#pragma once

#include <Windows.h>
#include "Border.h"
#include "Config.h"
#include "Level.h"
#include "Ball.h"
#include"Platform.h"

#define _USE_MATH_DEFINES
#include <math.h>

//------------------------------------------------------------------------------------------------------------
enum EKey_Type
{
	EKT_Left,
	EKT_Right,
	EKT_Space
};
//------------------------------------------------------------------------------------------------------------
const int Timer_ID = WM_USER + 1;
//------------------------------------------------------------------------------------------------------------
class AsEngine;
class ALevel;
class AsPlatform;
class ABall;

//------------------------------------------------------------------------------------------------------------

class AsEngine
{
public:
	AsEngine();

	void Init_Engine(HWND hwnd);
	void Draw(HDC hdc, RECT& paint_area);

	int On_Key_Down(EKey_Type key_type);
	int On_Timer();



	HWND Hwnd;
	HPEN BG_Pen;
	HBRUSH BG_Brush;
	static const int Circle_Size = 7;

private:

	ABall Ball;
	ALevel Level;
	AsPlatform Platform;
	AsBorder Border;
	
};
//------------------------------------------------------------------------------------------------------------
