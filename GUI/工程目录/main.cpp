#include"Scene.h"
#include "MyView.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /* 开场画面 */
    QPixmap start(":/images/start.png");
    QSplashScreen splash(start);
    splash.show();
    Sleep(500);


    /* 游戏界面 */
    MyView *view = new MyView;
    //等游戏界面出现后启动动画才会消失
    splash.finish(view);
   // view->setWindowTitle(QObject::tr("FIRE ON GALAXY"));
    view->setWindowTitle("FIRE ON GALAXY");
    view->setBackgroundBrush(QBrush(QPixmap(":/images/BackGround.png")));
    MyScene=new Scene;
    view->setScene(MyScene);
    view->show();

    return app.exec();
}

/*
做蓝色补给，增加一个追击我方的敌人，死亡掉蓝补给，三种敌人可以做关卡
思路：蓝条补给同血条，追击通过移动的时候随机数完成，注意移动的时候敌方不要相撞
难度：***
需求：**

*/
