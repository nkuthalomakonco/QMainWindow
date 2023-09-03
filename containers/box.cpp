#include "box.h"

Box::Box()
    :Container(),length(0),breadth(0),height(0)
{

}

Box::Box(QString cd, int len, int brth, int hght)
    :Container(cd),length(len),breadth(brth),height(hght)
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
