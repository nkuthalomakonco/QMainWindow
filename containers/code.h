#ifndef CODE_H
#define CODE_H

#include <QString>
#include <QDate>

class code
{     
private:
    QString m_code;
    QString m_type;
public:
    code(QString type,int count);
    ~code();
    QString getCode();
};

#endif // CODE_H
