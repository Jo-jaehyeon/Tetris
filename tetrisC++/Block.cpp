#include "Block.h"

const char Block::block[7][4][4][4] = {
	//������
	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

	//�׸���
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

	//'��' ���
	0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,

	//'��'���
	1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,

	//'��' ���
	1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//'Z' ���
	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

	//'S' ���
	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0
};

int Block::total_block[21][14] = { {0, } };

Block::Block()
{
}

Block::~Block()
{
}

Block::Block(const int& shape)
	:shape(shape), angle(rand() % 4), x(5), y(-4)
	//���� �ʱⰪ ����. ������ ������, ��ǥ�� (5, -4)
{
}

void Block::show_block(const int& x, const int& y)
{
	switch (shape)
	{
	case 0:
		SetColor(RED);
		break;
	case 1:
		SetColor(BLUE);
		break;
	case 2:
		SetColor(SKY_BLUE);
		break;
	case 3:
		SetColor(WHITE);
		break;
	case 4:
		SetColor(YELLOW);
		break;
	case 5:
		SetColor(VOILET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((y + j) < 0)
				continue;

			if (block[shape][angle][j][i] == 1)	//���� �����ϴ� ������
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("��");	//�� ���

			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
}

void Block::erase_block(const int& x, const int& y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (y + j < 0)
			{
				continue;
			}
			if (block[shape][angle][j][i] == 1)	//���� �����ϴ� ������
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("  ");	//�� ����
			}
		}
	}
}

bool Block::strike_check(const int& angle, const int& x, const int& y)
{
	int block_dat = 0;
	for (int i = 0; i < 4; i++) // y����
	{
		for (int j = 0; j < 4; j++) // x����
		{
			if (((x + j) == 0) || ((x + j) == 13))	//���� ���� ��Ҵٸ�
				block_dat = 1;
			else	//���� ���� ���� ������
			{
				if (y + i >= 0)	//ȭ�鿡 ��µǴ� �� ĭ�� ���ؼ���
				{
					block_dat = total_block[y + i][x + j];	//block_dat�� �� ĭ ������ total_block ������ �ٲ�
				}
				else	//ȭ�鿡 ��µ��� �ʴ� ĭ�̶��
				{
					block_dat = 0;
				}
			}
			if ((block_dat == 1) && (block[shape][angle][i][j] == 1))	//Ư�� ĭ�� ���� ����ְ� �� ĭ�� ĥ���� ���¶��
			{
				return true;	//true ��ȯ
			}
		}
	}
	return false;	//�ƴ϶�� true ��ȯ
}

