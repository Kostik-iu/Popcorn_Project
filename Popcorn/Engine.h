#pragma once

#include <Windows.h>
#include "Border.h"
#include "Config.h"
#include "Level.h"

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


//------------------------------------------------------------------------------------------------------------
class ABall
{
public:

	ABall();
	void Init();
	void Draw(HDC hdc, RECT& paint_area, AsEngine *engine);
	void Move(AsEngine *engine, ALevel *level, AsPlatform *platform);

	double Ball_Direction;
	static const int Ball_Size = AsConfig::Ball_Size;

	HPEN  Ball_Pen;
	HBRUSH  Ball_Brush;

private:
	int Ball_X_Pos, Ball_Y_Pos;
	double Ball_Speed;

	HWND Hwnd;
	RECT Ball_Rect, Prev_Ball_Rect;

};
//------------------------------------------------------------------------------------------------------------


class AsPlatform
{
public:
	AsPlatform();

	void Init();
	void Redraw(AsEngine* engine);
	void Draw(HDC hdc, AsEngine* engine, RECT& paint_area);

	static const int Y_Pos = 185;

	int Platform_X_Step;
	int X_Pos;
	int Platform_Width;

private:

	static const int Platform_Height = 7;

	int Inner_Width;

	HPEN Highlight_Pen, Platform_Circle_Pen, Platform_Inner_Pen;
	HBRUSH Platform_Circle_Brush, Platform_Inner_Brush;
	RECT Platform_Rect, Prev_Platform_Rect;
};

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
