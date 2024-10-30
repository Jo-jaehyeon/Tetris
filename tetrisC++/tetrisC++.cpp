#include "Stage.h"

void show_logo();	//로고 출력
Stage input_data();	//레벨을 선택받고, 그에 맞는 Stage 객체 반환
void show_gameclear();	//게임 클리어 문구 출력
void show_gameover();	//게임 오버 문구 출력

int main()
{
	srand((unsigned)time(NULL));	//rand의 초기값 설정
	setCursorView(false);
	show_logo();
	while (true)
	{
		Stage stage = input_data();	//입력받은 레벨의 Stage 객체를 받음.
		int play = stage.play();	//0을 받으면 10스테이지까지 클리어한 것, 1을 받으면 게임 오버된 것
		if (play == 0)
		{
			show_gameclear();
			break;
		}
		else if (play == 1)
		{
			show_gameover();
		}
	}
}

void show_logo()
{
	gotoxy(13, 3);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
	Sleep(100);
	gotoxy(13, 4);
	cout << "┃ ◆◆◆◆◆   ◆◆◆    ◆◆◆◆◆   ◆◆◆     ◆    ◆◆◆   ┃";
	Sleep(100);
	gotoxy(13, 5);
	cout << "┃   ◆     ◆        ◆     ◆  ◆    ◆    ◆  ◆  ┃";
	Sleep(100);
	gotoxy(13, 6);
	cout << "┃   ◆     ◆◆◆      ◆     ◆◆◆     ◆     ◆    ┃";
	Sleep(100);
	gotoxy(13, 7);
	cout << "┃   ◆     ◆        ◆     ◆  ◆    ◆   ◆  ◆   ┃";
	Sleep(100);
	gotoxy(13, 8);
	cout << "┃   ◆     ◆◆◆      ◆     ◆   ◆   ◆    ◆◆    ┃";
	Sleep(100);
	gotoxy(13, 9);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";

	gotoxy(28, 20);
	cout << "Please Press Any Key~!";

	for (int i = 0; i >= 0; i++)
	{
		if (i % 40 == 0) // 40의 배수
		{


			for (int j = 0; j < 5; j++)
			{
				gotoxy(17, 14 + j);
				cout << "                                                          "; // 지워주기 17로 바꾸니 정상으로 됨.


			}
			Block block1(rand() % 7);
			block1.show_block(6, 14);
			Block block2(rand() % 7);
			block2.show_block(12, 14);
			Block block3(rand() % 7);
			block3.show_block(19, 14);
			Block block4(rand() % 7);
			block4.show_block(24, 14);
		}
		if (_kbhit())
			break;
		Sleep(30); // 0.03초 Sleep중에 입력값 들어오는것 방자하는듯 40번 -> 1.2초
	}

	_getch();
	system("cls");
}

Stage input_data()
{
	double i = 0;	//소수를 입력할 수도 있어서 double로 선언함.
	SetColor(GRAY);
	gotoxy(10, 7);
	cout << "┏━━━━━━━━━━<GAME KEY>━━━━━━━━┓";
	Sleep(50);
	gotoxy(10, 8);
	cout << "┃ UP   : Rotate Block        ┃";
	Sleep(50);
	gotoxy(10, 9);
	cout << "┃ DOWN : Move One-Step Down  ┃";
	Sleep(50);
	gotoxy(10, 10);
	cout << "┃ SPACE: Move Bottom Down    ┃";
	Sleep(50);
	gotoxy(10, 11);
	cout << "┃ LEFT : Move Left           ┃";
	Sleep(50);
	gotoxy(10, 12);
	cout << "┃ RIGHT: Move Right          ┃";
	Sleep(50);
	gotoxy(10, 13);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";


	while (i < 1 || i > 10 || i - (int)i != 0)	//범위를 벗어나거나 소수를 입력하면 다시 입력받음.
	{
		gotoxy(10, 3);
		cout << "Select Start level[1-10]:       \b\b\b\b\b\b\b ";
		cin >> i;
		while (getchar() != '\n');
	}
	Stage stage(i);	//정수를 입력받았을 때 i를 레벨로 가지는 Stage 객체를 만듦.
	system("cls");
	return stage;
}

void show_gameclear()
{
	SetColor(GREEN);
	gotoxy(15, 8);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
	gotoxy(15, 9);
	cout << "┃**************************┃";
	gotoxy(15, 10);
	cout << "┃*        GAME CLEAR!     *┃";
	gotoxy(15, 11);
	cout << "┃**************************┃";
	gotoxy(15, 12);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
	fflush(stdin);
	Sleep(1000);

	_getch();
	system("cls");
}

void show_gameover()
{
	SetColor(RED);
	gotoxy(15, 8);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
	gotoxy(15, 9);
	cout << "┃**************************┃";
	gotoxy(15, 10);
	cout << "┃*        GAME OVER       *┃";
	gotoxy(15, 11);
	cout << "┃**************************┃";
	gotoxy(15, 12);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
	fflush(stdin);
	Sleep(1000);

	_getch();
	system("cls");
}