#include "Scene.h"
#include"ProcessGame.h"
#include"MyPlane.h"
Scene* MyScene;

Scene::Scene()
{
    //设置游戏框的位置、长宽
    setSceneRect(0,0,1024,640);

    /* 游戏标题 */
    TitleInfo = new QGraphicsTextItem;
    addItem(TitleInfo);
    TitleInfo->setHtml("<font color=white>浴火银河</font>");
    TitleInfo->setFont(QFont("Times New Roman", 30));
    TitleInfo->setZValue(2);
    TitleInfo->setPos(350,100);
    TitleInfo->hide();

    /* 本人信息 */
    CoderInfo = new QGraphicsTextItem;
    addItem( CoderInfo);
    CoderInfo->setHtml(tr("<font color=white> Designed By 171860659, Wu zihang @June,2019  All Rights Reserved."));
    CoderInfo->setFont(QFont("Times New Roman"));
    CoderInfo->setPos(100, 500);
    CoderInfo->setZValue(2);
    CoderInfo->hide();

    /* 对话框遮罩 */
    QWidget *mask = new QWidget;
    mask->setAutoFillBackground(true);
    mask->setPalette(QPalette(QColor(10, 10, 10,100)));
    mask->resize((int)width(),(int)height());
    MaskWidget = addWidget(mask);
    MaskWidget->setPos(0,0);
    MaskWidget->setZValue(1); //遮罩设在最上方，一开始隐藏，暂停和菜单中出现
    MaskWidget->hide();


    /* 游戏开始按钮 */
    StartGameButton = new QPushButton("开始游戏");
    StartGameButton->setFont(QFont("Times New Roman",18));
    StartGameButton->setStyleSheet("QPushButton{background: transparent; color:white; }" "QPushButton:hover{color:red;}");
    connect(StartGameButton,&QPushButton::clicked,this,&Scene::StartGame);
    StartGameWidget = addWidget(StartGameButton);
    StartGameWidget->setZValue(2);//放在第二层上面
    StartGameWidget->setPos(370,250);
    StartGameWidget->hide();

    /* 游戏帮助按钮*/
    HelpGameButton = new QPushButton("游戏指南");
    HelpGameButton ->setFont(QFont("Times New Roman",18));
    HelpGameButton ->setStyleSheet("QPushButton{background: transparent; color:white; }" "QPushButton:hover{color:red;}");
    connect(HelpGameButton ,&QPushButton::clicked,this,&Scene::ShowHelp);
    HelpGameWidget = addWidget(HelpGameButton );
    HelpGameWidget->setZValue(2);
    HelpGameWidget->setPos(370,300);
    HelpGameWidget->hide();

    /* 退出游戏按钮 */
    QuitGameButton = new QPushButton("退出游戏");
    QuitGameButton->setFont(QFont("Times New Roman",18));
    QuitGameButton->setStyleSheet("QPushButton{background: transparent; color:white; }" "QPushButton:hover{color:red;}");
    connect(QuitGameButton,&QPushButton::clicked,this,&Scene::QuitGame);
    QuitGameWidget = addWidget(QuitGameButton);
    QuitGameWidget->setPos(370, 350);
    QuitGameWidget->setZValue(2);
    QuitGameWidget->hide();

    /* 游戏继续提示 */
    game.IsPause = false;
    ContinueGameButton = new QPushButton("继续游戏");
    ContinueGameButton->setFont(QFont("Times New Roman",18));
    ContinueGameButton->setStyleSheet("QPushButton{background: transparent; color:white; }" "QPushButton:hover{color:red;}");
    connect(ContinueGameButton,&QPushButton::clicked,this,&Scene::PauseGame);
    ContinueGameWidget = addWidget(ContinueGameButton);
    ContinueGameWidget->setPos(370,250);
    ContinueGameWidget->setZValue(2);
    ContinueGameWidget->hide();

    /*返回菜单按钮*/
    BackMenuButton= new QPushButton("返回菜单");
    BackMenuButton->setFont(QFont("Times New Roman",18));
    BackMenuButton->setStyleSheet("QPushButton{background: transparent; color:white; }" "QPushButton:hover{color:red;}");
    connect(BackMenuButton,&QPushButton::clicked,this,&Scene::BackMenu);
    BackMenuWidget = addWidget(BackMenuButton);
    BackMenuWidget->setPos(370, 350);
    BackMenuWidget->setZValue(2);
    BackMenuWidget->hide();

    /* 初始化场景，循环播放背景音乐 */
    playList = new QMediaPlaylist;
    playList->addMedia(QUrl("qrc:///music/devil.mp3"));
    playList->addMedia(QUrl("qrc:///music/croatian.mp3"));
    playList->addMedia(QUrl("qrc:///music/angel.mp3"));
    playList->addMedia(QUrl("qrc:///music/shadowgraph.mp3"));
    playList->setPlaybackMode(QMediaPlaylist::Sequential);
    player = new QMediaPlayer(this);
    player->setPlaylist(playList);
    player->play();

    //设置物体图像的文件路径
    MyCraftImage = ":/images/MyCraft.png";
    EnemyImage = ":/images/enemy.png";
    SpecialEnemyImage = ":/images/SpecialEnemy.png";
    BlueEnemyImage = ":/images/BlueEnemy.png";
    MyBulletImage = ":/images/MyBullet.png";
    EnemyBulletImage = ":/images/EnemyBullet.png";
    SpecialEnemyBulletImage = ":/images/SpecialEnemyBullet.png";
    MedicineImage = ":/images/medicine.png";
    BlueMedicineImage = ":/images/BlueMedicine.png";


    //得分、血槽、蓝槽的位置
    ScorePos = QPointF(STATE_X, STATE_Y);
    BloodPos = QPointF(STATE_X,STATE_Y+STATE_DETAY);
    BluePos = QPointF(STATE_X, STATE_Y+2*STATE_DETAY);    


     /* 分数显示 */
    game.score = 0; //得分清零
    ScoreInfo = new QGraphicsTextItem;
    ScoreInfo->setHtml(QString("<font color=white>分数: %1</font>").arg(game.score));
    ScoreInfo->setFont(QFont("Times New Roman"));
    ScoreInfo->setPos(ScorePos);
    addItem(ScoreInfo);
    ScoreInfo->hide();

    /* 血量进度条 */
    BloodSlot= new QGraphicsRectItem(BloodPos.x(), BloodPos.y(), ORIGINAL_BLOOD,5);
    BloodSlot->setPen(QPen(Qt::white));
    addItem(BloodSlot);
    BloodSlot->hide();
    CurrentBlood = new QGraphicsRectItem(BloodPos.x(), BloodPos.y(), ORIGINAL_BLOOD, 5);
    CurrentBlood->setBrush(QBrush(Qt::red));
    addItem(CurrentBlood);
    CurrentBlood->hide();

    /* 蓝量进度条 */
    BlueSlot = new QGraphicsRectItem(BluePos.x(),BluePos.y(), ORIGINAL_BLOOD,5);
    BlueSlot->setPen(QPen(Qt::white));
    addItem(BlueSlot);
    BlueSlot->hide();
    CurrentBlue = new QGraphicsRectItem(BluePos.x(), BluePos.y(), ORIGINAL_SKILL, 5);
    CurrentBlue->setBrush(QBrush(Qt::blue));
    addItem(CurrentBlue);
    CurrentBlue->hide();


    /* 游戏终止提示 */
    GameLostInfo = new QGraphicsTextItem;
    addItem(GameLostInfo);
    GameLostInfo->setHtml(tr("<font color=white>游戏结束</font>"));
    GameLostInfo->setFont(QFont("Times New Roman", 22));
    GameLostInfo->setPos(300, 150);
    GameLostInfo->setZValue(2);
    GameLostInfo->hide();

    /* 重试按钮 */
    RetryGameButton = new QPushButton(tr("重新开始"));
    RetryGameButton->setFont(QFont("Times New Roman",18));
    RetryGameButton->setStyleSheet("QPushButton{background: transparent; color:white; }""QPushButton:hover{color:red;}");
    connect(RetryGameButton,&QPushButton::clicked,this,&Scene::RetryGame);
    RetryGameWidget = addWidget(RetryGameButton);
    RetryGameWidget->setPos(370,250);
    RetryGameWidget->setZValue(2);
    RetryGameWidget->hide();

    //菜单初始化
   ShowMenu();
}
void Scene::ShowMenu()
{
    //菜单初始化
    game.InMenu = 1;
    MaskWidget->show();
    CoderInfo->show();
    TitleInfo->show();
    StartGameButton->show();
    HelpGameButton->show();
    QuitGameButton->show();
}
void Scene::HideMenu()
{
    //进入游戏菜单隐藏
    game.InMenu = 0;
    MaskWidget->hide();
    CoderInfo->hide();
    TitleInfo->hide();
    StartGameButton->hide();
    HelpGameButton->hide();
    QuitGameButton->hide();
}
void Scene::ShowState(){
   //进入游戏 状态栏初始化
    game.score = 0;
    ScoreInfo->setHtml(QString("<font color=white>分数: %1</font>").arg(game.score));
    ScoreInfo->show();
    BloodSlot->show();
    CurrentBlood->setRect(BloodPos.x(), BloodPos.y(), ORIGINAL_BLOOD, CurrentBlood->rect().height());
    CurrentBlood->setBrush(Qt::red);
    CurrentBlood->update();
    CurrentBlood->show();
    BlueSlot->show();
    CurrentBlue->setRect(BluePos.x(), BluePos.y(), ORIGINAL_SKILL, CurrentBlue->rect().height());
    CurrentBlue->setBrush(Qt::blue);
    CurrentBlue->update();
    CurrentBlue->show();
}
void Scene::HideState(){
    //返回菜单，状态栏隐藏
     ScoreInfo->hide();
     BloodSlot->hide();
     CurrentBlood->hide();
     BlueSlot->hide();
     CurrentBlue->hide();
}
void Scene::CreateObject(QGraphicsPixmapItem* object){
    if(!items().contains(object))
    {
        addItem(object);
        object->update();
    }
}
void Scene::RemoveObject(QGraphicsPixmapItem* object){
    removeItem(object);
    object->update();
}
//槽函数
void Scene::StartGame()
{
    game.StartGame();
}
void Scene::ShowHelp()
{
    game.ShowHelp();
}
void Scene::QuitGame()
{
    game.QuitGame();
}
void Scene::PauseGame()
{
    game.PauseGame();
}
void Scene::BackMenu(){
    game.BackMenu();
}
void Scene::LoseGame()
{
    game.LoseGame();
}
void Scene::RetryGame()
{
   game.RetryGame();
}
//事件处理函数
void Scene::timerEvent(QTimerEvent *event)
{
    game.TimerEvent(event);
}
void Scene::keyPressEvent(QKeyEvent *event)
{
   game.KeyPressEvent(event);
}
void Scene::keyReleaseEvent(QKeyEvent *event)
{
   game.KeyReleaseEvent(event);
}

