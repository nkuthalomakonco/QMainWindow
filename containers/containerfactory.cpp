#include "containerfactory.h"
#include "box.h"
#include "cylinder.h"

containerFactory::containerFactory()
{

}

Container *containerFactory::createContainer(QString type,QString cd,
                                             int len=0, int brth=0, int hght=0,int dia=0,int wgt=0)
{
    if (type == "box")
        return new Box(cd,len,brth,hght,wgt);//Box(QString cd, int len, int brth, int hght, int wght);
    else if (type == "cylinder")
        return new Cylinder(cd,dia,hght,wgt);//Cylinder(QString cd,int d, int hght,int wght);
    return NULL;
}
