#include "palletlist.h"
#include <QDebug>

palletList::palletList()
    :palletlist(new QList<pallet*>)
{
}

palletList::~palletList()
{
    palletlist->clear();
//  qDeleteAll(palletlist->begin(), palletlist->end());
//  qDeleteAll(palletlist);
}

void palletList::addPallet(pallet *c)
{
    palletlist->append(c);
}

void palletList::deletePallet(int pos)
{
    palletlist->removeAt(pos);
}
/* -------------------------------------------------------------
 * Replace old pallet with updated pallet.
 * -------------------------------------------------------------
*/
bool palletList::updatePallet(pallet *p)
{
    if (!checkPallet(p))
        return false;
    for (int i = 0; i < size(); ++i) {
        if (palletlist->at(i)->getNumber() == p->getNumber()){
            palletlist->replace(i,p);
            return true;
        }
    }return false;
}
/* -------------------------------------------------------------
 * Delete pallet from the pallet list.
 * -------------------------------------------------------------
*/
void palletList::deletePallet(pallet *p)
{
//    const int pos = palletlist->indexOf(p);
//    palletlist->removeAt(pos);

    if (size()==0)
        return;
    if (!checkPallet(p))
        return;
    //pallet exist in the list.

    for (int i = 0; i < size(); ++i) {
        if (palletlist->at(i)->getNumber() == p->getNumber())
            palletlist->removeAt(i);
    }
}
/* -------------------------------------------------------------
 * Get pallet from pallet list.[with list position]
 * -------------------------------------------------------------
*/
pallet *palletList::getPallet(int pos) const
{
    if (size()==0)
        return 0;//null
    return palletlist->at(pos);
}
/* -------------------------------------------------------------
 * Get pallet from pallet list.
 * -------------------------------------------------------------
*/
pallet *palletList::getPallet(pallet *p)
{

    if (size()==0)
        return 0;//null
    if (!checkPallet(p))
        return 0;//null
    //pallet exist in the list.

    for (int i = 0; i < size(); ++i) {
        if (palletlist->at(i)->getNumber() == p->getNumber())
            return palletlist->at(i);
    }
    return 0;//null
}
/* -------------------------------------------------------------
 * Get pallet list size.
 * -------------------------------------------------------------
*/
int palletList::size() const
{
    return palletlist->size();
}
/* -------------------------------------------------------------
 * Check if pallet is in the list.
 * -------------------------------------------------------------
*/
bool palletList::checkPallet(pallet *p)
{
    if (size()==0)
        return false;
    for (int i = 0; i < size(); ++i) {
        if (palletlist->at(i)->getNumber() == p->getNumber())
            return true;
    }
    return false;
}
/* -------------------------------------------------------------
 * Print pallet list info.
 * -------------------------------------------------------------
*/
QString palletList::toString()
{
    for (int i = 0; i < size(); ++i) {
            qDebug()<<palletlist->at(i)->toString();
        }
    return "";
}

