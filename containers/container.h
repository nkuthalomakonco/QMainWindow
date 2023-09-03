#ifndef CONTAINER_H
#define CONTAINER_H

#include <QString>
#include <QDate>


//struct code{
//  code(int count){
//      if (count < 999)
//          m_count = count;
//      m_code = m_containerType.at(0);}
//  QString getCode(){creatCode();return m_code;}
//  void creatCode(){
//      QString abc = m_containerType.at(qrand() % m_containerType.size());//get A,B,C
//      m_code = QDate::currentDate().toString("yyyy/MM") + "/" + abc
//              + QString::number(m_count);
//  }
//  QString m_code;
//  int m_count;
//  QStringList m_containerType = { "A", "B", "C" };
//  QDate m_date;
//};


class Container
{
public:
    Container();
    Container(QString c);
    QString getCode();
    virtual int getWeight() = 0;
    virtual int getVolume() = 0;
    virtual QString toString() = 0;
    //QString toString() {return "toString";};
    QString createCode();
    virtual ~Container() {}
protected:
    QString code;
};

#endif // CONTAINER_H
