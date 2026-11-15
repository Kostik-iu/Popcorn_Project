#pragma once

#include <Windows.h>
#include "Border.h"

#define _USE_MATH_DEFINES
#include <math.h>

//------------------------------------------------------------------------------------------------------------
enum ELetter_Type
{
	ELT_None,

	ELT_O
};
//------------------------------------------------------------------------------------------------------------
enum EBrick_Type
{
	EBT_None,
	EBT_Red,
	EBT_Blue
};
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
	static const int Ball_Size = 4;

	HPEN  Ball_Pen;
	HBRUSH  Ball_Brush;

private:
	int Ball_X_Pos, Ball_Y_Pos;
	double Ball_Speed;

	HWND Hwnd;
	RECT Ball_Rect, Prev_Ball_Rect;

};
//------------------------------------------------------------------------------------------------------------

class ALevel
{
public:
	void Init();
	void Check_Level_Brick_Hit(int& next_y_pos, double& ball_direction);
	void Draw(HDC hdc, RECT &paint_area);


	static const int Level_X_Offset = 8;
	static const int Level_Y_Offset = 6;
	static const int Cell_Width = 16;
	static const int Cell_Height = 8;
	static const int Level_Width = 12;  // Ширина уровня в ячейках
	static const int Level_Height = 14;  // Высота уровня в ячейках
	static const int Max_X_Pos = Level_X_Offset + Cell_Width * Level_Width;
	static const int Max_Y_Pos = 199 - ABall::Ball_Size;

	RECT Level_Rect;
	HBRUSH Brick_Red_Brush, Brick_Blue_Brush;
	HPEN Brick_Red_Pen, Brick_Blue_Pen;
	HPEN Letter_Pen;


private:

	void Draw_Brick(HDC hdc, int x, int y, EBrick_Type brick_type);
	void Set_Brick_Letter_Colors(bool is_switch_color, HPEN& front_pen, HBRUSH& front_brush, HPEN& back_pen, HBRUSH& back_brush);
	void Draw_Brick_Letter(HDC hdc, int x, int y, EBrick_Type brick_type, ELetter_Type letter_type, int rotation_step);


	static const int Brick_Width = 15;
	static const int Brick_Height = 7;

	

	
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
