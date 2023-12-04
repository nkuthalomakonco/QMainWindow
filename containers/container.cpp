#include "container.h"


Container::Container(): code("unknown"),height(0),weight(0)
{

}

Container::Container(QString c): code(c),height(0),weight(0)
{

}

Container::Container(QString c, int h, int w): code(c),height(h),weight(w)
{

}

int Container::getHeight() const
{
    return height;
}

void Container::setHeight(int value)
{
    height = value;
}

QString Container::getCode() const
{
    return code;
}

void Container::setCode(const QString &value)
{
    code = value;
}

int Container::getWeight() const
{
    return weight;
}

void Container::setWeight(int value)
{
    weight = value;
}


