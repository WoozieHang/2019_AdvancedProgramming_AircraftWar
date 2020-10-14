#ifndef BULLET_H
#define BULLET_H

#include <QtWidgets>

#include "Object.h"
#include <utility>
#include <fstream>
#include <iostream>
using namespace std;

class Bullet: public Object
{
public:
	Bullet();
    Bullet(int t, int x, int y, const string &imageFile, const QPointF &dir, int power);
    pair<qreal,qreal> UpdatePosition();
    bool del();
    //物体生产函数
    static void ShootBullet(); //玩家飞机发射子弹
    static void EnemyShootBullet(); //所有敌机发射子弹
    //子弹移动
    bool MoveBullet( int NewX, int NewY); //改变子弹位置，返回子弹是否还在战场
    static void UpdateMyBullet(); //更新玩家所有子弹位置
    static void UpdateEnemyBullet(); //更新敌机所有子弹位置

private:
    QPointF dir; //子弹方向，同时也控制了子弹速度
	int power; //子弹杀伤力

friend class Scene;
friend class ProcessGame;
};

#endif // !BULLET_H

extern vector<Bullet*> mybullet;
extern vector<Bullet*> enemybullet;
