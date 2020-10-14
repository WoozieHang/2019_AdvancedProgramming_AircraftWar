#include "ProcessGame.h"

ProcessGame game;

ProcessGame::ProcessGame()
{

}
void ProcessGame::SetTimer(){
    /* 设置各动作更新时钟 */
    MyShootTimer = MyScene->startTimer(MY_BULLET_INTERVAL);
    EnemyShootTimer = MyScene->startTimer(ENEMY_BULLET_INTERVAL);
    MyBulletTimer=MyScene->startTimer(MY_BULLET_SPEED);
    EnemyBulletTimer=MyScene->startTimer(ENEMY_BULLET_SPEED);
    EnemyTimer = MyScene->startTimer(ENEMY_SPEED);
    EnemyGenerateTimer = MyScene->startTimer(ENEMY_GENERRATE_INTERVAL);
    SpecialEnemyGenerateTimer = MyScene->startTimer(SPECIAL_ENEMY_GENERRATE_INTERVAL);
    BlueEnemyGenerateTimer = MyScene->startTimer(BLUE_ENEMY_GENERRATE_INTERVAL);
}
void ProcessGame::DelTimer(){
    //释放定时器
    MyScene->killTimer(MyShootTimer);
    MyScene->killTimer(EnemyShootTimer);
    MyScene->killTimer(MyBulletTimer);
    MyScene->killTimer(EnemyBulletTimer);

    MyScene->killTimer(EnemyTimer);
    MyScene->killTimer(EnemyGenerateTimer);
    MyScene->killTimer(BlueEnemyGenerateTimer);
    MyScene->killTimer(SpecialEnemyGenerateTimer);
}
void ProcessGame::CleanGame(){
    //玩家删除
    delete mycraft;
    mycraft=nullptr;

    for(auto iter:enemy)
    {
       MyScene->removeItem(iter);
        delete iter;
    }
    enemy.clear();

    for(auto it:mybullet)
    {
        MyScene->removeItem(it);
        delete it;
    }
    mybullet.clear();

    for(auto it:enemybullet)
    {
         MyScene->removeItem(it);
        delete it;
    }
    enemybullet.clear();

    for(auto it:lifesupply)
    {
         MyScene->removeItem(it);
        delete it;
    }
    lifesupply.clear();

}
void ProcessGame::StartGame()
{
    MyScene->HideMenu();
    MyScene->ShowState();
    IsPause=0;
    /* 添加玩家飞机 */
   mycraft = new MyPlane(MyScene->width() / 2, MyScene->height()-MyPlane::height, MyScene->MyCraftImage, MyScene, ORIGINAL_BLOOD, ORIGINAL_SKILL,ORIGINAL_POWER);
    MyScene->CreateObject(mycraft);
    mycraft->SetMove(0,0);

    /* 添加敌机 */
    for (int i = 0; i < 3; i++)
        EnemyPlane::GenerateEnemy();

    //设置定时器
   SetTimer();
}
void ProcessGame::ShowHelp()
{
    QString helpText;
    helpText += QString("           关于游戏： \n");
    helpText += QString("这是一款模仿现实游戏浴火银河（FIRE ON GALAXY）的空战游戏\n");
    helpText += QString("           关于规则： \n");
    helpText += QString("\n子弹命中敌机，分数和蓝条会增加\n");
    helpText += QString("被敌机击中或撞到，血条会相应减少\n");
    helpText += QString("蓝条达到一定量的时候，可按空格发出技能\n");
    helpText += QString("\n         关于操作：\n");
    helpText += QString("↑：上； ↓：下； ←：左； →：右\n");
    helpText += QString("空格：弹雨四射，一次发射三个方向的子弹，消耗蓝条\n");
    helpText += QString("回车键：暂停游戏\n");
    helpText += QString("r键：切换音乐\n");
    helpText += QString("\n         关于敌人：\n");
    helpText += QString("\n（1）绿色敌人：普通敌人，直线前进，普通子弹，血少伤害低\n");
    helpText += QString("击落后不掉落补给\n");
    helpText += QString("\n（2）红色敌人：特殊敌人，直线前进，群发特殊子弹，血多伤害多\n");
    helpText += QString("击落后基本会掉落红色补给，可补充部分点血值\n");
    helpText += QString("\n（3）蓝色敌人：特殊敌人，追击我方前进，无子弹速度快，靠冲撞打攻击\n");
    helpText += QString("击落后掉落基本会蓝色补给，可补充部分点蓝值\n");

    QMessageBox::information(nullptr,QString("游戏帮助"),helpText);
}
void ProcessGame::QuitGame()
{
    exit(0);
}
void ProcessGame::PauseGame()
{
    if(!IsPause)
    {
        IsPause = true;
        DelTimer();
        MyScene->MaskWidget->show();
        MyScene->ContinueGameButton->show();
        MyScene->HelpGameButton->show();
        MyScene->BackMenuButton->show();
    }
    else
    {
        //重新设置定时器
        IsPause = false;
        SetTimer();
        MyScene->MaskWidget->hide();
        MyScene->ContinueGameButton->hide();
        MyScene->HelpGameButton->hide();
        MyScene->BackMenuButton->hide();
    }
}
void ProcessGame::BackMenu(){
    CleanGame();
    //通过暂停返回菜单
    if(IsPause){
    MyScene->MaskWidget->hide();
    MyScene->ContinueGameButton->hide();
    MyScene->HelpGameButton->hide();
    MyScene->BackMenuButton->hide();
    }

    //玩家死亡后返回菜单
    else{
    MyScene->GameLostInfo->hide();
    MyScene->RetryGameButton->hide();
    MyScene->HelpGameButton->hide();
    MyScene->BackMenuButton->hide();
    }

    MyScene->ShowMenu();
    MyScene->HideState();
}
void ProcessGame::LoseGame()
{
    DelTimer();
    MyScene->MaskWidget->show();
    MyScene->GameLostInfo->setHtml(QString("<font color=white>游戏结束, 您的分数: %1</font>").arg(score));
    MyScene->GameLostInfo->show();
    MyScene->RetryGameButton->show();
    MyScene->HelpGameButton->show();
    MyScene->BackMenuButton->show();
}
void ProcessGame::RetryGame()
{
    CleanGame();
    MyScene->GameLostInfo->hide();
    MyScene->RetryGameButton->hide();
    MyScene->HelpGameButton->hide();
    MyScene->BackMenuButton->hide();
    StartGame();
}
void ProcessGame::TimerEvent(QTimerEvent *event)
{
    //菜单界面不考虑时间事件
    if(InMenu==1)
        return ;
    //释放掉移动的趋势，若无移动趋势就跳过
    if(event->timerId()==MyCraftTimer&&(!mycraft->NotMove()))
        mycraft->MovePlane(mycraft->x()+mycraft->MoveX, mycraft->y()+mycraft->MoveY);
    else if(event->timerId()==EnemyShootTimer)
        Bullet::EnemyShootBullet();
    else if(event->timerId()==MyShootTimer)
        Bullet::ShootBullet();
    else if(event->timerId()==MyBulletTimer)
        Bullet::UpdateMyBullet();
    else if(event->timerId()==EnemyBulletTimer)
        Bullet::UpdateEnemyBullet();
    else if(event->timerId()==EnemyTimer)
        EnemyPlane::UpdateEnemy();
    else if(event->timerId()==EnemyGenerateTimer)
    {
        for(int i=0;i<2;i++)
            EnemyPlane::GenerateEnemy();
    }
    else if(event->timerId()==BlueEnemyGenerateTimer)
    {
        for(int i=0;i<2;i++)
            EnemyPlane::GenerateBlueEnemy();
    }
    else if(event->timerId()==SpecialEnemyGenerateTimer)
        EnemyPlane::GenerateSpecialEnemy();
    else if(event->timerId()==SkillTimer)
        mycraft->ShootType = SINGLE_SHOOT;
}
void ProcessGame::KeyPressEvent(QKeyEvent *event)
{

    if((!InMenu)&&(IsPause)&&event->key()!=Qt::Key_Return)
        return;

    else if((!InMenu)&&(!IsPause)&&event->key()==Qt::Key_Up && !event->isAutoRepeat())
    {
        if(mycraft->NotMove())
            MyCraftTimer = MyScene->startTimer(MY_CRAFT_SPEED);

        mycraft->SetMoveY(-10);
        MoveButtonState[UP]=1;
    }
    else if((!InMenu)&&(!IsPause)&&event->key()==Qt::Key_Down && !event->isAutoRepeat())
    {
        if(mycraft->NotMove())
            MyCraftTimer = MyScene->startTimer(MY_CRAFT_SPEED);
        mycraft->SetMoveY(+10);
        MoveButtonState[DOWN]=1;
    }
    else if((!InMenu)&&(!IsPause)&&event->key()==Qt::Key_Left && !event->isAutoRepeat())
    {
        if(mycraft->NotMove())
            MyCraftTimer = MyScene->startTimer(MY_CRAFT_SPEED);
        mycraft->SetMoveX(-10);
         MoveButtonState[LEFT]=1;
    }
    else if((!InMenu)&&(!IsPause)&&event->key()==Qt::Key_Right && !event->isAutoRepeat())
    {
        if(mycraft->NotMove())
            MyCraftTimer = MyScene->startTimer(MY_CRAFT_SPEED);
        mycraft->SetMoveX(+10);
        MoveButtonState[RIGHT]=1;
    }
    else if((!InMenu)&&(!IsPause)&&event->key()==Qt::Key_Space && mycraft->blue>=10)
    {
        //按Q的技能可以一次发射3个子弹，但是会消耗10点技能
         mycraft->ShootType =MANY_SHOOT ;
        mycraft->blue -= BLUE_CONSUME;
        UpdateBar(MyScene->CurrentBlue, MyScene->BlueSlot, MyScene->BluePos, -BLUE_CONSUME, QBrush(Qt::blue));
        SkillTimer = MyScene->startTimer(SKILLLAST); //5秒使用时间
    }
    else if((!InMenu)&&event->key()==Qt::Key_Return)
        PauseGame();

}
void ProcessGame::KeyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_R){
        int CurrentIndex=1+MyScene->playList->currentIndex();
        if(CurrentIndex == MyScene->playList->mediaCount())
             CurrentIndex=0;

        MyScene->playList->setCurrentIndex(CurrentIndex);
    }

    if(IsPause)
        return;
    else if((event->key()==Qt::Key_Up)&& !event->isAutoRepeat()) {
        MoveButtonState[UP]=0;
        if(MoveButtonState[DOWN]==1)
        mycraft->SetMoveY(+10);
        else
            mycraft->SetMoveY(0);

        //如果飞机不动就释放掉当前定时器
        if(mycraft->NotMove())
         MyScene->killTimer(MyCraftTimer);
    }

    else if((event->key()==Qt::Key_Down)&& !event->isAutoRepeat()) {
        MoveButtonState[DOWN]=0;
        if(MoveButtonState[UP]==1)
        mycraft->SetMoveY(-10);
        else
            mycraft->SetMoveY(0);

        //如果飞机不动就更新一下移动计时器
        if(mycraft->NotMove())
         MyScene->killTimer(MyCraftTimer);
   }
   else if((event->key()==Qt::Key_Left)&& !event->isAutoRepeat())
    {
        MoveButtonState[LEFT]=0;
        if(MoveButtonState[RIGHT]==1)
        mycraft->SetMoveX(+10);
        else
          mycraft->SetMoveX(0);

        //如果飞机不动就更新一下移动计时器
        if(mycraft->NotMove())
         MyScene->killTimer(MyCraftTimer);
    }
   else if((event->key()==Qt::Key_Right)&& !event->isAutoRepeat())
    {

        MoveButtonState[RIGHT]=0;
        if(MoveButtonState[LEFT]==1)
        mycraft->SetMoveX(-10);
        else
            mycraft->SetMoveX(0);

        //如果飞机不动就更新一下移动计时器
        if(mycraft->NotMove())
         MyScene->killTimer(MyCraftTimer);
    }
}

void ProcessGame::UpdateBar(QGraphicsRectItem *bar, QGraphicsRectItem *slot, const QPointF &pos, qreal var, const QBrush &brush)
{
    qreal wid = bar->rect().width();
    if(var<0)
        wid = max((qreal)0, wid+var);
    else
        wid = min(slot->rect().width(), wid+var);
    bar->setRect(pos.x(), pos.y(), wid, bar->rect().height());
    bar->setBrush(brush);
    bar->update();
}
