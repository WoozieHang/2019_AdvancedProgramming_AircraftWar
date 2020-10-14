#pragma once
class Enemy
{
	int posx;
	int posy;
public:
	static int speed;
	static void Create(Enemy* emy[],int& new_enemy);
	Enemy(int x, int y);
	void Show();
	void Clear();
	bool Move();
	bool WhetherHit(int x, int y);
};

