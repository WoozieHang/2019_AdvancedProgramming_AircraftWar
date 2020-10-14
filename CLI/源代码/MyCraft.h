#pragma once
#include"Config.h"
class MyCraft
{
	int posx;
	int posy;
	int grade;
	int blood;
public:
	MyCraft();
	~MyCraft();
	void Initial();
	int GetPosX()const;
	int GetPosY()const;
	int Blood()const;
	void LoseBlood();
	int Grade()const;
	void GetGrade();
	void State();
	void Show();
	void Clear();
	void Action(int Operator);
	void Attack( Bullet*b[], int &new_bullet);
	bool WhetherHit(int x, int y);
	void Reset();
};

