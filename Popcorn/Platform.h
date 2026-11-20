#pragma once

#include <Windows.h>


//------------------------------------------------------------------------------------------------------------

class AsEngine;


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