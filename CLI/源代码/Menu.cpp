#include"Menu.h"

#pragma warning(disable:4996)
extern Screen screen;
extern MyCraft my_craft;
extern Bullet* b[MAX_BULLET_NUM];
extern int first_bullet;
extern int new_bullet;
extern EnemyBullet* eb[MAX_BULLET_NUM];
extern int first_enemy_bullet;
extern int new_enemy_bullet;
extern Enemy* emy[MAX_ENEMY_NUM];
extern int first_enemy;
extern int new_enemy;
extern int enemy_num;
clock_t start_bullet;//子弹记录check间隔
clock_t start_ebullet;
double t_bullet;
double t_ebullet;
clock_t start_enemy;
double t_enemy;

clock_t start[BUTTON_NUM];
double t[BUTTON_NUM];

bool button[BUTTON_NUM];//valid inform
bool cold_button[BUTTON_NUM];
bool P1 = 0;//current SPACE value
bool P2 = 0;//old SPACE value
Menu::Menu(){
	current = 0;
	strcpy(choice[0], "开始游戏");
	strcpy(choice[1], "退出游戏");
	Choice[0] = Start;
	Choice[1] = End;
	run_tag = 1;
}

void Menu::Initial() {

	/*screen.color(11);
	screen.gotoxy(LEFT_BOUND, UP_BOUND);
	for (int i = LEFT_BOUND; i <= RIGHT_BOUND; i += 2) {
		std::cout << "■";
	}
	for (int i = UP_BOUND + 1; i <= DOWN_BOUND; i++) {
		screen.gotoxy(LEFT_BOUND, i);
		std::cout << "■";
		screen.gotoxy(RIGHT_BOUND, i);
		std::cout << "■";
	}
	screen.gotoxy(LEFT_BOUND, DOWN_BOUND);
	for (int i = LEFT_BOUND; i <= RIGHT_BOUND; i += 2) {
		std::cout << "■";
	}*/
	screen.color(12);
	char welcome[15] = "欢迎进入游戏 !";
	for (int i = 0; welcome[i] != '\0'; i++) {
		screen.gotoxy(INDEX_X-6+2*i, (FIRST_LAY + LAST_LAY) / 2);
		std::cout << welcome[i];
		screen.put_cursor();
		Sleep(200);
	}
	Sleep(1000);
	Clear();
}

void Menu::Infor() {
	screen.color(14);
	for (int i = 0; i <CHOICE_NUM; i++) {
		screen.gotoxy(INDEX_X + 2, FIRST_LAY + i * 2);
		std::cout << choice[i];
	}
	screen.gotoxy(INDEX_X, FIRST_LAY);
	std::cout << ">";
	current = 0;
}

void Menu::ShowGuide() {
	screen.color(15);
	screen.gotoxy(RIGHT_BOUND + GUIDE_INTERVAL, UP_BOUND+1);
	std::cout << "移动：键盘上下左右";
	screen.gotoxy(RIGHT_BOUND + GUIDE_INTERVAL, UP_BOUND+2);
	std::cout << "普通射击：空格键";
	screen.gotoxy(RIGHT_BOUND + GUIDE_INTERVAL, UP_BOUND + 3);
	std::cout << "暂停：P键";
	screen.gotoxy(RIGHT_BOUND + GUIDE_INTERVAL, UP_BOUND + 4);
	std::cout << "退出：ESC";
	screen.put_cursor();
}

void Menu::OperateMenu() {
	while (run_tag) {
		//screen.gotoxy(INDEX_X, FIRST_LAY + 2 * current);
		if (_kbhit()) {
			screen.put_cursor();
			char temp = _getche();
			screen.put_cursor();
			std::cout << " ";
			if (temp == 80) {
				screen.gotoxy(INDEX_X, FIRST_LAY + 2 * current);
				std::cout << " ";
				current = (current + 1) % CHOICE_NUM;
				screen.gotoxy(INDEX_X, FIRST_LAY + 2 * current);
				std::cout << ">";
			}
			else if (temp == 72) {
				screen.gotoxy(INDEX_X, FIRST_LAY + 2 * current);
				std::cout << " ";
				current = (current + CHOICE_NUM - 1) % CHOICE_NUM;
				screen.gotoxy(INDEX_X, FIRST_LAY + 2 * current);
				std::cout << ">";
			}

			else if (temp == 13) {
				Choice[current](this);
				screen.put_cursor();
			}
		}
		screen.put_cursor();
	}
}


