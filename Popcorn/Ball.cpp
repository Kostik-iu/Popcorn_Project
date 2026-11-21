#include "Ball.h"
#include "Engine.h"

ABall::ABall()
	: Ball_Direction(M_PI - M_PI_4), Ball_Pen(nullptr), Ball_Brush(nullptr), Ball_X_Pos(20), Ball_Y_Pos(170), Ball_Speed(3.0), Hwnd(nullptr), Ball_Rect{}, Prev_Ball_Rect{}
{

}


//-----------------------------------------------------------------------------------------------------------

void ABall::Init()
{
	AsConfig::Create_Pen_Brush(255, 255, 255, Ball_Pen, Ball_Brush);

}


//------------------------------------------------------------------------------------------------------------
void ABall::Draw(HDC hdc, RECT& paint_area, AsEngine* engine)
{
	RECT intersection_rect;

	if (!IntersectRect(&intersection_rect, &paint_area, &Ball_Rect))
		return;

	// 1. Очищаем фон
	SelectObject(hdc, engine->BG_Pen);
	SelectObject(hdc, engine->BG_Brush);

	Ellipse(hdc, Prev_Ball_Rect.left, Prev_Ball_Rect.top, Prev_Ball_Rect.right - 1, Prev_Ball_Rect.bottom - 1);

	// 2. Рисуем шарик
	SelectObject(hdc, Ball_Pen);
	SelectObject(hdc, Ball_Brush);

	Ellipse(hdc, Ball_Rect.left, Ball_Rect.top, Ball_Rect.right - 1, Ball_Rect.bottom - 1);
}
//------------------------------------------------------------------------------------------------------------



void ABall::Move(AsEngine* engine, ALevel* level, AsPlatform* platform)
{
	int next_x_pos, next_y_pos;
	int max_x_pos = ALevel::Max_X_Pos - Ball_Size;
	int Y_Pos = AsPlatform::Y_Pos - Ball_Size;

	Prev_Ball_Rect = Ball_Rect;

	next_x_pos = Ball_X_Pos + (int)(Ball_Speed * cos(Ball_Direction));
	next_y_pos = Ball_Y_Pos - (int)(Ball_Speed * sin(Ball_Direction));

	// Корректируем позицию при отражении от рамки
	if (next_x_pos < AsBorder::Border_X_Offset)
	{
		next_x_pos = ALevel::Level_X_Offset - (next_x_pos - ALevel::Level_X_Offset);
		Ball_Direction = M_PI - Ball_Direction;
	}

	if (next_y_pos < AsBorder::Border_Y_Offset)
	{
		next_y_pos = AsBorder::Border_Y_Offset - (next_y_pos - AsBorder::Border_Y_Offset);
		Ball_Direction = -Ball_Direction;
	}

	if (next_x_pos > max_x_pos)
	{
		next_x_pos = max_x_pos - (next_x_pos - max_x_pos);
		Ball_Direction = M_PI - Ball_Direction;
	}

	if (next_y_pos > ALevel::Max_Y_Pos)
	{
		next_y_pos = ALevel::Max_Y_Pos - (next_y_pos - ALevel::Max_Y_Pos);
		Ball_Direction = M_PI + (M_PI - Ball_Direction);
	}

	// Корректируем позицию при отражении от платформы
	if (next_y_pos > Y_Pos)
	{
		if (next_x_pos >= platform->X_Pos && next_x_pos <= platform->X_Pos + platform->Platform_Width)
		{
			next_y_pos = Y_Pos - (next_y_pos - Y_Pos);
			Ball_Direction = M_PI + (M_PI - Ball_Direction);
		}
	}

	// Корректируем позицию при отражении от кирпичей
	level->Check_Level_Brick_Hit (next_x_pos, next_y_pos, Ball_Direction);

	// Смещаем шарик
	Ball_X_Pos = next_x_pos;
	Ball_Y_Pos = next_y_pos;

	Ball_Rect.left = Ball_X_Pos * AsConfig::Global_Scale;
	Ball_Rect.top = Ball_Y_Pos * AsConfig::Global_Scale;
	Ball_Rect.right = Ball_Rect.left + Ball_Size * AsConfig::Global_Scale;
	Ball_Rect.bottom = Ball_Rect.top + Ball_Size * AsConfig::Global_Scale;

	InvalidateRect(engine->Hwnd, &Prev_Ball_Rect, FALSE);
	InvalidateRect(engine->Hwnd, &Ball_Rect, FALSE);
}
//------------------------------------------------------------------------------------------------------------