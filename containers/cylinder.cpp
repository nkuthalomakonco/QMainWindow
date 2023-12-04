#include "cylinder.h"

Cylinder::Cylinder()
    :Container(),diameter(0)
{
    setObjectName("Cylinder");
}

Cylinder::Cylinder(QString cd, int d, int hght, int wght)
    :Container(cd,hght,wght),diameter(d)
{
    setObjectName("Cylinder");
}

Cylinder::~Cylinder()
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

int Cylinder::getDiameter() const
{
    return diameter;
}

void Cylinder::setDiameter(int value)
{
    diameter = value;
}

int Cylinder::getHeight() const
{
    return height;
}

void Cylinder::setHeight(int value)
{
    height = value;
}
