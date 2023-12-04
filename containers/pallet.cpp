#include "pallet.h"
#include<QDebug>

pallet::pallet(int n)
    :number(n),weight(0),volume(0),containerList(new QList<Container*>)
{

}

pallet::~pallet()
{
    containerList->clear();
    delete containerList;
}

int pallet::getNumber() const
{
    return number;
}

void pallet::setNumber(int value)
{
    number = value;
}

void pallet::addContainer(Container *c)
{
    containerList->append(c);
}

Container *pallet::getContainer(int pos)
{
    if(size()==0)return 0;
    return containerList->at(pos);
}

bool pallet::removeContainer(Container *c)
{
    if(size()==0)return false;
    for (int i = 0; i < size(); ++i) {
        if (containerList->at(i)->getCode() == c->getCode()){
            containerList->removeAt(i);
            return true;
        }
    }return false;
}

int pallet::size() const
{
    if(!containerList)qDebug()<<"containerList null.";
    if(!containerList)return 0;//check for null.
    return containerList->size();
}

int pallet::getWeight() const
{
    if(size()==0)return 0;
    int w = 0;
    for (int i = 0; i < size(); ++i)w+=containerList->at(i)->getWeight();
    return w;
}

int pallet::getVolume() const
{
    if(size()==0)return 0;
    int v = 0;
    for (int i = 0; i < size(); ++i)v+=containerList->at(i)->getVolume();
    return v;
}

QList<Container *> *pallet::getContainerList() const
{
    return containerList;
}

void pallet::setContainerList(QList<Container *> *value)
{
    containerList = value;
}

QString pallet::toString(){
    return QString("Pallet no: %1 Number of containers: %2")
            .arg(QString::number(number)).arg(QString::number(size()));
}
