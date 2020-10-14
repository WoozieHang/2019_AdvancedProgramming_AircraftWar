#include"Config.h"

extern Screen screen;
Bullet* b[MAX_BULLET_NUM];
EnemyBullet* eb[MAX_BULLET_NUM];
int first_bullet=0;
int new_bullet=0;
int first_enemy_bullet = 0;
int new_enemy_bullet = 0;

int Bullet::speed = 60;//30ms per move
Bullet::Bullet() {
	
}
Bullet::Bullet(int x,int y) {
	if (LEFT_BOUND < x&&x < RIGHT_BOUND&&y>UP_BOUND&&y<DOWN_BOUND) {
		posx = x;
		posy = y;
		Show();
	}
}
void Bullet::Show() {
	screen.color(15);
	screen.gotoxy(posx, posy);
	std::cout << ".";
	screen.put_cursor();
}
void Bullet::Clear(){
	screen.gotoxy(posx, posy);
	std::cout << " ";
	screen.put_cursor();
}
bool Bullet::Move() {
	if (posy > UP_BOUND+1) {
		Clear();
		posy--;
		Show();
		return 1;
	}
	else {
		Clear();
		return 0;
	}
}

int Bullet::GetX()const {
	return posx;
}

int Bullet::GetY()const {
	return posy;
}


int EnemyBullet::speed = 200;//700ms per move
EnemyBullet::EnemyBullet(int x, int y){
	if (LEFT_BOUND < x&&x < RIGHT_BOUND&&y>UP_BOUND&&y<DOWN_BOUND) {
		posx = x;
		posy = y;
		Show();
	}
}
void EnemyBullet::Show() {
	screen.color(15);
	screen.gotoxy(posx, posy);
	std::cout << "*";
	screen.put_cursor();
}

bool EnemyBullet::Move() {
	if (posy< DOWN_BOUND-1) {
		Clear();
		posy++;
		Show();
		return 1;
	}
	else {
		Clear();
		return 0;
	}
}
