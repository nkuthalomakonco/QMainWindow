#include "code.h"

code::code(QString type, int count){
    m_type = "C";
    if(type=="box")m_type = "B";
    m_code = QDate::currentDate().toString("yyyy/MM") + "/" + m_type
            + QString::number(count + 1);
}

code::~code()
{

}

QString code::getCode(){return m_code;}
