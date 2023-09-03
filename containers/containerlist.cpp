#include "containerlist.h"

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

int ContainerList::size() const
{
    return containerList->size();
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
    containerList->removeAt(pos);
}

void ContainerList::deleteContainer(Container *c)
{
    //containerList->remove(c);
    (void)c;
}

