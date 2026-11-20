#include "Engine.h"
#include "Config.h"
#include "Level.h"


//------------------------------------------------------------------------------------------------------------

AsEngine::AsEngine()
	: Hwnd(nullptr), BG_Pen(nullptr), BG_Brush(nullptr), Ball{}, Level{}, Platform{}, Border{}

{

}
//------------------------------------------------------------------------------------------------------------
void AsEngine::Init_Engine(HWND hwnd)
{// Настройка игры при старте

	Hwnd = hwnd;


	AsConfig::Create_Pen_Brush(15, 63, 31, BG_Pen, BG_Brush);
	

	Ball.Init();
	Level.Init();
	Platform.Init();
	Border.Init();
	
	Platform.Redraw(this);

	SetTimer(Hwnd, Timer_ID, 50, 0);
}
//------------------------------------------------------------------------------------------------------------
void AsEngine::Draw(HDC hdc, RECT &paint_area)
{// Отрисовка экрана игры

	

		Level.Draw(hdc,paint_area);

		Platform.Draw(hdc, this, paint_area);

	//int i;

	//for (i = 0; i < 16; i++)
	//{
	//	Draw_Brick_Letter(hdc, 20 + i * Cell_Width * Global_Scale, 100, EBT_Blue, ELT_O, i);
	//	Draw_Brick_Letter(hdc, 20 + i * Cell_Width * Global_Scale, 130, EBT_Red, ELT_O, i);
	//}

		Ball.Draw(hdc, paint_area, this);

		Border.Draw_Bounds(hdc, paint_area, BG_Pen, BG_Brush);
}
//------------------------------------------------------------------------------------------------------------
int AsEngine::On_Key_Down(EKey_Type key_type)
{
	switch (key_type)
	{
	case EKT_Left:
		Platform.X_Pos -= Platform.Platform_X_Step;

		if (Platform.X_Pos <= AsBorder::Border_X_Offset)
			Platform.X_Pos = AsBorder::Border_X_Offset;

		Platform.Redraw(this);
		break;

	case EKT_Right:
		Platform.X_Pos += Platform.Platform_X_Step;

		if (Platform.X_Pos >= ALevel::Max_X_Pos - Platform.Platform_Width + 1)
			Platform.X_Pos = ALevel::Max_X_Pos - Platform.Platform_Width + 1;

		Platform.Redraw(this);
		break;

	case EKT_Space:
		break;
	}

	return 0;
}
//------------------------------------------------------------------------------------------------------------
int AsEngine::On_Timer()
{
	Ball.Move(this, &Level, &Platform);

	return 0;
}
//------------------------------------------------------------------------------------------------------------






