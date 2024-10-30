#include "Stage.h"

const int Stage::level_data[10][2] =
{
	{40, 20}, {38, 20}, {35, 20}, {30, 20}, {25, 20}, {20, 20}, {15, 20}, {10, 20}, {6, 20}, {4, 99999}
};

Stage::Stage()
{
}

Stage::~Stage()
{
}

Stage::Stage(const int& level)
	:level(level), speed(level_data[level - 1][0]), left_lines(level_data[level - 1][1]), score(0), is_gameover(0)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if ((j == 0) || (j == 13))
			{
				Block::total_block[i][j] = 1; // �� ���̵� 1�� ä���
			}
			else {
				Block::total_block[i][j] = 0;
			}
		}
	}

	for (int j = 0; j < 14; j++)			//ȭ���� ���� ���� ���� 1�� ä���.
		Block::total_block[20][j] = 1;

	for (int i = 0; i < 7; i++)
	{
		block_check[i] = false;	//��� ���� ��µ��� ���� ���·� �ʱ�ȭ
	}
}

int Stage::play()
{
	show_total_block();
	cur = make_block();		//���� ���� ����.
	next = make_block();	//���� ���� ����.
	show_next_block(33, 15);
	show_gamestat(35);
	for (int i = 1; 1; i++)
	{
		if (_kbhit())
		{
			int keytemp = _getch();
			if (keytemp == 224)	//Ȯ�� Ű ���� ������
			{
				keytemp = _getch();	//Ű ���� �� �� �� ����.
				switch (keytemp)
				{
				case 72:		//�� ����Ű�� �Է����� �� ȸ���ϱ�
					cur.rotate_block();
					break;
				case 75:		//���� ����Ű�� �Է����� �� �������� �̵�
					cur.move_left();
					break;
				case 77:		//������ ����Ű�� �Է����� �� ���������� �̵�
					cur.move_right();
					break;
				case 80:		//�Ʒ� ����Ű�� �Է����� �� �Ʒ��� �̵�
					is_gameover = move_block();
					show_cur_block();
					break;
				}
			}
			if (keytemp == 32)	//�����̽��ٸ� �������� �ٴ����� �̵�
			{
				while (is_gameover == 0)	//���� �ٴڿ� ���� ������ is_gameover == 0, �ٴڿ� ������ is_gameover == 2
				{
					is_gameover = move_block();
				}
				show_cur_block();
			}
		}
		if (i % speed == 0) // i �� speed�� ����� �ɶ�. speed ���� �������� ���� �����
		{
			is_gameover = move_block();
			show_cur_block();
		}
		if (check_clear())	//���� Ŭ�����ϸ�
		{
			return 0;
		}
		if (is_gameover == 1)	//���� �����Ǹ�
		{
			SetColor(GRAY);
			is_gameover = 0;
			return 1;
		}

		gotoxy(77, 23);
		Sleep(15);
		gotoxy(77, 23);
	}
}

void Stage::show_total_block()
{
	for (int i = 0; i < 21; i++) // ���̰� 21
	{
		for (int j = 0; j < 14; j++) // ���ΰ� 14
		{
			if (j == 0 || j == 13 || i == 20)		//������ ���� �ܺ� ���� ����
			{
				SetColor((level - 1) % 6 + 1);

			}
			else {
				SetColor(DARK_GRAY);
			}
			
			gotoxy((j * 2) + Block::ab_x, i + Block::ab_y);
			if (Block::total_block[i][j] == 1)
				printf("��"); // ���� 2�� ũ��, ���� 1��ũ��
			else 
				printf("  ");
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
}

void Stage::show_next_block(int wx, int nbx)
{
	SetColor((level) % 6 + 1); // ������ ���� ���� �� �׵θ� ���� �޶���
	for (int i = 1; i < 7; i++)
	{
		gotoxy(wx, i);
		for (int j = 0; j < 6; j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				cout << "�� ";
			}
			else {
				cout << "  ";
			}
		}
	} // ���� �� ������ �� �׵θ�
	next.show_block(nbx, 1);	//���� ���� ���� �� �׵θ� �ȿ� ���
}

void Stage::show_gamestat(int x)
{
	static int printed_text = 0;
	SetColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(x, 7);
		cout << "STAGE";

		gotoxy(x, 9);
		cout << "SCORE";

		gotoxy(x, 12);
		cout << "LINES";


	}
	gotoxy(x + 6, 7);
	cout << level;
	gotoxy(x, 10);
	cout << score;
	gotoxy(x, 13);
	cout << "  ";
	gotoxy(x, 13);
	if (left_lines >= 0)	//���� �� ���� 0 �̻��̸�
		cout << left_lines;	//left_lines ���
	else
		cout << 0;	//0 ���
}

