QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editionarea.cpp \
    filterarea.cpp \
    libraryarea.cpp \
    main.cpp \
    imagedit.cpp \
    rognerarea.cpp \
    selectionaera.cpp \
    settingarea.cpp \
    toolboxarea.cpp

HEADERS += \
    editionarea.h \
    filterarea.h \
    imagedit.h \
    libraryarea.h \
    rognerarea.h \
    selectionaera.h \
    settingarea.h \
    toolboxarea.h

FORMS += \
    editionarea.ui \
    filterarea.ui \
    imagedit.ui \
    libraryarea.ui \
    rognerarea.ui \
    selectionaera.ui \
    settingarea.ui \
    toolboxarea.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Icone/Icone_selection.png
