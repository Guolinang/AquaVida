QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appwindow.cpp \
    databasemanager.cpp \
    filter.cpp \
    loginscreen.cpp \
    main.cpp

HEADERS += \
    appwindow.h \
    databasemanager.h \
    filter.h \
    loginscreen.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    appwindow.ui \
    databasemanager.ui \
    filter.ui \
    loginscreen.ui

RESOURCES += \
    res.qrc