void Menu::Clear() {
	for (int i = UP_BOUND + 1; i < DOWN_BOUND; i++) {
		screen.gotoxy(LEFT_BOUND + 2, i);
		for (int j = LEFT_BOUND+2; j < RIGHT_BOUND; j++) {
			std::cout << " ";
		}
	}
	for (int i = UP_BOUND; i < DOWN_BOUND; i++) {
		screen.gotoxy(RIGHT_BOUND + GUIDE_INTERVAL, i);
		for (int j = RIGHT_BOUND + GUIDE_INTERVAL; j < RIGHT_BOUND+ GUIDE_INTERVAL+GUIDE_MAX_LEN; j++) {
			
			std::cout << " ";
		}
	}
}

void Menu::GameProcess() {
	while (1) {
		//响应本机的移动、响应暂停、响应子弹移动、响应子弹发射
		button[LEFT] = (bool)(GetAsyncKeyState(VK_LEFT) & 0x8000);
		button[RIGHT] = (bool)(GetAsyncKeyState(VK_RIGHT) & 0x8000);
		button[UP] = (bool)(GetAsyncKeyState(VK_UP) & 0x8000);
		button[DOWN] = (bool)(GetAsyncKeyState(VK_DOWN) & 0x8000);
		button[CONTROL] = (bool)(GetAsyncKeyState(VK_SPACE) & 0x8000);
		P1= (bool)(GetAsyncKeyState(80) & 0x8000);
		for (int i = 0; i < BUTTON_NUM; i++) {
			if (!cold_button[i])
				start[i] = clock();
			t[i] = clock() - start[i];
		}
		t_bullet = clock() - start_bullet;
		t_ebullet = clock() - start_ebullet;
		t_enemy = clock() - start_enemy;
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			GameOver();
			return;
		}
		
		if (P1&&!P2) {
			GamePause();
		}
		if (button[LEFT]&&!cold_button[LEFT]) {
			cold_button[LEFT] = 1;
			my_craft.Action(MOVE_LEFT);
		}
		if (button[RIGHT] && !cold_button[RIGHT]) {
			cold_button[RIGHT] = 1;
			my_craft.Action(MOVE_RIGHT);
		}
		if (button[UP] && !cold_button[UP]) {
			cold_button[UP] = 1;
			my_craft.Action(MOVE_UP);
		}
		if (button[DOWN] && !cold_button[DOWN]) {
			cold_button[DOWN] = 1;
			my_craft.Action(MOVE_DOWN);
		}
		if (button[CONTROL] && !cold_button[CONTROL]) {
			cold_button[CONTROL] = 1;
			my_craft.Attack(b, new_bullet);
		}
		if (t_enemy>=Enemy::speed&&(rand()%(1+enemy_num)==0)&&enemy_num < CURRENT_ENEMY_NUM) {
			Enemy::Create(emy, new_enemy);
			enemy_num++;
		}
		//check the cold time if over
		for(int i=0;i<BUTTON_NUM-1;i++)
		if (t[i] >= RESPONSE_INTERVAL) {
			cold_button[i] = 0;
		}
		if (t_bullet >= Bullet::speed&&first_bullet != new_bullet) {
			start_bullet = clock();
			//check first bullet if end
			if (b[first_bullet]->Move() == 0) {
				delete b[first_bullet];
				b[first_bullet] = NULL;
				first_bullet = (first_bullet + 1) % MAX_BULLET_NUM;
			}
			for (int i = first_bullet; i != new_bullet; i = (i + 1) % MAX_BULLET_NUM) {
				b[i]->Move();
			}
		}

		if (first_bullet != new_bullet&&enemy_num > 0)
			for (int i = first_bullet; b[i] != NULL; i = (i + 1) % MAX_BULLET_NUM) {
				for (int j = first_enemy; emy[j] != NULL; j = (j + 1) % MAX_ENEMY_NUM) {
					if (emy[j] != NULL&&emy[j]->WhetherHit(b[i]->GetX(), b[i]->GetY())) {
						emy[j]->Clear();
						delete emy[j];
						emy[j] = emy[(j + 1) % MAX_ENEMY_NUM];
						for (int k = j; emy[k] != NULL; k = (k + 1) % MAX_ENEMY_NUM) {
							emy[k] = emy[(k + 1) % MAX_ENEMY_NUM];
						}
						enemy_num--;
						new_enemy = (new_enemy + MAX_ENEMY_NUM - 1) % MAX_ENEMY_NUM;

						b[i]->Clear();
						delete b[i];
						b[i] = b[(i + 1) % MAX_BULLET_NUM];
						for (int k = i; b[k] != NULL; k = (k + 1) % MAX_BULLET_NUM) {
							b[k] = b[(k + 1) % MAX_BULLET_NUM];
						}
						new_bullet = (new_bullet + MAX_BULLET_NUM - 1) % MAX_BULLET_NUM;

						if (b[i] == NULL) {
							i = (i + MAX_BULLET_NUM - 1) % MAX_BULLET_NUM;
							break;
						}
						else {
							j = first_enemy;
						}
					}
				}
			}


		if (t_ebullet >= EnemyBullet::speed&&first_enemy_bullet != new_enemy_bullet) {
			start_ebullet = clock();
			//check first ebullet if end
			for (int i = first_enemy_bullet; i != new_enemy_bullet; i = (i + 1) % MAX_BULLET_NUM) {
				if (eb[i]->Move() == 0) {
					delete eb[i];
					eb[i] = NULL;
					for (int j = i; j != new_enemy_bullet; j = (j + 1) % MAX_BULLET_NUM)
						eb[j] = eb[(j + 1) % MAX_BULLET_NUM];
					new_enemy_bullet = (new_enemy_bullet + MAX_BULLET_NUM - 1) % MAX_BULLET_NUM;
					if (new_enemy_bullet == i)
						break;
				}
			}
		}
		if (t_enemy >= Enemy::speed&&enemy_num>0) {
			start_enemy = clock();
			//check first bullet if end
			while (first_enemy!=new_enemy) {
				if (emy[first_enemy] == NULL){
					first_enemy = (first_enemy + 1) % MAX_ENEMY_NUM;
					continue;
				}
				if (emy[first_enemy]->Move() == 0) {
					delete emy[first_enemy];
					emy[first_enemy] = NULL;
					enemy_num--;
					first_enemy = (first_enemy + 1) % MAX_ENEMY_NUM;
				}
				else break;
			}
			for (int i = (first_enemy+1)%MAX_ENEMY_NUM; i != new_enemy; i = (i + 1) % MAX_ENEMY_NUM) {
				emy[i]->Move();
			}
		}
		if (first_bullet != new_bullet&&enemy_num > 0)
			for (int i = first_bullet; b[i] != NULL; i = (i + 1) % MAX_BULLET_NUM) {
				for (int j = first_enemy; emy[j] != NULL; j = (j + 1) % MAX_ENEMY_NUM) {
					if (emy[j] != NULL&&emy[j]->WhetherHit(b[i]->GetX(), b[i]->GetY())) {
						emy[j]->Clear();
						delete emy[j];
						emy[j] = emy[(j + 1) % MAX_ENEMY_NUM];
						for (int k = j; emy[k] != NULL; k = (k + 1) % MAX_ENEMY_NUM) {
							emy[k] = emy[(k + 1) % MAX_ENEMY_NUM];
						}
						enemy_num--;
						new_enemy = (new_enemy + MAX_ENEMY_NUM - 1) % MAX_ENEMY_NUM;

						b[i]->Clear();
						delete b[i];
						b[i] = b[(i + 1) % MAX_BULLET_NUM];
						for (int k = i; b[k] != NULL; k = (k + 1) % MAX_BULLET_NUM) {
							b[k] = b[(k + 1) % MAX_BULLET_NUM];
						}
						new_bullet = (new_bullet + MAX_BULLET_NUM - 1) % MAX_BULLET_NUM;

						if (b[i] == NULL) {
							i = (i + MAX_BULLET_NUM - 1) % MAX_BULLET_NUM;
							break;
						}
						else {
							j = first_enemy;
						}
					}
				}
			}

		for (int j = first_enemy; emy[j] != NULL; j = (j + 1) % MAX_ENEMY_NUM) {
			if (emy[j] != NULL&&emy[j]->WhetherHit(my_craft.GetPosX(), my_craft.GetPosY())) {
				emy[j]->Clear();
				delete emy[j];
				emy[j] = emy[(j + 1) % MAX_ENEMY_NUM];
				for (int k = j; emy[k] != NULL; k = (k + 1) % MAX_ENEMY_NUM) {
					emy[k] = emy[(k + 1) % MAX_ENEMY_NUM];
				}
				enemy_num--;
				new_enemy = (new_enemy + MAX_ENEMY_NUM - 1) % MAX_ENEMY_NUM;
				if (my_craft.Blood()) {
					my_craft.LoseBlood();
					my_craft.Reset();
				}
				else{
					GameOver();
					return;
				}
			}
		}
		for (int j = first_enemy_bullet; eb[j] != NULL; j = (j + 1) % MAX_BULLET_NUM) {
			if (eb[j] != NULL&&my_craft.WhetherHit(eb[j]->GetX(),eb[j]->GetY())) {
				eb[j]->Clear();
				delete eb[j];
				eb[j] = eb[(j + 1) % MAX_BULLET_NUM];
				for (int k = j; eb[k] != NULL; k = (k + 1) % MAX_BULLET_NUM) {
					eb[k] = eb[(k + 1) % MAX_BULLET_NUM];
				}
				new_enemy_bullet = (new_enemy_bullet + MAX_BULLET_NUM - 1) % MAX_BULLET_NUM;
				if (my_craft.Blood() > 1) {
					my_craft.LoseBlood();
					my_craft.Reset();
				}
				else {
					GameOver();
					return;
				}
			}
		}
		//解除冷却
		if (t[CONTROL] >= SHOT_INTERVAL) {
			cold_button[CONTROL] = 0;
		}
		P2 = P1;
	}
}

