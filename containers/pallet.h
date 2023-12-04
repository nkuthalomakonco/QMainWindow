#ifndef PALLET_H
#define PALLET_H

#include "container.h"
//did not use singleton
class pallet
{
public:
    pallet(int n);
    ~pallet();
    int getNumber() const;
    void setNumber(int value);
    void addContainer(Container *c);
    Container *getContainer(int pos);
    bool removeContainer(Container *c);
    int size()const;
    int getWeight() const;
    int getVolume() const;

    QList<Container *> *getContainerList() const;
    void setContainerList(QList<Container *> *value);

    QString toString();

    bool operator==(pallet *p){return (this->number == p->number);}
private:
    int number,weight,volume;
    QList<Container*>* containerList;
};

#endif // PALLET_H