void Block::rotate_block()
{
	if (shape != 0)	//���� ����� ���밡 �ƴ� ��
	{
		if (strike_check((angle + 1) % 4, x, y) == true)	//ȸ����Ų ���� ���� ����ִٸ�
		{
			if (strike_check((angle + 1) % 4, x - 1, y) == false)	//ȸ����Ű�� �������� �� ĭ ������ ���� �� ����ִٸ�
			{
				erase_block(x, y);	//���� �����
				angle = (angle + 1) % 4;	//ȸ����Ű��
				x -= 1;	//�������� �� ĭ �̵�
				show_block(x, y);	//�ٲ� �� ���
			}
		}
		else	//ȸ����Ų ���� ���� ���� �ʾҴٸ�
		{
			erase_block(x, y);	//���� �����
			angle = (angle + 1) % 4;	//ȸ����Ű��
			show_block(x, y);	//�ٲ� �� ���
		}
	}
	else	//���� ����� ������ ��
	{
		switch (angle)
		{
		case 0:	//�� ����� ��
			if (strike_check(angle + 1, x - 1, y + 1) == false)	//ȸ����Ű�� ���� �� ĭ, �Ʒ��� �� ĭ �̵����� �� ���� ���� ������
			{
				erase_block(x, y);	//���� �����
				angle = 1;	//ȸ����Ű��
				x -= 1;	//�������� �� ĭ
				y += 1;	//�Ʒ��� �� ĭ �̵�
				show_block(x, y);	//�ٲ� �� ���
				break;
			}
			else	//���� ������
			{
				if (strike_check(angle + 1, x, y + 1) == false)	//ȸ����Ű�� �Ʒ��� ��ĭ �̵����� �� ���� ���� ������
				{
					erase_block(x, y);	//���� �����
					angle += 1;	//ȸ����Ű��
					y += 1;	//�Ʒ��� �� ĭ �̵�
					show_block(x, y);	//�ٲ� �� ���
				}
				else if (strike_check(angle + 1, x - 2, y + 1) == false)	//ȸ����Ű�� �������� �� ĭ �Ʒ��� �� ĭ �̵����� �� ���� ���� ������ 
				{
					erase_block(x, y);	//���� �����
					angle += 1;	//ȸ����Ű��
					x -= 2;	//�������� �� ĭ
					y += 1;	//�Ʒ��� �� ĭ �̵�
					show_block(x, y);	//�ٲ� �� ���
				}
				else if (strike_check(angle + 1, x - 3, y + 1) == false)	//ȸ����Ű�� �������� �� ĭ �Ʒ��� �� ĭ �̵����� �� ���� ���� ������
				{
					erase_block(x, y);	//���� �����
					angle += 1;	//ȸ����Ű��
					x -= 3;	//�������� �� ĭ
					y += 1;	//�Ʒ��� �� ĭ �̵�
					show_block(x, y);	//�ٲ� �� ���
				}
				break;
			}
		case 1:	//�� ����� ��
			if (strike_check(angle + 1, x + 2, y - 1) == false)	//ȸ����Ű�� ���������� �� ĭ, ���� �� ĭ �̵����� �� ���� ���� ������
			{
				erase_block(x, y);	//���� �����
				angle += 1;	//ȸ����Ű��
				x += 2;	//���������� �� ĭ
				y -= 1;	//���� �� ĭ �̵�
				show_block(x, y);	//�ٲ� �� ���
			}
			break;
		case 2:	//�� ����� ��(�ڿ������� ȸ����Ű�� ���� angle�� 0�� ���� ������.)
			if (strike_check(angle + 1, x - 2, y + 2) == false)	//ȸ����Ű�� �������� �� ĭ, �Ʒ��� �� ĭ �̵����� �� ���� ���� ������
			{
				erase_block(x, y);	//���� �����
				angle += 1;	//ȸ����Ű��
				x -= 2;	//�������� �� ĭ
				y += 2;	//�Ʒ��� �� ĭ �̵�
				show_block(x, y);	//�ٲ� �� ���
				break;
			}
			else	//���� ������
			{
				if (strike_check(angle + 1, x - 3, y + 2) == false)	//ȸ����Ű�� �������� �� ĭ, �Ʒ��� �� ĭ �̵����� �� ���� ���� ������
				{
					erase_block(x, y);	//���� �����
					angle += 1;	//ȸ����Ű��
					x -= 3;	//�������� �� ĭ
					y += 2;	//�Ʒ��� �� ĭ �̵�
					show_block(x, y);	//�ٲ� �� ���
				}
				else if (strike_check(angle + 1, x - 1, y + 2) == false)	//ȸ����Ű�� �������� �� ĭ, �Ʒ��� �� ĭ �̵����� �� ���� ���� ������
				{
					erase_block(x, y);	//���� �����
					angle += 1;	//ȸ����Ű��
					x -= 1;	//�������� �� ĭ
					y += 2;	//�Ʒ��� �� ĭ �̵�
					show_block(x, y);	//�ٲ� �� ���
				}
				else if (strike_check(angle + 1, x, y + 2) == false)	//ȸ����Ű�� �Ʒ��� �� ĭ �̵����� �� ���� ���� ������
				{
					erase_block(x, y);	//���� �����
					angle += 1;	//ȸ����Ű��
					y += 2;	//�Ʒ��� �� ĭ �̵�
					show_block(x, y);	//�ٲ� �� ���
				}
				break;
			}
		case 3:	//�� ����� ��(�ڿ������� ȸ���� ���� angle�� 1�� ���� ������.)
			if (strike_check(0, x + 1, y - 2) == false)	//ȸ����Ű�� ���������� �� ĭ, ���� �� ĭ �̵����� �� ���� ���� ������
			{
				erase_block(x, y);	//���� �����
				angle = 0;	//ȸ����Ű��
				x += 1;	//���������� �� ĭ
				y -= 2;	//���� �� ĭ �̵�
				show_block(x, y);	//�ٲ� �� ���
			}
			break;
		}
	}
}

void Block::move_left()
{
	if (x > 1)	//x��ǥ�� 1 �ʰ�(2 �̻�)�̸�
	{
		if (strike_check(angle, x - 1, y) == false)	//�������� �� ĭ �̵����� �� ���� ���� ������
		{
			erase_block(x, y);	//���� �����
			x--;	//�������� �� ĭ �̵�
			show_block(x, y);	//�ٲ� �� ���

		}
	}
}

void Block::move_right()
{
	if (x < 14)	//x��ǥ�� 14 �̸�(13 ����)�̸�
	{
		if (strike_check(angle, x + 1, y) == false)	//���������� �� ĭ �̵����� �� ���� ���� ������
		{
			erase_block(x, y);	//���� �����
			x++;	//���������� �� ĭ �̵�
			show_block(x, y);	//�ٲ� �� ���

		}
	}
}

void Block::merge_block()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][angle][i][j] == 1)	//���� ĥ�����ִ� ĭ�� ���ؼ���
				total_block[y + i][x + j] = 1;	//total_block�� ���� 1�� �ٲ�(�ٴڿ� ���� ������).
		}
	}
}

int Block::move_block()
{
	erase_block(x, y);	//���� �����
	y++;	//���� �� ĭ �Ʒ��� �̵�
	if (strike_check(angle, x, y) == true)	//�ٴڰ� ����ִٸ�
	{
		if (y <= 0)	//���� y��ǥ�� 0 ���϶��(ȭ���� �� ���� �Ѿ �׿��ٸ�)
		{
			y--;	//���� �� ĭ ���� �̵� 
			return 1;	//1 ��ȯ(���� ����)
		}
		y--;	//���� �� ĭ ���� �̵�
		merge_block();	//�ٴڿ� �� ����
		return 2;	//2 ��ȯ(�ٴڿ� ���յ���)
	}
	return 0;	//0 ��ȯ(�ٴڰ� ���� ����)
}

int Block::getX()
{
	return x;
}

int Block::getY()
{
	return y;
}

int Block::getShape()
{
	return shape;
}

int Block::getAngle()
{
	return angle;
}
