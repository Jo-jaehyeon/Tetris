#pragma once
#include "Block.h"

class Stage
{
	/*
	*    Member Function
	*/
public:
	Stage();
	~Stage();
	Stage(const int& level);
	int				play();
	void			show_total_block();		//쌓여져있는 블럭을 화면에 표시한다.
	void			show_next_block(int wx, int nbx);
	void			show_gamestat(int x);

	Block			make_block();			//Block 객체를 생성하여 블럭을 만든다.
	void			show_cur_block();		//진행중인 블럭을 화면에 표시한다
	void			erase_cur_block();		//블럭 진행의 잔상을 지우기 위한 함수
	void			check_full_line();
	bool			check_clear();
	
	int				move_block();
	int				getLevel();
	int				getScore();
	int				getLeft();
	

	/*
	*    Member Variable
	*/
private:
	int					level;				//레벨
	int					speed;				//블럭이 떨어지는 속도. 작을수록 빠름.
	int					left_lines;			//남은 줄 수
	int					score;				//점수
	bool				block_check[7];	//블럭이 나왔는지 확인하기 위한 배열.
	Block				cur;				//현재 블럭을 저장하는 객체
	Block				next;				//다음 블럭을 저장하는 객체
	int					is_gameover;		//게임 오버 여부를 저장하는 변수
	static const int	level_data[10][2];
};

