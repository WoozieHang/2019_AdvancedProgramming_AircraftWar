#pragma once
#include<iostream>
#include<windows.h>
#include"Bullet.h"
#include"Screen.h"
#include<Windows.h>
#include<time.h>
#include"Enemy.h"
#include"MyCraft.h"
#include<string>
#include<conio.h>
#include<random>
#define CHOICE_NUM 2
#define LEFT_BOUND 0
#define RIGHT_BOUND 66
#define UP_BOUND 0
#define DOWN_BOUND 30
#define FIRST_LAY 3+(UP_BOUND+DOWN_BOUND)/3
#define LAST_LAY FIRST_LAY+(CHOICE_NUM-1)*2
#define INDEX_X 4+(LEFT_BOUND+RIGHT_BOUND)/3
#define ORIGINAL_X (LEFT_BOUND+RIGHT_BOUND)/3
#define ORIGINAL_Y DOWN_BOUND-1
#define MAX_CH_LEN 50
#define GUIDE_INTERVAL 5
#define GUIDE_MAX_LEN 20
#define GUIDE_MAX_NUM 7
#define TOTAL_RIGHT_BOUND RIGHT_BOUND+53
#define MOVE_UP 72
#define MOVE_LEFT 75
#define MOVE_RIGHT 77
#define MOVE_DOWN 80
#define SHOT 's'
#define MAX_BULLET_NUM 10000
#define RESPONSE_INTERVAL 100
#define SHOT_INTERVAL 70
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define CONTROL 4
#define BUTTON_NUM 5
#define MAX_ENEMY_NUM 10000
#define STATE_POSX RIGHT_BOUND+GUIDE_INTERVAL
#define STATE_POSY GUIDE_MAX_NUM+1
#define CURRENT_ENEMY_NUM 7
#define MAX_BLOOD 3
#define NB_SPARKLING_INTERVAL 200
#define NB_SPARKLING_NUM 3
#define ENEMY_INTIAL_SPEED 1000
//only for debugging
/*
screen.gotoxy(RIGHT_BOUND+3, 0);
std::cout <<"only for debugging: "<<(int)temp<<" ";
*/

//for color 
/*
for (int i = 0; i < 20; i++) {
		screen.color(i);
		screen.gotoxy(RIGHT_BOUND+3, 5+i);
		std::cout << "■";
	}
*/
//既要记录子弹num、敌人num，同时消亡时也要依次前移遍历数组
