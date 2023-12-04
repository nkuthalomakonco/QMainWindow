#ifndef WRITEXML_H
#define WRITEXML_H

#include <QDebug>
#include <QDomDocument>

#include "palletlist.h"

class writeXml: public QObject
{
    Q_OBJECT
public:
    writeXml();
    writeXml(palletList *palletlist);
    void setPalletlist(palletList *value);
    ~writeXml();

public slots:
    bool write();
    //bool write(palletList *palletlist);

signals:
      void done(const QString &o);
      void done();
private:
    QDomDocument doc;
    palletList *palletlist;
};

#endif // WRITEXML_H
