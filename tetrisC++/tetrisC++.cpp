#include "Stage.h"

void show_logo();	//�ΰ� ���
Stage input_data();	//������ ���ùް�, �׿� �´� Stage ��ü ��ȯ
void show_gameclear();	//���� Ŭ���� ���� ���
void show_gameover();	//���� ���� ���� ���

int main()
{
	srand((unsigned)time(NULL));	//rand�� �ʱⰪ ����
	setCursorView(false);
	show_logo();
	while (true)
	{
		Stage stage = input_data();	//�Է¹��� ������ Stage ��ü�� ����.
		int play = stage.play();	//0�� ������ 10������������ Ŭ������ ��, 1�� ������ ���� ������ ��
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
	cout << "������������������������������������������������������������������������������������������";
	Sleep(100);
	gotoxy(13, 4);
	cout << "�� �ߡߡߡߡ�   �ߡߡ�    �ߡߡߡߡ�   �ߡߡ�     ��    �ߡߡ�   ��";
	Sleep(100);
	gotoxy(13, 5);
	cout << "��   ��     ��        ��     ��  ��    ��    ��  ��  ��";
	Sleep(100);
	gotoxy(13, 6);
	cout << "��   ��     �ߡߡ�      ��     �ߡߡ�     ��     ��    ��";
	Sleep(100);
	gotoxy(13, 7);
	cout << "��   ��     ��        ��     ��  ��    ��   ��  ��   ��";
	Sleep(100);
	gotoxy(13, 8);
	cout << "��   ��     �ߡߡ�      ��     ��   ��   ��    �ߡ�    ��";
	Sleep(100);
	gotoxy(13, 9);
	cout << "������������������������������������������������������������������������������������������";

	gotoxy(28, 20);
	cout << "Please Press Any Key~!";

	for (int i = 0; i >= 0; i++)
	{
		if (i % 40 == 0) // 40�� ���
		{


			for (int j = 0; j < 5; j++)
			{
				gotoxy(17, 14 + j);
				cout << "                                                          "; // �����ֱ� 17�� �ٲٴ� �������� ��.


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
		Sleep(30); // 0.03�� Sleep�߿� �Է°� �����°� �����ϴµ� 40�� -> 1.2��
	}

	_getch();
	system("cls");
}

Stage input_data()
{
	double i = 0;	//�Ҽ��� �Է��� ���� �־ double�� ������.
	SetColor(GRAY);
	gotoxy(10, 7);
	cout << "����������������������<GAME KEY>������������������";
	Sleep(50);
	gotoxy(10, 8);
	cout << "�� UP   : Rotate Block        ��";
	Sleep(50);
	gotoxy(10, 9);
	cout << "�� DOWN : Move One-Step Down  ��";
	Sleep(50);
	gotoxy(10, 10);
	cout << "�� SPACE: Move Bottom Down    ��";
	Sleep(50);
	gotoxy(10, 11);
	cout << "�� LEFT : Move Left           ��";
	Sleep(50);
	gotoxy(10, 12);
	cout << "�� RIGHT: Move Right          ��";
	Sleep(50);
	gotoxy(10, 13);
	cout << "������������������������������������������������������������";


	while (i < 1 || i > 10 || i - (int)i != 0)	//������ ����ų� �Ҽ��� �Է��ϸ� �ٽ� �Է¹���.
	{
		gotoxy(10, 3);
		cout << "Select Start level[1-10]:       \b\b\b\b\b\b\b ";
		cin >> i;
		while (getchar() != '\n');
	}
	Stage stage(i);	//������ �Է¹޾��� �� i�� ������ ������ Stage ��ü�� ����.
	system("cls");
	return stage;
}

void show_gameclear()
{
	SetColor(GREEN);
	gotoxy(15, 8);
	cout << "��������������������������������������������������������";
	gotoxy(15, 9);
	cout << "��**************************��";
	gotoxy(15, 10);
	cout << "��*        GAME CLEAR!     *��";
	gotoxy(15, 11);
	cout << "��**************************��";
	gotoxy(15, 12);
	cout << "��������������������������������������������������������";
	fflush(stdin);
	Sleep(1000);

	_getch();
	system("cls");
}

void show_gameover()
{
	SetColor(RED);
	gotoxy(15, 8);
	cout << "��������������������������������������������������������";
	gotoxy(15, 9);
	cout << "��**************************��";
	gotoxy(15, 10);
	cout << "��*        GAME OVER       *��";
	gotoxy(15, 11);
	cout << "��**************************��";
	gotoxy(15, 12);
	cout << "��������������������������������������������������������";
	fflush(stdin);
	Sleep(1000);

	_getch();
	system("cls");
}