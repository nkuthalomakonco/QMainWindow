#ifndef CONTAINER_H
#define CONTAINER_H

#include <QString>
#include <QDate>
#include <QObject>


class Container: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString code READ getCode WRITE setCode)
    Q_PROPERTY(int height READ getHeight WRITE setHeight)
    Q_PROPERTY(int weight READ getWeight WRITE setWeight)

public:
    Container();
    Container(QString c);
    Container(QString c,int h,int w);
    virtual int getVolume() = 0;
    virtual QString toString() = 0;
    virtual ~Container(){};
    int getHeight() const;
    void setHeight(int value);
    QString getCode() const;
    void setCode(const QString &value);
    int getWeight() const;
    void setWeight(int value);

protected:
    QString code;
    int height;
    int weight;
};

#endif // CONTAINER_H
