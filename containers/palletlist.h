#ifndef PALLETLIST_H
#define PALLETLIST_H

#include "pallet.h"

class palletList
{
public:
    palletList();
    ~palletList();
    void addPallet(pallet* p);
    //void updatePallet(pallet* p);
    void deletePallet(int pos);
    void deletePallet(pallet* p);
    pallet* getPallet(int pos) const;
    pallet* getPallet(pallet* p);//get pallet from list.
    int size() const;
    bool checkPallet(pallet* p);
    QString toString();
    bool updatePallet(pallet *p);
private:
    QList<pallet*>* palletlist;
};

#endif // PALLETLIST_H
