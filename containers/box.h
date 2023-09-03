#ifndef BOX_H
#define BOX_H

#include "container.h"

class Box : public Container
{
public:
    //A box, where we want to know its dimensions: length, breadth, and height.
    Box();
    Box(QString cd,int len, int brth, int hght);
    int getWeight();
    int getVolume();
    QString toString();
private:
    int length, breadth, height;
};

#endif // BOX_H
