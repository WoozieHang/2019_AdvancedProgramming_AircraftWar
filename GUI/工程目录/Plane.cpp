#include "Plane.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

#include"Config.h"

#include"ProcessGame.h"
using namespace std;

Plane::Plane()
{
}

Plane::Plane(int x, int y, const string &imageFile, QGraphicsScene *scene, int bld, int t):
    Object(t, imageFile)
{
    setPos(x, y);
    blood = bld;
    scene->addItem(this);
    update();
}

bool Plane::crash(int hurt)
{
    if (blood <= 0) //若已经耗尽生命值
		return false;
    else if (blood <= hurt) //若生命值此次crash后耗尽
	{
        blood-=hurt;
        //delScreen(scene);

        MyScene->RemoveObject(this);
		return false;
	}
    else{
        blood-=hurt;
		return true;
    }
}


bool Plane::MovePlane(int NewX, int NewY)
{
    //返回值为飞机是否还存活

    // 检查位置是否有变化，无变化则不移动
    if (x() == NewX && y() == NewY)
        return true;

    //我方飞机
    else if(type==ME){
        //玩家飞机合法性
        if(NewX<0 || NewX>(MyScene->width()-MyPlane::width) || NewY<0 || (NewY>MyScene->height()-MyPlane::height))
            return true;

        //玩家飞机与补给碰撞，遇到红色补给则+5血，蓝色补给则+10 蓝
        for(vector<Medicine*>::iterator it=lifesupply.begin();it!=lifesupply.end(); )
        {
            if(collidesWithItem(*it))
            {
                if((*it)->type==RED_MEDICINE){
                    blood = min(blood+BLOOD_CURE, ORIGINAL_BLOOD);
                    game.UpdateBar(MyScene->CurrentBlood,MyScene->BloodSlot,MyScene->BloodPos,+BLOOD_CURE,Qt::red);
                }
                else{
                    //补充蓝
                    blue = min(blue+BLUE_CURE, ORIGINAL_BLOOD);
                    game.UpdateBar(MyScene->CurrentBlue,MyScene->BlueSlot,MyScene->BluePos,+BLUE_CURE,Qt::blue);

                }
                MyScene->removeItem(*it);
                delete *it;
                it = lifesupply.erase(it);
            }
            else
                it++;
        }

    /* 检查是否与敌机碰撞 */
    for (vector<EnemyPlane*>::iterator it = enemy.begin(); it != enemy.end(); ){
        bool alive = true; //it所指向的飞机是否还有生命值
        if (collidesWithItem(*it))
        {
                crash(CRASH_HURT);
                alive = (*it)->crash(CRASH_HURT);
                game.UpdateBar(MyScene->CurrentBlood, MyScene->BloodSlot, MyScene->BloodPos, -CRASH_HURT, QBrush(Qt::red));
        }

        if (alive)
            it++;
        else //若飞机坠毁，则将此飞机去掉
        {
            delete *it;
            it = enemy.erase(it);
        }
     }
    }
    // 若此飞机为敌机
    else if (type == ENEMY||type == SPECIAL_ENEMY||type==BLUE_ENEMY)
    {
        //敌方飞机合法性
        if(NewX<0 || NewX>MyScene->width()|| NewY<0 || NewY>MyScene->height()){
            //如果敌方飞机从下方离开，则释放敌方飞机
            if (NewY>MyScene->height())
            {
                MyScene->RemoveObject(this);
                return false;
            }
            //否则不移动敌方飞机
            else
                return true;
        }
        else if(collidesWithItem(mycraft)){
        mycraft->crash(CRASH_HURT);
        crash(CRASH_HURT);
        game.UpdateBar(MyScene->CurrentBlood, MyScene->BloodSlot, MyScene->BloodPos, -CRASH_HURT, QBrush(Qt::red));
        }
    }

    /* 若plane存活，则更改坐标并同步屏幕 */
    if (blood > 0)
    {
        moveBy(NewX-x(), NewY-y());
        update();
    }

    return blood > 0;
}
