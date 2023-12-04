#include "containerlist.h"
#include "containerfactory.h"
#include "qmetaobject.h"
#include <QMetaObject>


ContainerList* ContainerList::onlyInstanceContainerList = NULL;

ContainerList::~ContainerList()
{
//    qDeleteAll(containerList);
//    delete containerList;
}

ContainerList *ContainerList::getInstance()
{
    if (onlyInstanceContainerList == NULL)
        onlyInstanceContainerList = new ContainerList;
    return onlyInstanceContainerList;
}

Container *ContainerList::getContainer(int pos) const
{
    return containerList->at(pos);
}
Container *ContainerList::getContainer(QString code) const
{
    if(size()==0)return nullptr;

    for (int i = 0; i < size(); ++i) {
        if (containerList->at(i)->getCode() == code)
            return containerList->at(i);
    }

    return nullptr;
}

int ContainerList::size() const
{
    return containerList->size();
}

containerListMemento *ContainerList::createMemento()
{
    if(size()==0)return new containerListMemento();
    QList<QStringList> mem;
    QStringList memList;

    for (int i=0; i<containerList->size(); i++)
      {
        const Container *cn = containerList->at(i);
        const QMetaObject* metaObject = cn->metaObject();
        for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
            memList << QString::fromLatin1(metaObject->property(i).name());

        //memList.append(containerList->at(i)->getCode());
        //memList.append(QString::number(containerList->at(i)->getWeight()));

        //use QMetaProperty. to get class names.

        mem.append(memList);//add just code prop.
        memList.clear();
      }

    containerListMemento* memento = new containerListMemento();
    memento->setState(mem);
    return memento;
}

void ContainerList::setMemento(containerListMemento *m)
{
    qDeleteAll(*containerList);
    containerList->clear();

    QList<QStringList> mem = m->getState();

    Container *cn = 0;

    //create container factory.
    containerFactory *cf = new containerFactory();
    QString cd = "";
    int d = 0;
    int h = 0;
    int w = 0;
    int l = 0;
    int b = 0;

    for (int i=0; i<mem.size(); i++)
    {
        QStringList list = mem.at(i);
       //check if box or cylinder
        cd = list.at(0);
        if(list.size()==4){

             d = list.at(1).toInt();
             h = list.at(2).toInt();
             w = list.at(3).toInt();
        }
        else{
            //box
            b = list.at(1).toInt();
            l = list.at(2).toInt();
            h = list.at(3).toInt();
            w = list.at(4).toInt();
        }
        cn = cf->createContainer("box",cd,l,b,h,d,w);
        if(cn) containerList->append(cn);
        cn = 0;
    }

    delete cf;
}

ContainerList::ContainerList()
{
    containerList = new QList<Container*>;
}
void ContainerList::addContainer(Container *c)
{
    containerList->append(c);
}

void ContainerList::deleteContainer(int pos)
{
    if(containerList->isEmpty())
        return;
    containerList->removeAt(pos);
}
void ContainerList::deleteContainer(QString code)
{
    if(containerList->isEmpty()) return;
    for (int i = 0; i < size(); ++i) {
        if (containerList->at(i)->getCode() == code)
            containerList->removeAt(i);
    }
}

void ContainerList::deleteContainer(Container *c)
{
    if(containerList->isEmpty()) return;
    for (int i = 0; i < size(); ++i) {
        if (containerList->at(i)->getCode() == c->getCode())
            containerList->removeAt(i);
    }
}

