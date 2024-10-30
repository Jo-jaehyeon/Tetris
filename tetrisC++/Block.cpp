#include "Block.h"

const char Block::block[7][4][4][4] = {
	//막대모양
	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

	//네모모양
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

	//'ㅓ' 모양
	0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,

	//'ㄱ'모양
	1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,

	//'ㄴ' 모양
	1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//'Z' 모양
	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

	//'S' 모양
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
	//블럭의 초기값 설정. 각도는 무작위, 좌표는 (5, -4)
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

			if (block[shape][angle][j][i] == 1)	//블럭이 존재하는 곳에만
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("■");	//블럭 출력

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
			if (block[shape][angle][j][i] == 1)	//블럭이 존재하는 곳에만
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("  ");	//블럭 지움
			}
		}
	}
}

bool Block::strike_check(const int& angle, const int& x, const int& y)
{
	int block_dat = 0;
	for (int i = 0; i < 4; i++) // y방향
	{
		for (int j = 0; j < 4; j++) // x방향
		{
			if (((x + j) == 0) || ((x + j) == 13))	//양쪽 벽에 닿았다면
				block_dat = 1;
			else	//양쪽 벽에 닿지 않으면
			{
				if (y + i >= 0)	//화면에 출력되는 블럭 칸에 대해서만
				{
					block_dat = total_block[y + i][x + j];	//block_dat을 그 칸 주위의 total_block 값으로 바꿈
				}
				else	//화면에 출력되지 않는 칸이라면
				{
					block_dat = 0;
				}
			}
			if ((block_dat == 1) && (block[shape][angle][i][j] == 1))	//특정 칸이 벽에 닿아있고 그 칸이 칠해진 상태라면
			{
				return true;	//true 반환
			}
		}
	}
	return false;	//아니라면 true 반환
}

void Block::rotate_block()
{
	if (shape != 0)	//블럭의 모양이 막대가 아닐 때
	{
		if (strike_check((angle + 1) % 4, x, y) == true)	//회전시킨 블럭이 벽과 닿아있다면
		{
			if (strike_check((angle + 1) % 4, x - 1, y) == false)	//회전시키고 왼쪽으로 한 칸 갔을때 벽과 안 닿아있다면
			{
				erase_block(x, y);	//블럭을 지우고
				angle = (angle + 1) % 4;	//회전시키고
				x -= 1;	//왼쪽으로 한 칸 이동
				show_block(x, y);	//바뀐 블럭 출력
			}
		}
		else	//회전시킨 블럭이 벽과 닿지 않았다면
		{
			erase_block(x, y);	//블럭을 지우고
			angle = (angle + 1) % 4;	//회전시키고
			show_block(x, y);	//바뀐 블럭 출력
		}
	}
	else	//블럭의 모양이 막대일 때
	{
		switch (angle)
		{
		case 0:	//ㅣ 모양일 때
			if (strike_check(angle + 1, x - 1, y + 1) == false)	//회전시키고 왼쪽 한 칸, 아래로 한 칸 이동했을 때 벽과 닿지 않으면
			{
				erase_block(x, y);	//블럭을 지우고
				angle = 1;	//회전시키고
				x -= 1;	//왼쪽으로 한 칸
				y += 1;	//아래로 한 칸 이동
				show_block(x, y);	//바뀐 블럭 출력
				break;
			}
			else	//벽과 닿으면
			{
				if (strike_check(angle + 1, x, y + 1) == false)	//회전시키고 아래로 한칸 이동했을 때 벽과 닿지 않으면
				{
					erase_block(x, y);	//블럭을 지우고
					angle += 1;	//회전시키고
					y += 1;	//아래로 한 칸 이동
					show_block(x, y);	//바뀐 블럭 출력
				}
				else if (strike_check(angle + 1, x - 2, y + 1) == false)	//회전시키고 왼쪽으로 두 칸 아래로 한 칸 이동했을 때 벽과 닿지 않으면 
				{
					erase_block(x, y);	//블럭을 지우고
					angle += 1;	//회전시키고
					x -= 2;	//왼쪽으로 두 칸
					y += 1;	//아래로 한 칸 이동
					show_block(x, y);	//바뀐 블럭 출력
				}
				else if (strike_check(angle + 1, x - 3, y + 1) == false)	//회전시키고 왼쪽으로 세 칸 아래로 한 칸 이동했을 때 벽과 닿지 않으면
				{
					erase_block(x, y);	//블럭을 지우고
					angle += 1;	//회전시키고
					x -= 3;	//왼쪽으로 세 칸
					y += 1;	//아래로 한 칸 이동
					show_block(x, y);	//바뀐 블럭 출력
				}
				break;
			}
		case 1:	//ㅡ 모양일 때
			if (strike_check(angle + 1, x + 2, y - 1) == false)	//회전시키고 오른쪽으로 두 칸, 위로 한 칸 이동했을 때 벽과 닿지 않으면
			{
				erase_block(x, y);	//블럭을 지우고
				angle += 1;	//회전시키고
				x += 2;	//오른쪽으로 두 칸
				y -= 1;	//위로 한 칸 이동
				show_block(x, y);	//바뀐 블럭 출력
			}
			break;
		case 2:	//ㅣ 모양일 때(자연스럽게 회전시키기 위해 angle이 0일 때와 구분함.)
			if (strike_check(angle + 1, x - 2, y + 2) == false)	//회전시키고 왼쪽으로 두 칸, 아래로 두 칸 이동했을 때 벽과 닿지 않으면
			{
				erase_block(x, y);	//블럭을 지우고
				angle += 1;	//회전시키고
				x -= 2;	//왼쪽으로 두 칸
				y += 2;	//아래로 두 칸 이동
				show_block(x, y);	//바뀐 블럭 출력
				break;
			}
			else	//벽과 닿으면
			{
				if (strike_check(angle + 1, x - 3, y + 2) == false)	//회전시키고 왼쪽으로 세 칸, 아래로 두 칸 이동했을 때 벽과 닿지 않으면
				{
					erase_block(x, y);	//블럭을 지우고
					angle += 1;	//회전시키고
					x -= 3;	//왼쪽으로 세 칸
					y += 2;	//아래로 두 칸 이동
					show_block(x, y);	//바뀐 블럭 출력
				}
				else if (strike_check(angle + 1, x - 1, y + 2) == false)	//회전시키고 왼쪽으로 한 칸, 아래로 두 칸 이동했을 때 벽과 닿지 않으면
				{
					erase_block(x, y);	//블럭을 지우고
					angle += 1;	//회전시키고
					x -= 1;	//왼쪽으로 한 칸
					y += 2;	//아래로 두 칸 이동
					show_block(x, y);	//바뀐 블럭 출력
				}
				else if (strike_check(angle + 1, x, y + 2) == false)	//회전시키고 아래로 두 칸 이동했을 때 벽과 닿지 않으면
				{
					erase_block(x, y);	//블럭을 지우고
					angle += 1;	//회전시키고
					y += 2;	//아래로 두 칸 이동
					show_block(x, y);	//바뀐 블럭 출력
				}
				break;
			}
		case 3:	//ㅡ 모양일 때(자연스러운 회전을 위해 angle이 1일 때와 구분함.)
			if (strike_check(0, x + 1, y - 2) == false)	//회전시키고 오른쪽으로 한 칸, 위로 두 칸 이동했을 때 벽과 닿지 않으면
			{
				erase_block(x, y);	//블럭을 지우고
				angle = 0;	//회전시키고
				x += 1;	//오른쪽으로 한 칸
				y -= 2;	//위로 두 칸 이동
				show_block(x, y);	//바뀐 블럭 출력
			}
			break;
		}
	}
}

