#ifndef CYLINDER_H
#define CYLINDER_H

#include "container.h"

class Cylinder : public Container
{
    Q_OBJECT
    Q_PROPERTY(int diameter READ getDiameter WRITE setDiameter)


public:
    Cylinder();
    Cylinder(QString cd,int d, int hght,int wght);
    ~Cylinder();
    int getWeight();
    int getVolume();
    QString toString();

    int getDiameter() const;
    void setDiameter(int value);

    int getHeight() const;
    void setHeight(int value);

private:
    int diameter;
};

#endif // CYLINDER_H
