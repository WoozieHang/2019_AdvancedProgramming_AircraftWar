#include "Bullet.h"
#include <iostream>
using namespace std;
#include"ProcessGame.h"
vector<Bullet*> mybullet;
vector<Bullet*> enemybullet;
Bullet::Bullet()
{
}

Bullet::Bullet(int t, int x, int y, const string &imageFile, const QPointF &dir, int power):
    Object(t, imageFile)
{
    setPos(x, y);
	this->dir = dir;
	this->power = power;
}

pair<qreal, qreal> Bullet::UpdatePosition()
{
    return make_pair(x()+dir.x(), y()+dir.y());
}

bool Bullet::del()
{
    power=0;
    //delScreen(scene);
    MyScene->RemoveObject(this);

    return 0;
}

void Bullet::UpdateMyBullet()
{
    for (vector<Bullet*>::iterator it = mybullet.begin(); it != mybullet.end(); )
    {
        pair<int, int> pos = (*it)->UpdatePosition();
        if ((*it)->MoveBullet(pos.first, pos.second))
            it++;
        else
        {
            delete *it;
            it = mybullet.erase(it);
        }
    }
}
void Bullet::ShootBullet()
{
    /* 玩家飞机发出新子弹，新子弹在玩家飞机炮管外的位置 */
    if( mycraft->ShootType==SINGLE_SHOOT)
    {
        Bullet *bullet = new Bullet(MY_BULLET, mycraft->x()+40, mycraft->y()-38,
                                    MyScene->MyBulletImage, QPointF(0,-3), mycraft->power);
        mybullet.push_back(bullet);
        MyScene->addItem(bullet);
    }
    else if( mycraft->ShootType==MANY_SHOOT)
    {
        Bullet *bullet1 = new Bullet(MY_BULLET, mycraft->x()+40, mycraft->y()-38,
                                    MyScene->MyBulletImage, QPointF(-3,-3), mycraft->power);
        mybullet.push_back(bullet1);
        bullet1->setRotation(-45);
        MyScene->addItem(bullet1);

        Bullet *bullet2 = new Bullet(MY_BULLET,mycraft->x()+40, mycraft->y()-38,
                                    MyScene->MyBulletImage, QPointF(0,-3), mycraft->power);
        mybullet.push_back(bullet2);
        MyScene->addItem(bullet2);

        Bullet *bullet3 = new Bullet(MY_BULLET, mycraft->x()+40, mycraft->y()-38,
                                    MyScene->MyBulletImage, QPointF(3,-3), mycraft->power);
        mybullet.push_back(bullet3);
        bullet3->setRotation(45);
        MyScene->addItem(bullet3);
    }
}
void Bullet::EnemyShootBullet()
{
    /* 仍存活的敌机发出新子弹，新子弹在敌机炮管外的位置 */
    for (vector<EnemyPlane*>::iterator it = enemy.begin(); it != enemy.end(); it++)
        if ((*it)->blood > 0)
        {
            if((*it)->type==ENEMY)
            {
                Bullet *bullet = new Bullet(ENEMY_BULLET, (*it)->x()+(*it)->pixmap().width()/2, (*it)->y()+(*it)->pixmap().height()-15,
                                        MyScene->EnemyBulletImage, QPointF(0,1), ENEMY_POWER);
                enemybullet.push_back(bullet);
                MyScene->addItem(bullet);
            }
            else if((*it)->type==SPECIAL_ENEMY)
            {
                Bullet *bullet0 = new Bullet(SPECIAL_ENEMY_BULLET, (*it)->x()+(*it)->pixmap().width()/2, (*it)->y()+(*it)->pixmap().height()-15,
                                     MyScene->SpecialEnemyBulletImage, QPointF(0,1), SPECIAL_ENEMY_POWER);
                enemybullet.push_back(bullet0);
                MyScene->addItem(bullet0);

                Bullet *bullet1 = new Bullet(SPECIAL_ENEMY_BULLET, (*it)->x()+(*it)->pixmap().width()/2, (*it)->y()+(*it)->pixmap().height()-15,
                                     MyScene->SpecialEnemyBulletImage, QPointF(-1,1), SPECIAL_ENEMY_POWER);
                bullet1->setRotation(45);
                enemybullet.push_back(bullet1);
                MyScene->addItem(bullet1);

                Bullet *bullet2 = new Bullet(SPECIAL_ENEMY_BULLET, (*it)->x()+(*it)->pixmap().width()/2, (*it)->y()+(*it)->pixmap().height()-15,
                                     MyScene->SpecialEnemyBulletImage, QPointF(1,1), SPECIAL_ENEMY_POWER);
                bullet2->setRotation(-45);
                enemybullet.push_back(bullet2);
                MyScene->addItem(bullet2);

                Bullet *bullet3 = new Bullet(SPECIAL_ENEMY_BULLET, (*it)->x()+(*it)->pixmap().width()/2, (*it)->y()+(*it)->pixmap().height()-15,
                                     MyScene->SpecialEnemyBulletImage, QPointF(-2,1), SPECIAL_ENEMY_POWER);
                bullet3->setRotation(63);
                enemybullet.push_back(bullet3);
                MyScene->addItem(bullet3);

                Bullet *bullet4 = new Bullet(SPECIAL_ENEMY_BULLET, (*it)->x()+(*it)->pixmap().width()/2, (*it)->y()+(*it)->pixmap().height()-15,
                                     MyScene->SpecialEnemyBulletImage, QPointF(2,1), SPECIAL_ENEMY_POWER);
                bullet4->setRotation(-63);
                enemybullet.push_back(bullet4);
                MyScene->addItem(bullet4);
            }
        }
}
void Bullet::UpdateEnemyBullet()
{
    for(vector<Bullet*>::iterator it = enemybullet.begin(); it!=enemybullet.end(); )
    {
        pair<int ,int> pos = (*it)->UpdatePosition();
        if((*it)->MoveBullet( pos.first, pos.second))
            it++;
        else
        {
            delete *it;
            it = enemybullet.erase(it);
        }
    }
}
bool Bullet::MoveBullet(int NewX, int NewY)
{
    //返回值为是否撞击过

    /* 检查位置是否有变化，无变化则返回true */
    if (x() == NewX && y() == NewY)
        return true;

    /* 检查子弹是否击中我方飞机 */
    if ((type==ENEMY_BULLET||type==SPECIAL_ENEMY_BULLET) && collidesWithItem(mycraft))
    {

        mycraft->crash(power);
        game.UpdateBar(MyScene->CurrentBlood, MyScene->BloodSlot, MyScene->BloodPos, -power, QBrush(Qt::red));
        del();

        if(mycraft->blood<=0)
            game.LoseGame();
    }

    else if(type==MY_BULLET)
    {
        // 然后检查敌机：若敌机已经没有生命值，就从enemyplanes中删去
        for (vector<EnemyPlane*>::iterator it = enemy.begin(); it != enemy.end(); )
        {
            bool alive = true;
            if (collidesWithItem(*it))
            {

                alive = (*it)->crash(mycraft->power);
                mycraft->blue+=BLUE_INC;
                game.UpdateBar(MyScene->CurrentBlue, MyScene->BlueSlot, MyScene->BluePos, +BLUE_INC, QBrush(Qt::blue));
                del();
                game.score++;
                MyScene->ScoreInfo->setHtml(QString("<font color=white>分数: %1</font>").arg(game.score));
            }

            if(alive)
                it++;
            else
            {
                delete *it;
                it = enemy.erase(it);
                if((*it)->type==SPECIAL_ENEMY)
                {
                    Medicine *newlifeSupply = new Medicine(RED_MEDICINE, MyScene->MedicineImage);
                    newlifeSupply->setPos(pos());
                    lifesupply.push_back(newlifeSupply);
                    MyScene->addItem(newlifeSupply);
                }
                else if((*it)->type==BLUE_ENEMY)
                {
                    //to do
                    Medicine *newBlueSupply = new Medicine(BLUE_MEDICINE, MyScene->BlueMedicineImage);
                    newBlueSupply->setPos(pos());
                    lifesupply.push_back(newBlueSupply);
                    MyScene->addItem(newBlueSupply);
                }
            }
        }
    }

    /* 若子弹还具有杀伤力则更新位置并同步屏幕 */
    if (power > 0)
    {
        /* 若此时子弹试图打出边界，则销毁子弹 */
        if (NewX <= 0 || NewX >= MyScene->width() || NewY <= 0 || NewY >= MyScene->height())
        {
           // bullet->delScreen(this);
            MyScene->RemoveObject(this);
            return false;
        }
        MyScene->CreateObject(this);
        moveBy(NewX-x(), NewY-y());
        update();
    }

    return power>0;
}

