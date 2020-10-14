#ifndef MYVIEW_H
#define MYVIEW_H


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

#include "Plane.h"
#include "MyPlane.h"
class MyView: public QGraphicsView
{
    //提供信号和槽的机制
    Q_OBJECT
public:
    MyView();
protected:
    //event dealing function
    void resizeEvent(QResizeEvent* event){
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::IgnoreAspectRatio);
    }
};
#endif // MYVIEW_H

