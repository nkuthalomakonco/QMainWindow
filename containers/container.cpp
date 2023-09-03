#include "container.h"


Container::Container(): code("unknown")
{

}

Container::Container(QString c): code(c)
{

}

QString Container::getCode()
{
    return code;
}

QString Container::createCode()
{
    //    QStringList m_containerType = { "A", "B", "C" };
    //    QString abc = m_containerType.at(qrand() % m_containerType.size());//get A,B,C
    //    QString m_code = QDate::currentDate().toString("yyyy/MM") + "/" + abc
    //            + QString::number(c);
    //    return m_code;
        return QString("code");
}
