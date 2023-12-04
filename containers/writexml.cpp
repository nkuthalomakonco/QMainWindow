#include "writexml.h"
#include<QFile>
#include <QStandardPaths>
#include <QMetaProperty>

writeXml::writeXml()
    :palletlist(new palletList())
{

}

writeXml::writeXml(palletList *palletlist)
{
    this->palletlist = palletlist;
}

void writeXml::setPalletlist(palletList *value)
{
    palletlist = value;
}

writeXml::~writeXml() {
//    delete m_container;
//    delete m_pallet;
//    delete palletlist;
}

bool writeXml::write()
{    
    if(palletlist==0){emit done("");return false;}
    if(palletlist->size()==0){emit done("");return false;}

//  <pallets NumberOfPallets="2">
    // Making the root element
    QDomElement root = doc.createElement("pallets");
    root.setAttribute("NumberOfPallets", palletlist->size());
    doc.appendChild(root);

    pallet *m_pallet = 0;
    Container *m_container = 0;

    m_pallet = 0;
    m_container = 0;

    for (int i = 0; i < palletlist->size(); ++i) {
            m_pallet = palletlist->getPallet(i);
            qDebug()<<m_pallet->toString();
        //  <pallet weight="3" volume="7" number="1">
            QDomElement rootpallet = doc.createElement("pallet");
            rootpallet.setAttribute("weight", m_pallet->getWeight());
            rootpallet.setAttribute("volume", m_pallet->getVolume());
            rootpallet.setAttribute("number", m_pallet->getNumber());

            root.appendChild(rootpallet);
        for (int i = 0; i < m_pallet->size(); ++i) {
              //pallet has list of containers.
            m_container = m_pallet->getContainer(i);
            const QMetaObject *meta = m_container->metaObject();
            QDomElement rootcontainer = doc.createElement(meta->className());
            root.appendChild(rootcontainer);//top

            for(int i = 1; i < meta->propertyCount(); ++i){
                //qDebug() << QString::fromLatin1(meta->property(i).name());
                QMetaProperty metaProp = meta->property(i);
                const char *propName = metaProp.name();
                QVariant propValue = m_container->property(propName);
                QString value = propValue.toString();

                QDomElement element = doc.createElement(propName);//
                QDomText text = doc.createTextNode(value);
                element.appendChild(text);
                rootcontainer.appendChild(element);
            }

            }

        }

//    delete m_pallet;//move away.
//    delete m_container;

    // Writing to a file
    QString fn = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"/containers.xml";

    QFile file(fn);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        emit done(file.errorString());
        return false;
    }

    QTextStream stream(&file);
    emit done(doc.toString());
    stream << doc.toString();
    file.close();
    return true;

}


