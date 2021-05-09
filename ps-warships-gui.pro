QT += core gui network widgets
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
  logic/logic.cpp \
  logic/point.cpp \
  main.cpp \
  application.cpp \
  pages/board-build-random.cpp \
  pages/board-build.cpp \
  pages/join-game.cpp \
  pages/main-menu.cpp \
  pages/start-server.cpp

HEADERS += \
  application.h \
  logic/logic.h \
  logic/point.h

FORMS += \
  application.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
