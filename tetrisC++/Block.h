#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

enum {
	BLACK,      /*  0 : ��� */
	DARK_BLUE,    /*  1 : ��ο� �Ķ� */
	DARK_GREEN,    /*  2 : ��ο� �ʷ� */
	DARK_SKY_BLUE,  /*  3 : ��ο� �ϴ� */
	DARK_RED,    /*  4 : ��ο� ���� */
	DARK_VOILET,  /*  5 : ��ο� ���� */
	DARK_YELLOW,  /*  6 : ��ο� ��� */
	GRAY,      /*  7 : ȸ�� */
	DARK_GRAY,    /*  8 : ��ο� ȸ�� */
	BLUE,      /*  9 : �Ķ� */
	GREEN,      /* 10 : �ʷ� */
	SKY_BLUE,    /* 11 : �ϴ� */
	RED,      /* 12 : ���� */
	VOILET,      /* 13 : ���� */
	YELLOW,      /* 14 : ��� */
	WHITE      /* 15 : �Ͼ� */
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
	void show_block(const int& x, const int& y);	//�������� ���� ȭ�鿡 ǥ���Ѵ�
	void erase_block(const int& x, const int& y);	//�� ������ �ܻ��� ����� ���� �Լ�
	bool strike_check(const int& angle, const int& x, const int& y);	//���� ȭ�� �� �Ʒ��� �δ��ƴ��� �˻� �δ�ġ�� 1������ �ƴϸ� 0���� // ���� ���̵忡 �δ��ƴ��� �ε�??
	void rotate_block();
	void move_left();
	void move_right();
	void merge_block();	//���� �ٴڿ� ������� �������� ���� �׾��� ���� ��ħ
	int move_block();	//���ӿ����� 1������ �ٴڿ� ���� ������ 2�� ����
	int getX();
	int getY();
	int getShape();
	int getAngle();
};

