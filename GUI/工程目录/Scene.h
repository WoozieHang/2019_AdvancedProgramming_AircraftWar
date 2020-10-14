#ifndef SCENE_H
#define SCENE_H

#include <ctime>
#include <vector>
#include <cassert>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <windows.h>

#include <QUrl>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include"Medicine.h"
#include "Plane.h"
#include "MyPlane.h"
#include "EnemyPlane.h"
#include "Config.h"
//#include"ProcessGame.h"

using namespace std;

class Scene: public QGraphicsScene
{
    //提供信号和槽的机制
    Q_OBJECT
public:
    Scene();

protected:


private:
    //文本信息
    QGraphicsTextItem *TitleInfo; //游戏标题
    QGraphicsTextItem *CoderInfo; //作者信息
    QGraphicsTextItem *ScoreInfo; //显示当前打掉的飞机数
    QGraphicsTextItem *GameLostInfo; //玩家死亡显示文本
    QGraphicsTextItem *GameHelpInfo; //游戏初始帮助

    //菜单按钮
    QPushButton *StartGameButton ;
    QPushButton *HelpGameButton ;
    QPushButton *QuitGameButton;
    QPushButton *BackMenuButton;
    QPushButton *ContinueGameButton;
    QPushButton *RetryGameButton;

    //遮罩面板
    QGraphicsWidget *MaskWidget;
    QGraphicsWidget *StartGameWidget;
    QGraphicsWidget *HelpGameWidget;
    QGraphicsWidget *ContinueGameWidget;
    QGraphicsWidget *BackMenuWidget;
    QGraphicsWidget *RetryGameWidget;
    QGraphicsWidget *QuitGameWidget;

    //得分、血槽、蓝槽的位置
    QPointF ScorePos;
    QPointF BloodPos;
    QPointF BluePos;

    //图像文件路径
    string MyCraftImage;
    string EnemyImage;
    string SpecialEnemyImage;
    string BlueEnemyImage;
    string MyBulletImage;
    string EnemyBulletImage;
    string SpecialEnemyBulletImage;
    string MedicineImage;
    string BlueMedicineImage;

    //媒体音乐管理
    QMediaPlayer *player;
    QMediaPlaylist *playList;

    //状态栏图案
    QGraphicsRectItem* BloodSlot;
    QGraphicsRectItem* CurrentBlood;
    QGraphicsRectItem* BlueSlot;
    QGraphicsRectItem* CurrentBlue;

    //显示或隐藏菜单
     void ShowMenu(); //菜单界面
     void HideMenu();


     //显示或隐藏游戏当前状态：分数、血量、蓝量
     void ShowState();
     void HideState();

     //创建物体、删去物体
     void CreateObject(QGraphicsPixmapItem* object);
     void RemoveObject(QGraphicsPixmapItem* object);

     //slot function
     void StartGame(); //开始游戏
     void ShowHelp(); //显示帮助信息
     void QuitGame(); //结束游戏
     void PauseGame(); //暂停游戏或继续游戏
     void BackMenu();//返回菜单
     void LoseGame(); //玩家生命值用尽
     void RetryGame();  //重新开始


       //计划放入game中的函数们
    //event dealing function
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

  friend Bullet;
  friend Plane;
  friend class ProcessGame;
  friend EnemyPlane;
};


#endif // !CONTROL_H

extern Scene* MyScene;
