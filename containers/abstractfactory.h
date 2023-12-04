#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "container.h"

class AbstractFactory
{
public:
    virtual Container* createContainer(QString type) = 0;
    virtual Container* createContainer(QString type,QString cd,int len, int brth, int hght,int dia) = 0;
    virtual ~AbstractFactory(){}
};

#endif // ABSTRACTFACTORY_H
