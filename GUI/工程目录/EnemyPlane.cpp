#include "EnemyPlane.h"
#include"MyPlane.h"
#include"Config.h"
#include <cstdlib>
#include"ProcessGame.h"
vector<EnemyPlane *> enemy;

EnemyPlane::EnemyPlane()
{
}

EnemyPlane::EnemyPlane(int x, int y, const string &imageFile, QGraphicsScene *scene, int t, int life):
    Plane(x, y, imageFile, scene, life, t)
{
}

pair<int,int> EnemyPlane::UpdatePosition()
{
    return make_pair(x(), y()+2);
}

pair<int,int> EnemyPlane::UpdateSpecialPosition()
{
    if(mycraft->x()>this->x()&&(mycraft->x()-this->x())>10)
        return make_pair(x()+10, y()+10);
    else if(mycraft->x()>this->x())
        return make_pair(x()+5, y()+15);
    else if(mycraft->x()<this->x()&&(this->x()-mycraft->x())>10)
        return make_pair(x()-10, y()+10);
    else if(mycraft->x()<this->x())
        return make_pair(x()-5, y()+15);
    else
         return make_pair(x(), y()+18);

}

bool EnemyPlane::UpdateEnemy()
{
    /* 若当前敌机少于1，则自动生成3个敌机 */
    if (enemy.size() < 1)
    {
        for (int i = 0; i < 3; i++)
            GenerateEnemy();
    }

    /* 所有敌机移动位置 */
    for (vector<EnemyPlane*>::iterator it = enemy.begin(); it != enemy.end(); )
    {
        pair<int, int> pos;
        if((*it)->type==ENEMY||(*it)->type==SPECIAL_ENEMY)
            pos= (*it)->UpdatePosition();
        else pos=(*it)->UpdateSpecialPosition();

        if ((*it)->MovePlane(pos.first, pos.second))
            it++;
        else
            it = enemy.erase(it);
    }

    return mycraft->blood > 0;
}


bool EnemyPlane::GenerateEnemy()
{
    //返回是否生成成功
    /* 随机在第一行生成敌机 */
    QPixmap pixmap(QPixmap(QString::fromStdString(MyScene->EnemyImage)));
    int x = rand() % (int)MyScene->width(); //敌机最左端位置
    int i;
    for(i=0;i<50;i++)
    {
        bool legal = true;
        //不能和其他飞机重合
        for(vector<EnemyPlane*>::iterator it=enemy.begin();it!=enemy.end();++it)
        {
            if((*it)->sceneBoundingRect().intersects(QRectF(x, 0, pixmap.width(), pixmap.height())))
            {
                legal = false;
                break;
            }
        }

        if(legal)
            break;
        else
            x = rand() % (int)MyScene->width();
    }
    /* 若生成100次随机都未能找到合适的位置则退出 */
    if(i==50)
        return false;

    /* 新增敌机 */
    EnemyPlane *newenemy = new EnemyPlane(x, 0, MyScene->EnemyImage, MyScene, ENEMY, ENEMY_BLOOD);
    enemy.push_back(newenemy);
    return true;
}
bool EnemyPlane::GenerateSpecialEnemy()
{
    /* 随机在第一行生成敌机 */
    QPixmap pixmap(QPixmap(QString::fromStdString(MyScene->SpecialEnemyImage)));
    int x = rand() % (int)MyScene->width(); //敌机最左端位置
    int i;
    for(i=0;i<50;i++)
    {
        bool legal = true; //此位置是否合法
        //不能和其他飞机重合
        for(vector<EnemyPlane*>::iterator it=enemy.begin();it!=enemy.end();++it)
        {
            if((*it)->sceneBoundingRect().intersects(QRectF(x, 0, pixmap.width(), pixmap.height())))
            {
                legal = false;
                break;
            }
        }

        if(legal)
            break;
        else
            x = rand() % (int)MyScene->width();
    }

    /* 若生成100次随机都未能找到合适的位置则退出 */
    if(i==50)
        return false;

    /* 新增敌机 */
    EnemyPlane *newenemy = new EnemyPlane(x, 0, MyScene->SpecialEnemyImage, MyScene, SPECIAL_ENEMY, SPECIAL_ENEMY_BLOOD);
    enemy.push_back(newenemy);
    return true;
}

bool EnemyPlane::GenerateBlueEnemy()
{
    /* 随机在第一行生成敌机 */
    QPixmap pixmap(QPixmap(QString::fromStdString(MyScene->BlueEnemyImage)));
    int x = rand() % (int)MyScene->width(); //敌机最左端位置
    int i;
    for(i=0;i<50;i++)
    {
        bool legal = true; //此位置是否合法
        //不能和其他飞机重合
        for(vector<EnemyPlane*>::iterator it=enemy.begin();it!=enemy.end();++it)
        {
            if((*it)->sceneBoundingRect().intersects(QRectF(x, 0, pixmap.width(), pixmap.height())))
            {
                legal = false;
                break;
            }
        }

        if(legal)
            break;
        else
            x = rand() % (int)MyScene->width();
    }

    /* 若生成100次随机都未能找到合适的位置则退出 */
    if(i==50)
        return false;

    /* 新增敌机 */
    EnemyPlane *newenemy = new EnemyPlane(x, 0, MyScene->BlueEnemyImage, MyScene, BLUE_ENEMY, BLUE_ENEMY_BLOOD);
    enemy.push_back(newenemy);
    return true;
}
