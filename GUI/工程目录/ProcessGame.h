#ifndef PROCESSGAME_H
#define PROCESSGAME_H

#include "Scene.h"

class ProcessGame
{


//存储移动按钮以改变将来的运动趋势
bool MoveButtonState[4];

//通过定时器来实现物体的移动
int EnemyBulletTimer;
int EnemyShootTimer;
int MyBulletTimer;
int MyShootTimer;
int MyCraftTimer;
int EnemyTimer;
int EnemyGenerateTimer;
int SpecialEnemyGenerateTimer;
int BlueEnemyGenerateTimer;
int SkillTimer; //技能使用时间

//分数
int score;


//游戏阶段标记
bool IsPause; //游戏是否暂停
bool InMenu; //是否处于菜单界面

public:
    ProcessGame();
    void SetTimer();
    void DelTimer();
    void CleanGame();//清除现场的Object

    //slot function
    void StartGame(); //开始游戏
    void ShowHelp(); //显示帮助信息
    void QuitGame(); //结束游戏
    void PauseGame(); //暂停游戏或继续游戏
    void BackMenu();//返回菜单
    void LoseGame(); //玩家生命值用尽
    void RetryGame();  //重新开始
    //事件响应函数
    void TimerEvent(QTimerEvent *event);
    void KeyPressEvent(QKeyEvent *event);
    void KeyReleaseEvent(QKeyEvent *event);

    //状态更新
    void UpdateBar(QGraphicsRectItem *bar, QGraphicsRectItem *slot, const QPointF &pos, qreal var, const QBrush &brush); //更新血条或技能条

friend class Scene;
friend class Bullet;
};


extern ProcessGame game;
#endif // PROCESSGAME_H
