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
	void			show_total_block();		//�׿����ִ� ���� ȭ�鿡 ǥ���Ѵ�.
	void			show_next_block(int wx, int nbx);
	void			show_gamestat(int x);

	Block			make_block();			//Block ��ü�� �����Ͽ� ���� �����.
	void			show_cur_block();		//�������� ���� ȭ�鿡 ǥ���Ѵ�
	void			erase_cur_block();		//�� ������ �ܻ��� ����� ���� �Լ�
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
	int					level;				//����
	int					speed;				//���� �������� �ӵ�. �������� ����.
	int					left_lines;			//���� �� ��
	int					score;				//����
	bool				block_check[7];	//���� ���Դ��� Ȯ���ϱ� ���� �迭.
	Block				cur;				//���� ���� �����ϴ� ��ü
	Block				next;				//���� ���� �����ϴ� ��ü
	int					is_gameover;		//���� ���� ���θ� �����ϴ� ����
	static const int	level_data[10][2];
};

