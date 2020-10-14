#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "Plane.h"

class EnemyPlane :public Plane
{
public:
	EnemyPlane();
    EnemyPlane(int x, int y, const string &imageFile, QGraphicsScene *scene, int t, int life);
    pair<int,int> UpdatePosition();
    pair<int,int> UpdateSpecialPosition();
 static bool UpdateEnemy(); //根据敌机方向更新敌机位置
 static bool GenerateEnemy(); //生成一架敌机
 static bool GenerateSpecialEnemy(); //生成红色敌人
static bool GenerateBlueEnemy(); //生成蓝敌人
friend class Scene;
friend class ProcessGame;
};

#endif // !ENEMYPLANE_H

extern vector<EnemyPlane *> enemy;
