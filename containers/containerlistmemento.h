#ifndef CONTAINERLISTMEMENTO_H
#define CONTAINERLISTMEMENTO_H

#include <QList>
#include <QStringList>


class containerListMemento
{
    friend class Containerlist;//friend class Originator;
//protected:
public:

    containerListMemento();
    QList<QStringList> getState();
    void setState(QList<QStringList> s);

    QList<QStringList> state;
};

#endif // CONTAINERLISTMEMENTO_H
