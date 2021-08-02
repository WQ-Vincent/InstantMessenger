QT       += core gui sql
QT +=xml
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addfrd.cpp \
    changepw.cpp \
    database.cpp \
    inform.cpp \
    listwidget.cpp \
    listwidget2.cpp \
    login.cpp \
    loginlose.cpp \
    main.cpp \
    mainwindow.cpp \
    pwback.cpp \
    qnchatmessage.cpp \
    regist.cpp \
    setting.cpp \
    tabwidget.cpp

HEADERS += \
    addfrd.h \
    changepw.h \
    database.h \
    inform.h \
    listwidget.h \
    listwidget2.h \
    login.h \
    loginlose.h \
    mainwindow.h \
    pwback.h \
    qnchatmessage.h \
    regist.h \
    setting.h \
    tabwidget.h

FORMS += \
    addfrd.ui \
    changepw.ui \
    inform.ui \
    login.ui \
    loginlose.ui \
    mainwindow.ui \
    pwback.ui \
    regist.ui \
    setting.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    wbb.jpg

RESOURCES += \
    image.qrc
