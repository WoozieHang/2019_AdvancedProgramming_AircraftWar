#pragma once
class Bullet{
protected:
	int posx;
	int posy;
public:
	int GetX()const;
	int GetY()const;
	static int speed;
	Bullet(int x,int y);
	Bullet();
	void Show();
	void Clear();
	bool Move();//return if remain
};

class EnemyBullet:public Bullet {
public:
	static int speed;
	EnemyBullet(int x, int y);
	void Show();
	bool Move();//return if remain
};
