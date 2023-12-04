#include "box.h"

Box::Box()
    :Container(),length(0),breadth(0)
{
    setObjectName("Box");
}

Box::Box(QString cd, int len, int brth, int hght,int wght)
    :Container(cd,hght,wght),length(len),breadth(brth)
{
    setObjectName("Box");
}

Box::~Box()
{

}

int Box::getWeight()
{
    return 1;
}

int Box::getVolume()
{
    return 1;
}


QString Box::toString()
{

    return QString("Box:%1 %2 %3 %4")
            .arg(code,QString::number(length),
                 QString::number(breadth),QString::number(height));

}

int Box::getLength() const
{
    return length;
}

void Box::setLength(int value)
{
    length = value;
}

int Box::getBreadth() const
{
    return breadth;
}

void Box::setBreadth(int value)
{
    breadth = value;
}