void Block::move_left()
{
	if (x > 1)	//x좌표가 1 초과(2 이상)이면
	{
		if (strike_check(angle, x - 1, y) == false)	//왼쪽으로 한 칸 이동했을 때 벽과 닿지 않으면
		{
			erase_block(x, y);	//블럭을 지우고
			x--;	//왼쪽으로 한 칸 이동
			show_block(x, y);	//바뀐 블럭 출력

		}
	}
}

void Block::move_right()
{
	if (x < 14)	//x좌표가 14 미만(13 이하)이면
	{
		if (strike_check(angle, x + 1, y) == false)	//오른쪽으로 한 칸 이동했을 때 벽과 닿지 않으면
		{
			erase_block(x, y);	//블럭을 지우고
			x++;	//오른쪽으로 한 칸 이동
			show_block(x, y);	//바뀐 블럭 출력

		}
	}
}

void Block::merge_block()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][angle][i][j] == 1)	//블럭의 칠해져있는 칸에 대해서만
				total_block[y + i][x + j] = 1;	//total_block의 값을 1로 바꿈(바닥에 블럭을 결합함).
		}
	}
}

int Block::move_block()
{
	erase_block(x, y);	//블럭을 지우고
	y++;	//블럭을 한 칸 아래로 이동
	if (strike_check(angle, x, y) == true)	//바닥과 닿아있다면
	{
		if (y <= 0)	//블럭의 y좌표가 0 이하라면(화면의 맨 위를 넘어서 쌓였다면)
		{
			y--;	//블럭을 한 칸 위로 이동 
			return 1;	//1 반환(게임 오버)
		}
		y--;	//블럭을 한 칸 위로 이동
		merge_block();	//바닥에 블럭 결합
		return 2;	//2 반환(바닥에 결합됐음)
	}
	return 0;	//0 반환(바닥과 닿지 않음)
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
