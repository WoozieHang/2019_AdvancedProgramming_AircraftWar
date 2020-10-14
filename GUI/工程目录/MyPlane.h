#ifndef MYPLANE_H
#define MYPLANE_H

#include "Plane.h"
#include"Config.h"
class MyPlane:public Plane
{
    static const int height=102;
    static const int width=72;
public:
	MyPlane();
    MyPlane(int x, int y, const string &imageFile, QGraphicsScene *scene, int bld, int skl,int pwr);
    bool NotMove(){
        return (MoveX==0)&&(MoveY==0);
    }

    void SetMoveX(int x){
        MoveX=x;
    }

    void SetMoveY(int y){
        MoveY=y;
    }

    void SetMove(int x,int y){
        MoveX=x;
        MoveY=y;
    }

private:

    int power;
    int ShootType; //射击模式
    int MoveX;
    int MoveY;

friend class Scene;
friend class ProcessGame;
friend class EnemyPlane;
friend class Plane;
friend class Bullet;
};

#endif // !MYPLANE_H

extern MyPlane* mycraft;
