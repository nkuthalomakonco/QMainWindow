#include "containerlistmemento.h"

containerListMemento::containerListMemento()
{

}

QList<QStringList> containerListMemento::getState()
{
    return state;
}

void containerListMemento::setState(QList<QStringList> s)
{
     state = s;
}
