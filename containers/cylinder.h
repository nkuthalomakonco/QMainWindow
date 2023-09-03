#ifndef CYLINDER_H
#define CYLINDER_H

#include "container.h"

class Cylinder : public Container
{

public:
    Cylinder();
    Cylinder(QString cd,int d, int hght);
    int getWeight();
    int getVolume();
    QString toString();
private:
    int diameter, height;
};

#endif // CYLINDER_H
