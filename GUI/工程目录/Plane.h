#ifndef PLANE_H
#define PLANE_H

#include "Bullet.h"
#include "Object.h"
#include <QtWidgets>
#include <cstring>
#include <vector>
using namespace std;

class Plane: public Object
{
public:
	Plane();
    Plane(int x, int y, const string &imageFile, QGraphicsScene *scene, int bld, int ct);
    bool crash(int hurt); //飞机发生碰撞
    bool MovePlane(int NewX, int NewY);
protected:
    int blood; //生命值
    int blue;

friend class Scene;
friend class ProcessGame;
friend class Bullet;
};

#endif // !PLANE_H