void Menu::GamePause() {
	bool p = 0;//state of pause
	bool p1 = 1;//pause button 
	screen.gotoxy(RIGHT_BOUND + GUIDE_INTERVAL, GUIDE_MAX_NUM);
	
	screen.color(11);
	std::cout << "暂停";
	screen.put_cursor();
	while (1) {
   		p1 = (bool)(GetAsyncKeyState(80) & 0x8000);
		if (!p1)
			p = 1;

		if (p1&&p==1) {
			screen.gotoxy(RIGHT_BOUND + GUIDE_INTERVAL, GUIDE_MAX_NUM);
			std::cout << "    ";
			screen.put_cursor();
			return;
		}
	} 
}

void Menu::Start(Menu* m) {
	m->Clear();
	screen.color(12);
	char r[15] = "准备... 开始!";
	for (int i = 0; r[i] != '\0'; i++) {
		screen.gotoxy(INDEX_X-6+2*i, (FIRST_LAY + LAST_LAY) / 2);
		std::cout << r[i];
		screen.put_cursor();
		if (r[i] != ' ')
			Sleep(70);
		else
			Sleep(700);
	}
	Sleep(200);
	m->Clear();
	m->ShowGuide();
	my_craft.Initial();
	my_craft.State();

	first_bullet = 0;
	new_bullet = 0;
	for (int i = 0; i < MAX_BULLET_NUM; i++)
		b[i] = NULL;

	first_enemy_bullet = 0;
	new_enemy_bullet = 0;
	for (int i = 0; i < MAX_BULLET_NUM; i++)
		eb[i] = NULL;

	first_enemy = 0;
	new_enemy = 0;
	enemy_num = 0;
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
		emy[i] = NULL;

	for (int i = 0; i<BUTTON_NUM; i++)
		start[i] = clock();
	start_bullet = clock();
	start_ebullet = clock();
	start_enemy = clock();
	//response to the keyboard
	m->GameProcess();

}

