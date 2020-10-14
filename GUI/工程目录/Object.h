#ifndef OBJECT_H
#define OBJECT_H

#include <QtWidgets>
#include <string>

using namespace std;



class Object : public QGraphicsPixmapItem
{
public:
    Object();
    Object(int t, const string &imageFile);
    ~Object();

protected:
    int type;
friend class Plane;
friend class Bullet;
};

#endif // OBJECT_H
