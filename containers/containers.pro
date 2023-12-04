QT -= gui
QT += widgets
QT += xml
QT += network
#CONFIG += c++11 console
#CONFIG += c++14
CONFIG += c++11
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        abstractfactory.cpp \
        box.cpp \
        code.cpp \
        container.cpp \
        containerfactory.cpp \
        containerlist.cpp \
        containerlistmemento.cpp \
        cylinder.cpp \
        main.cpp \
        mainclient.cpp \
        pallet.cpp \
        palletlist.cpp \
        writexml.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    abstractfactory.h \
    box.h \
    code.h \
    container.h \
    containerfactory.h \
    containerlist.h \
    containerlistmemento.h \
    cylinder.h \
    mainclient.h \
    pallet.h \
    palletlist.h \
    writexml.h

RESOURCES += \
    resources.qrc
