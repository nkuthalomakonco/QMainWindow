#ifndef CONTAINERLIST_H
#define CONTAINERLIST_H
#include "container.h"

class ContainerList
{
public:
    ~ContainerList();
    void addContainer(Container* c);
    void deleteContainer(int pos);
    void deleteContainer(Container* c);
    static ContainerList* getInstance();
    Container* getContainer(int pos) const;
    int size() const;
private:
    ContainerList();
    static ContainerList* onlyInstanceContainerList;
    QList<Container*>* containerList;
};

#endif // CONTAINERLIST_H
