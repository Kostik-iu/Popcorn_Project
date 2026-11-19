#pragma once
#include <Windows.h>
#include "Config.h"

//------------------------------------------------------------------------------------------------------------

class AsEngine;
class ALevel;
class AsPlatform;

//------------------------------------------------------------------------------------------------------------
class ABall
{
public:

	ABall();

	void Init();
	void Draw(HDC hdc, RECT& paint_area, AsEngine* engine);
	void Move(AsEngine* engine, ALevel* level, AsPlatform* platform);

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