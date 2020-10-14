#include"Config.h"

void Screen::gotoxy(int x, int y)//位置函数
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Screen::color(int a)//颜色函数
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
void Screen::put_cursor() {
	gotoxy(TOTAL_RIGHT_BOUND, DOWN_BOUND/2);
}
Screen screen;