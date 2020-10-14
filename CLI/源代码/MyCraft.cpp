#include"Config.h"

extern Screen screen;
MyCraft my_craft;
MyCraft::MyCraft()
{
	posx =-2+(LEFT_BOUND + RIGHT_BOUND) / 2;
	posy = DOWN_BOUND - 1;
	grade = 0;
	blood = MAX_BLOOD;
}
void MyCraft::State() {
	screen.color(11);
	screen.gotoxy(STATE_POSX, STATE_POSY);
	std::cout << "ÉúÃü: ";
	screen.color(12);
	for (int i = 0; i < blood; i++)
		std::cout << "¡ö";
	std::cout<< "             ";
	screen.color(11);
	screen.gotoxy(STATE_POSX,STATE_POSY+1);
	std::cout << "µÃ·Ö: ";
	screen.color(12); 
	std::cout<< grade << "             ";
}
void MyCraft::GetGrade() {
	grade+=100;
	State();
	if (Enemy::speed >100)
		Enemy::speed -=20;
	if (EnemyBullet::speed >30)
		EnemyBullet::speed -= 5;
}

int MyCraft::Grade()const {
	return grade;
}
void MyCraft::LoseBlood() {
	blood--;
	State();
}

int MyCraft::Blood() const{
	return blood;
}
void MyCraft::Clear() {
	screen.gotoxy(posx - 1, posy);
	std::cout << "   ";
	screen.gotoxy(posx, posy - 1);
	std::cout << " ";
	screen.put_cursor();
}
void MyCraft::Show() {
	screen.color(14);
	screen.gotoxy(posx - 1, posy);
	std::cout << ">-<";
	screen.gotoxy(posx, posy - 1);
	std::cout << "|";
	screen.put_cursor();
}

MyCraft::~MyCraft()
{
	
}


void MyCraft:: Action(int Operator) {
	switch (Operator) {
		case MOVE_UP: {
			Clear();
			posy = posy<=2+UP_BOUND ? posy: posy - 1;
			Show();
			break;
		}
		case MOVE_LEFT: {
			Clear();
			posx = posx<= 4+LEFT_BOUND ? posx : posx - 2;
			Show();
			break;
		}
		case MOVE_RIGHT: {
			Clear();
			posx = posx>=RIGHT_BOUND-4 ? posx : posx+2;
			Show();
			break;
		}
		case MOVE_DOWN: {
			Clear();
			posy = posy >= DOWN_BOUND - 2 ? posy : posy + 1;
			Show();
			break;
		}
		default:break;
	}
}

void MyCraft::Attack(Bullet* b[], int& new_bullet) {
		b[new_bullet] = new Bullet(posx, posy - 2);
		new_bullet = (new_bullet + 1) % MAX_BULLET_NUM;
}

int MyCraft::GetPosX()const {
	return posx;
}

int MyCraft::GetPosY()const {
	return posy;
}

void MyCraft::Initial() {
	posx = -2 + (LEFT_BOUND + RIGHT_BOUND) / 2;
	posy = DOWN_BOUND - 1;
	my_craft.Show();
	grade = 0;
	Enemy::speed = ENEMY_INTIAL_SPEED;
	EnemyBullet::speed = 200;
	blood = MAX_BLOOD;
}

bool MyCraft::WhetherHit(int x, int y) {
	if (((posx - 1) == x || x == (posx + 1)) && ((y == posy) || (y == posy - 1))) {
		Clear();
		return 1;
	}
	else if (x == posx && (y >= posy - 1) && (y <= posy + 1)) {
		Clear();
		return 1;
	}
	else
		return 0;
}

void MyCraft::Reset() {
	Clear();
	posx = -2 + (LEFT_BOUND + RIGHT_BOUND) / 2;
	posy = DOWN_BOUND - 1;
	for (int i = 0; i < NB_SPARKLING_NUM; i++) {
		Clear();
		Sleep(NB_SPARKLING_INTERVAL);
		Show();
		Sleep(NB_SPARKLING_INTERVAL);
	}
}