void Menu::End(Menu* m) {
	m->Clear();
	screen.color(12);
	char Bye[10] = "再见 !";
	for (int i = 0; Bye[i] != '\0'; i++) {
		screen.gotoxy(INDEX_X+2*i, (FIRST_LAY + LAST_LAY) / 2);
		std::cout << Bye[i];
		screen.put_cursor();
		Sleep(200);
	}
	Sleep(1000);
	m->run_tag = 0;
}

void Menu::GameOver() {
	//show grades
	Clear();
	bool g = 0;//state of pause
	bool g1 = 1;//pause button 
	screen.gotoxy(INDEX_X, (FIRST_LAY + LAST_LAY) / 2);
	screen.color(11);
	std::cout << "得分：" << my_craft.Grade();
	screen.gotoxy(INDEX_X, 1 + (FIRST_LAY + LAST_LAY) / 2);
	std::cout << "按回车返回菜单";
	screen.put_cursor();
	while (1) {
		g1 = (bool)(GetAsyncKeyState(VK_RETURN) & 0x8000);
		if (!g1)
			g = 1;

		if (g1&&g == 1) {
			if(_kbhit())
			getchar();
			break;
		}
	}
	//exit
	Clear();
	screen.color(12);
	char Bye[12] = "游戏结束 !";
	for (int i = first_bullet; i != new_bullet; i = (i + 1) % MAX_BULLET_NUM) {
		delete b[i];
		b[i] = NULL;
	}
	for (int i = first_enemy_bullet; i != new_enemy_bullet; i = (i + 1) % MAX_BULLET_NUM) {
		delete eb[i];
		eb[i] = NULL;
	}
	for (int i = first_enemy; i != new_enemy; i = (i + 1) % MAX_ENEMY_NUM) {
		delete emy[i];
		emy[i] = NULL;
	}
	first_bullet = 0;
	new_bullet = 0;
	first_enemy_bullet = 0;
	new_enemy_bullet = 0;
	first_enemy = 0;
	new_enemy = 0;
	enemy_num = 0;
	for (int i = 0; Bye[i] != '\0'; i++) {
		screen.gotoxy(INDEX_X-4+2 * i, (FIRST_LAY + LAST_LAY) / 2);
		std::cout << Bye[i];
		screen.put_cursor();
		Sleep(200);
	}
	Sleep(1000);
	Clear();
	Infor();
}