#ifndef BOX_H
#define BOX_H

#include "container.h"

class Box : public Container
{
    Q_OBJECT
    Q_PROPERTY(int length READ getLength WRITE setLength)
    Q_PROPERTY(int breadth READ getBreadth WRITE setBreadth)

public:
    Box();
    Box(QString cd, int len, int brth, int hght, int wght);
    ~Box();
    int getWeight();
    int getVolume();
    QString toString();

    int getLength() const;
    void setLength(int value);

    int getBreadth() const;
    void setBreadth(int value);

private:
    int length, breadth;
};

#endif // BOX_H
