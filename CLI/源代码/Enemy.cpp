#include"Config.h"

extern MyCraft my_craft;
extern Screen screen;
extern EnemyBullet* eb[MAX_BULLET_NUM];
extern int first_enemy_bullet ;
extern int new_enemy_bullet;
int Enemy::speed=ENEMY_INTIAL_SPEED;

Enemy* emy[MAX_ENEMY_NUM];
int enemy_num = 0;
int first_enemy = 0;
int new_enemy = 0;
Enemy::Enemy(int x, int y) {
	posx = x;
	posy = y;
}

void Enemy::Show() {
	screen.color(15);
	screen.gotoxy(posx, posy-1);
	std::cout << "W";
	screen.gotoxy(posx-1, posy);
	std::cout << "000";
	screen.gotoxy(posx, posy+1);
	std::cout << "|";
	screen.put_cursor();
}

void Enemy::Clear() {
	if (this == NULL)
		return;
	if (posy <= DOWN_BOUND - 2) {
		screen.gotoxy(posx, posy - 1);
		std::cout << " ";
		screen.gotoxy(posx - 1, posy);
		std::cout << "   ";
		screen.gotoxy(posx, posy + 1);
		std::cout << " ";
		screen.put_cursor();
	}
	else if (posy == DOWN_BOUND - 1) {
		screen.gotoxy(posx, posy - 1);
		std::cout << " ";
		screen.gotoxy(posx - 1, posy);
		std::cout << "   ";
		screen.put_cursor();
	}
	else {
		screen.gotoxy(posx, posy - 1);
		std::cout << " ";
		screen.put_cursor();
	}
}
void Enemy::Create(Enemy* emy[],int& new_enemy) {
	int rx = LEFT_BOUND + 2 + rand() % (RIGHT_BOUND - LEFT_BOUND-3);
	int ry = UP_BOUND + 2;
	emy[new_enemy] = new Enemy(rx, ry);
	emy[new_enemy]->Show();
	new_enemy = (new_enemy + 1) % MAX_ENEMY_NUM;
	
}
bool Enemy::Move() {
	Clear();
	int r = rand() % 3;
	if (r == 0 && posx > LEFT_BOUND + 3)
		posx--;
	else if (r == 1 && posx < RIGHT_BOUND - 3)
		posx++;
	if (posy<DOWN_BOUND-2) {
		posy++;
		Show();
		//·¢Éä×Óµ¯
		if (rand() % 5 == 0) {
			eb[new_enemy_bullet] = new EnemyBullet(posx, posy + 2);
			new_enemy_bullet = (new_enemy_bullet + 1) % MAX_ENEMY_NUM;
		}
	}
	else if (posy == DOWN_BOUND-2) {
		posy++;
		screen.color(15);
		screen.gotoxy(posx, posy - 1);
		std::cout << "W";
		screen.gotoxy(posx - 1, posy);
		std::cout << "000";
		screen.put_cursor();
	}
	else if (posy == DOWN_BOUND -1) {
		posy++;
		screen.color(15);
		screen.gotoxy(posx, posy - 1);
		std::cout << "W";
		screen.put_cursor();
	}
	else return 0;
	return 1;
}

bool Enemy::WhetherHit(int x, int y) {
	if ((x >= posx - 1) && (x <= posx + 1) && (y >= posy - 1) && (y <= posy + 1)) {
		Clear();
		my_craft.GetGrade();
		return 1;
	}
	else
		return 0;
}
