#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

enum {
	BLACK,      /*  0 : 까망 */
	DARK_BLUE,    /*  1 : 어두운 파랑 */
	DARK_GREEN,    /*  2 : 어두운 초록 */
	DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
	DARK_RED,    /*  4 : 어두운 빨강 */
	DARK_VOILET,  /*  5 : 어두운 보라 */
	DARK_YELLOW,  /*  6 : 어두운 노랑 */
	GRAY,      /*  7 : 회색 */
	DARK_GRAY,    /*  8 : 어두운 회색 */
	BLUE,      /*  9 : 파랑 */
	GREEN,      /* 10 : 초록 */
	SKY_BLUE,    /* 11 : 하늘 */
	RED,      /* 12 : 빨강 */
	VOILET,      /* 13 : 보라 */
	YELLOW,      /* 14 : 노랑 */
	WHITE      /* 15 : 하양 */
};

inline void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
}

inline void SetColor(int color)

{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);

}

inline void setCursorView(bool visible)
{
	CONSOLE_CURSOR_INFO cursor = { 1, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

class Block
{
private:
	int shape;
	int angle;
	int x;
	int y;
	static const char block[7][4][4][4];
public:
	static const int ab_x = 5;
	static const int ab_x2 = 80;
	static const int ab_y = 1;
	static int total_block[21][14];
	Block();
	~Block();
	Block(const int& shape);
	void show_block(const int& x, const int& y);	//진행중인 블럭을 화면에 표시한다
	void erase_block(const int& x, const int& y);	//블럭 진행의 잔상을 지우기 위한 함수
	bool strike_check(const int& angle, const int& x, const int& y);	//블럭이 화면 맨 아래에 부닥쳤는지 검사 부닥치면 1을리턴 아니면 0리턴 // 양쪽 사이드에 부닥쳤는지 인듯??
	void rotate_block();
	void move_left();
	void move_right();
	void merge_block();	//블럭이 바닥에 닿았을때 진행중인 블럭과 쌓아진 블럭을 합침
	int move_block();	//게임오버는 1을리턴 바닥에 블럭이 닿으면 2를 리턴
	int getX();
	int getY();
	int getShape();
	int getAngle();
};

