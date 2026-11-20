#include "Border.h"
#include "Config.h"

//------------------------------------------------------------------------------------------------------------

AsBorder::AsBorder()
	: Border_Blue_Pen(nullptr), Border_White_Pen(nullptr), Border_Blue_Brush(nullptr), Border_White_Brush(nullptr)
{

}

void AsBorder::Init()
{

	AsConfig::Create_Pen_Brush(85, 255, 255, Border_Blue_Pen, Border_Blue_Brush);
	AsConfig::Create_Pen_Brush(255, 255, 255, Border_White_Pen, Border_White_Brush);

}

//------------------------------------------------------------------------------------------------------------

void AsBorder::Draw_Bounds(HDC hdc, RECT& paint_area, HPEN bg_pen, HBRUSH bg_brush)
{// Рисует рамку уровня

	int i;

	// 1. Линия слева
	for (i = 0; i < 50; i++)
		Draw_Element(hdc, 2, 1 + i * 4, false, bg_pen, bg_brush);

	// 2. Линия справаd
	for (i = 0; i < 50; i++)
		Draw_Element(hdc, 201, 1 + i * 4, false, bg_pen, bg_brush);

	// 3. Линия сверху
	for (i = 0; i < 50; i++)
		Draw_Element(hdc, 3 + i * 4, 0, true, bg_pen, bg_brush);

	//------------------------------------------------------------------------------------------------------------

}

void AsBorder::Draw_Element(HDC hdc, int x, int y, bool top_boder, HPEN bg_pen, HBRUSH bg_brush)
{// Рисует элемент рамки уровня

 // Основная линия
	SelectObject(hdc, Border_Blue_Pen);
	SelectObject(hdc, Border_Blue_Brush);

	if (top_boder)
		Rectangle(hdc, x * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + 4) * AsConfig::Global_Scale, (y + 4) * AsConfig::Global_Scale);
	else
		Rectangle(hdc, (x + 1) * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + 4) * AsConfig::Global_Scale, (y + 4) * AsConfig::Global_Scale);

	// Белая кайма
	SelectObject(hdc, Border_White_Pen);
	SelectObject(hdc, Border_White_Brush);

	if (top_boder)
		Rectangle(hdc, x * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + 4) * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale);
	else
		Rectangle(hdc, x * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + 1) * AsConfig::Global_Scale, (y + 4) * AsConfig::Global_Scale);

	// Перфорация
	SelectObject(hdc, bg_pen);
	SelectObject(hdc, bg_brush);

	if (top_boder)
		Rectangle(hdc, (x + 2) * AsConfig::Global_Scale, (y + 2) * AsConfig::Global_Scale, (x + 3) * AsConfig::Global_Scale, (y + 3) * AsConfig::Global_Scale);
	else
		Rectangle(hdc, (x + 2) * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + 3) * AsConfig::Global_Scale, (y + 2) * AsConfig::Global_Scale);
}
//------------------------------------------------------------------------------------------------------------


