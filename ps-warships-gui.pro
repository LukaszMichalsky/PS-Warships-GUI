QT       += core gui network widgets
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    application.cpp \
    pages/join-game.cpp \
    pages/main-menu.cpp \
    pages/start-server.cpp

HEADERS += \
    application.h

FORMS += \
    application.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
