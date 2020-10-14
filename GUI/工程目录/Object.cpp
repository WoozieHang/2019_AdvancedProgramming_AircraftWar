#include "Object.h"

Object::Object()
{

}

Object::Object(int t, const string &imageFile):
    QGraphicsPixmapItem(QPixmap(QString::fromStdString(imageFile)))
{
    type=t;
}

Object::~Object()
{

}
