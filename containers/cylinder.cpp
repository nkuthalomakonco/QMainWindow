#include "cylinder.h"

Cylinder::Cylinder()
    :Container(),diameter(0),height(0)
{

}

Cylinder::Cylinder(QString cd, int d, int hght)
    :Container(cd),diameter(d),height(hght)
{

}

int Cylinder::getWeight()
{
    return 1;
}

int Cylinder::getVolume()
{
    return 1;
}


QString Cylinder::toString()
{
    return QString("Cylinder:%1 %2 %3")
            .arg(code,QString::number(diameter),
                 QString::number(height));
}
