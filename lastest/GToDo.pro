#-------------------------------------------------
#
# Project created by QtCreator 2022-11-06T21:07:51
#
#-------------------------------------------------

QT += core gui sql printsupport multimedia axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_ICONS = logo.ico
TARGET = GTDO
TEMPLATE = app
#CONFIG += resources_big
QT +=sql
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
    GBtnRroup.cpp \
    GNotifyMessage.cpp \
    GQstringDate.cpp \
    GSplashScreen.cpp \
    GToDo.cpp \
    GToDoItem.cpp \
    Main.cpp \
    form.cpp

HEADERS += \
    GBtnRroup.h \
    GNotifyMessage.h \
    GQstringDate.h \
    GSplashScreen.h \
    GToDo.h \
    GToDoItem.h \
    form.h

FORMS += \
    GBtnRroup.ui \
    GNotifyMessage.ui \
    GSplashScreen.ui \
    GToDo.ui \
    GToDoItem.ui \
    form.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += image.qrc

TRANSLATIONS = language\lan_cn.ts\
                language\lan_tw.ts\
                language\lan_en.ts
DISTFILES += \
    Total.qml \
    TotalForm.ui.qml
