#-------------------------------------------------
#
# Project created by QtCreator 2022-11-06T21:07:51
#
#-------------------------------------------------

QT += core gui sql printsupport multimedia axcontainer
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_ICONS = logo.ico
TARGET = GTDO
TEMPLATE = app
#CONFIG += resources_big

DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
    GBtnRroup.cpp \
    GNotifyMessage.cpp \
    GQstringDate.cpp \
    GToDo.cpp \
    GToDoItem.cpp \
    Main.cpp \
    PageSetting.cpp \
    page_mini.cpp \
    widget.cpp

HEADERS += \
    GBtnRroup.h \
    GNotifyMessage.h \
    GQstringDate.h \
    GToDo.h \
    GToDoItem.h \
    PageSetting.h \
    page_mini.h \
    widget.h

FORMS += \
    GBtnRroup.ui \
    GNotifyMessage.ui \
    GToDo.ui \
    GToDoItem.ui \
    PageSetting.ui \
    page_mini.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += image.qrc

TRANSLATIONS = language\lan_cn.ts\
                language\lan_tw.ts\
                language\lan_en.ts
DISTFILES +=
