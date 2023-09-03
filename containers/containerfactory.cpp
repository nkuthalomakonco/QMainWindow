#include "containerfactory.h"
#include "box.h"
#include "cylinder.h"

containerFactory::containerFactory()
{

}

Container *containerFactory::createContainer(QString type,QString cd,
                                             int len=0, int brth=0, int hght=0,int dia=0)
{
    if (type == "box")
        return new Box(cd,len,brth,hght);//Box(QString cd,int len, int brth, int hght);
    else if (type == "cylinder")
        return new Cylinder(cd,dia,hght);//Cylinder(QString cd,int d, int hght);
    return NULL;
}
