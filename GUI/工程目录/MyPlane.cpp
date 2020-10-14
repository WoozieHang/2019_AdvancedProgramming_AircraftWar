#include "MyPlane.h"
#include <iostream>
using namespace std;

MyPlane* mycraft;

MyPlane::MyPlane():Plane()
{
}

MyPlane::MyPlane(int x, int y, const string &imageFile, QGraphicsScene *scene, int bld, int skl,int pwr):
    Plane(x, y, imageFile, scene, bld, ME)
{
    this->blue = skl;
    this->power=pwr;
    ShootType=SINGLE_SHOOT;
    MoveX=0;
    MoveY=0;
}
