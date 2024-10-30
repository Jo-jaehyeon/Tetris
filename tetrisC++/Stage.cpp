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
				Block::total_block[i][j] = 1; // 양 사이드 1로 채우기
			}
			else {
				Block::total_block[i][j] = 0;
			}
		}
	}

	for (int j = 0; j < 14; j++)			//화면의 제일 밑의 줄은 1로 채운다.
		Block::total_block[20][j] = 1;

	for (int i = 0; i < 7; i++)
	{
		block_check[i] = false;	//모든 블럭을 출력되지 않은 상태로 초기화
	}
}

int Stage::play()
{
	show_total_block();
	cur = make_block();		//현재 블럭을 만듦.
	next = make_block();	//다음 블럭을 만듦.
	show_next_block(33, 15);
	show_gamestat(35);
	for (int i = 1; 1; i++)
	{
		if (_kbhit())
		{
			int keytemp = _getch();
			if (keytemp == 224)	//확장 키 값이 들어오면
			{
				keytemp = _getch();	//키 값을 한 번 더 받음.
				switch (keytemp)
				{
				case 72:		//위 방향키를 입력했을 때 회전하기
					cur.rotate_block();
					break;
				case 75:		//왼쪽 방향키를 입력했을 때 왼쪽으로 이동
					cur.move_left();
					break;
				case 77:		//오른쪽 방향키를 입력했을 때 오른쪽으로 이동
					cur.move_right();
					break;
				case 80:		//아래 방향키를 입력했을 때 아래로 이동
					is_gameover = move_block();
					show_cur_block();
					break;
				}
			}
			if (keytemp == 32)	//스페이스바를 눌렀을때 바닥으로 이동
			{
				while (is_gameover == 0)	//블럭이 바닥에 닿지 않으면 is_gameover == 0, 바닥에 닿으면 is_gameover == 2
				{
					is_gameover = move_block();
				}
				show_cur_block();
			}
		}
		if (i % speed == 0) // i 가 speed의 배수가 될때. speed 값이 작을수록 자주 실행됨
		{
			is_gameover = move_block();
			show_cur_block();
		}
		if (check_clear())	//게임 클리어하면
		{
			return 0;
		}
		if (is_gameover == 1)	//게임 오버되면
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
	for (int i = 0; i < 21; i++) // 높이가 21
	{
		for (int j = 0; j < 14; j++) // 가로가 14
		{
			if (j == 0 || j == 13 || i == 20)		//레벨에 따라 외벽 색이 변함
			{
				SetColor((level - 1) % 6 + 1);

			}
			else {
				SetColor(DARK_GRAY);
			}
			
			gotoxy((j * 2) + Block::ab_x, i + Block::ab_y);
			if (Block::total_block[i][j] == 1)
				printf("■"); // 띄어쓰기 2개 크기, 엔터 1개크기
			else 
				printf("  ");
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
}

void Stage::show_next_block(int wx, int nbx)
{
	SetColor((level) % 6 + 1); // 레벨에 따라 다음 블럭 테두리 색깔 달라짐
	for (int i = 1; i < 7; i++)
	{
		gotoxy(wx, i);
		for (int j = 0; j < 6; j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				cout << "■ ";
			}
			else {
				cout << "  ";
			}
		}
	} // 다음 블럭 나오는 곳 테두리
	next.show_block(nbx, 1);	//다음 블럭을 다음 블럭 테두리 안에 출력
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
	if (left_lines >= 0)	//남은 줄 수가 0 이상이면
		cout << left_lines;	//left_lines 출력
	else
		cout << 0;	//0 출력
}

Block Stage::make_block()
{
	int shape;
	bool check = true;
	for (int i = 0; i < 7; i++)
	{
		check = check && block_check[i];	//block_check의 모든 값과 and 연산을 함
	}
	if (check)	//check가 true라면 == block_check의 모든 값이 true라면 == 모든 블럭이 한번씩 나왔다면
	{
		for (int i = 0; i < 7; i++)
		{
			block_check[i] = false;	//block_check를 초기화함
		}
	}
	while (1)
	{
		shape = rand() % 7;	//블럭 무작위 선택
		if (block_check[shape])	//무작위 블럭이 이미 나온 상태라면
		{
			continue;
		}
		else
		{
			block_check[shape] = true;	//그 블럭이 나왔다고 표시함
			break;
		}
	}
	return Block(shape);
}

void Stage::show_cur_block()
{
	cur.show_block(cur.getX(), cur.getY());	//현재 블럭의 위치에서 블럭을 출력
}

void Stage::erase_cur_block()
{
	cur.erase_block(cur.getX(), cur.getY());	//현재 블럭의 위치에서 블럭을 지움
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
		if (j == 13)	//한줄이 다 채워졌음
		{
			left_lines--;	//남은 줄 수 - 1
			show_total_block();
			SetColor(BLUE);
			gotoxy(1 * 2 + Block::ab_x, i + Block::ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "□";
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
	if (left_lines <= 0)	//클리어 스테이지
	{
		if (level < 10) {	//마지막 스테이지가 아니면
			level++;	//레벨을 한 단계 올림
			speed = level_data[level - 1][0];	//올린 레벨에 맞는 speed 값 가져옴
			left_lines = level_data[level - 1][1];	//올린 레벨에 맞는 줄 수 가져옴
			show_total_block();
			show_gamestat(35);
			show_next_block(33,15);
			return false;	//게임 클리어가 아니므로 false 반환
		}
		else {	//마지막 스테이지이면
			SetColor(GRAY);
			score = 0;
			return true;	//게임 클리어이므로 true 반환
		}
	}
	return false;
}



int Stage::move_block()
{
	int moving = cur.move_block();	//현재 블럭을 움직인 뒤 반환되는 값 저장
	if (moving == 2)	//게임 오버되지 않고 블럭이 바닥에 닿았을 때
	{
		cur = next;	//현재 블럭을 다음 블럭으로 바꿈
		next = make_block();	//다음 블럭을 새로 만듦.
		check_full_line();	//다 채워진 줄이 있는지 확인
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