Block Stage::make_block()
{
	int shape;
	bool check = true;
	for (int i = 0; i < 7; i++)
	{
		check = check && block_check[i];	//block_check�� ��� ���� and ������ ��
	}
	if (check)	//check�� true��� == block_check�� ��� ���� true��� == ��� ���� �ѹ��� ���Դٸ�
	{
		for (int i = 0; i < 7; i++)
		{
			block_check[i] = false;	//block_check�� �ʱ�ȭ��
		}
	}
	while (1)
	{
		shape = rand() % 7;	//�� ������ ����
		if (block_check[shape])	//������ ���� �̹� ���� ���¶��
		{
			continue;
		}
		else
		{
			block_check[shape] = true;	//�� ���� ���Դٰ� ǥ����
			break;
		}
	}
	return Block(shape);
}

void Stage::show_cur_block()
{
	cur.show_block(cur.getX(), cur.getY());	//���� ���� ��ġ���� ���� ���
}

void Stage::erase_cur_block()
{
	cur.erase_block(cur.getX(), cur.getY());	//���� ���� ��ġ���� ���� ����
}

void Stage::check_full_line()
{
	for (int i = 0; i < 20; i++)
	{
		int j;
		for (j = 1; j < 13; j++)
		{
			if (Block::total_block[i][j] == 0)
				break;
		}
		if (j == 13)	//������ �� ä������
		{
			left_lines--;	//���� �� �� - 1
			show_total_block();
			SetColor(BLUE);
			gotoxy(1 * 2 + Block::ab_x, i + Block::ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "��";
				Sleep(10);
			}
			gotoxy(1 * 2 + Block::ab_x, i + Block::ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "  ";
				Sleep(10);
			}

			for (int k = i; k > 0; k--)
			{
				for (j = 1; j < 13; j++)
					Block::total_block[k][j] = Block::total_block[k - 1][j];
			}
			for (j = 1; j < 13; j++)
				Block::total_block[0][j] = 0;
			score += 100 + (level * 10) + (rand() % 10);
			show_gamestat(35);
		}
	}
}

bool Stage::check_clear()
{
	if (left_lines <= 0)	//Ŭ���� ��������
	{
		if (level < 10) {	//������ ���������� �ƴϸ�
			level++;	//������ �� �ܰ� �ø�
			speed = level_data[level - 1][0];	//�ø� ������ �´� speed �� ������
			left_lines = level_data[level - 1][1];	//�ø� ������ �´� �� �� ������
			show_total_block();
			show_gamestat(35);
			show_next_block(33,15);
			return false;	//���� Ŭ��� �ƴϹǷ� false ��ȯ
		}
		else {	//������ ���������̸�
			SetColor(GRAY);
			score = 0;
			return true;	//���� Ŭ�����̹Ƿ� true ��ȯ
		}
	}
	return false;
}



int Stage::move_block()
{
	int moving = cur.move_block();	//���� ���� ������ �� ��ȯ�Ǵ� �� ����
	if (moving == 2)	//���� �������� �ʰ� ���� �ٴڿ� ����� ��
	{
		cur = next;	//���� ���� ���� ������ �ٲ�
		next = make_block();	//���� ���� ���� ����.
		check_full_line();	//�� ä���� ���� �ִ��� Ȯ��
		show_total_block();
		show_next_block(33,15);
	}
	return moving;
}

int Stage::getLevel()
{
	return level;
}

int Stage::getScore()
{
	return score;
}

int Stage::getLeft()
{
	return left_lines;
}