#ifndef CONTAINERFACTORY_H
#define CONTAINERFACTORY_H

#include "abstractfactory.h"

#include "container.h"

class containerFactory
{

public:
    containerFactory();
    Container* createContainer(QString type,QString cd,int len, int brth, int hght,int dia,int wgt);

};

#endif // CONTAINERFACTORY_H
