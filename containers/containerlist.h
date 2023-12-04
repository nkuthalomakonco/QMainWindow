#ifndef CONTAINERLIST_H
#define CONTAINERLIST_H

#include "container.h"
#include "containerlistmemento.h"

class ContainerList
{
public:
    ~ContainerList();
    void addContainer(Container* c);
    void deleteContainer(int pos);
    void deleteContainer(Container* c);
    void deleteContainer(QString code);
    static ContainerList* getInstance();
    Container* getContainer(int pos) const;
    Container* getContainer(QString code)const;
    int size() const;

    containerListMemento* createMemento();
    void setMemento(containerListMemento* m);

private:
    ContainerList();
    static ContainerList* onlyInstanceContainerList;
    QList<Container*>* containerList;
};

#endif // CONTAINERLIST_H
