#ifndef CODE_H
#define CODE_H

#include <QString>
#include <QDate>

class code
{     
private:
    void creatCode(){
          m_count = m_codes.size();
          QString abc = m_containerType.at(qrand() % m_containerType.size());//get A,B,C
          m_code = QDate::currentDate().toString("yyyy/MM") + "/" + abc
                  + QString::number(m_count + 1);
      }
public:
      code(QStringList cList){
          m_codes = cList;}
      QString getCode(){creatCode();return m_code;}
      QString m_code;
      int m_count;
      QStringList m_codes;
      QStringList m_containerType = { "A", "B", "C" };
      QDate m_date;
};

#endif // CODE_H
