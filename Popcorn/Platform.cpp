#include "Platform.h"
#include"Engine.h"


//------------------------------------------------------------------------------------------------------------


AsPlatform::AsPlatform()
	: Platform_X_Step(AsConfig::Global_Scale * 2), X_Pos(AsBorder::Border_X_Offset), Platform_Width(28), Inner_Width(21), Highlight_Pen(nullptr), Platform_Circle_Pen(nullptr), Platform_Inner_Pen(nullptr),
	Platform_Circle_Brush(nullptr), Platform_Inner_Brush(nullptr), Platform_Rect{}, Prev_Platform_Rect{}
{
}

//------------------------------------------------------------------------------------------------------------
void AsPlatform::Init()
{
	Highlight_Pen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));

	AsConfig::Create_Pen_Brush(151, 0, 0, Platform_Circle_Pen, Platform_Circle_Brush);
	AsConfig::Create_Pen_Brush(0, 128, 192, Platform_Inner_Pen, Platform_Inner_Brush);


}

//------------------------------------------------------------------------------------------------------------
void AsPlatform::Redraw(AsEngine* engine)
{
	Prev_Platform_Rect = Platform_Rect;

	Platform_Rect.left = X_Pos * AsConfig::Global_Scale;
	Platform_Rect.top = Y_Pos * AsConfig::Global_Scale;
	Platform_Rect.right = Platform_Rect.left + Platform_Width * AsConfig::Global_Scale;
	Platform_Rect.bottom = Platform_Rect.top + Platform_Height * AsConfig::Global_Scale;

	InvalidateRect(engine->Hwnd, &Prev_Platform_Rect, FALSE);
	InvalidateRect(engine->Hwnd, &Platform_Rect, FALSE);
}
//------------------------------------------------------------------------------------------------------------
void AsPlatform::Draw(HDC hdc, AsEngine* engine, RECT& paint_area)
{// Рисуем платформу

	int x = X_Pos;
	int y = Y_Pos;

	RECT intersection_rect;

	if (!IntersectRect(&intersection_rect, &paint_area, &Platform_Rect))
		return;


	SelectObject(hdc, engine->BG_Pen);
	SelectObject(hdc, engine->BG_Brush);

	Rectangle(hdc, Prev_Platform_Rect.left, Prev_Platform_Rect.top, Prev_Platform_Rect.right, Prev_Platform_Rect.bottom);

	// 1. Рисуем боковые шарики
	SelectObject(hdc, Platform_Circle_Pen);
	SelectObject(hdc, Platform_Circle_Brush);

	Ellipse(hdc, x * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + AsEngine::Circle_Size) * AsConfig::Global_Scale, (y + AsEngine::Circle_Size) * AsConfig::Global_Scale);
	Ellipse(hdc, (x + Inner_Width) * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + AsEngine::Circle_Size + Inner_Width) * AsConfig::Global_Scale, (y + AsEngine::Circle_Size) * AsConfig::Global_Scale);

	// 2. Рисуем блик
	SelectObject(hdc, Highlight_Pen);

	Arc(hdc, (x + 1) * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + AsEngine::Circle_Size - 1) * AsConfig::Global_Scale, (y + AsEngine::Circle_Size - 1) * AsConfig::Global_Scale,
		(x + 1 + 1) * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + 1) * AsConfig::Global_Scale, (y + 1 + 2) * AsConfig::Global_Scale);

	// 3. Рисуем среднюю часть
	SelectObject(hdc, Platform_Inner_Pen);
	SelectObject(hdc, Platform_Inner_Brush);

	RoundRect(hdc, (x + 4) * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + 4 + Inner_Width - 1) * AsConfig::Global_Scale, (y + 1 + 5) * AsConfig::Global_Scale, 3 * AsConfig::Global_Scale, 3 * AsConfig::Global_Scale);
}

//------------------------------------------------------------------------------------------------------------