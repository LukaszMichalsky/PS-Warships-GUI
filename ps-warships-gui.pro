QT += core gui network widgets
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
  chat-window.cpp \
  graphic-board.cpp \
  graphic-board/clickedWithState/clicked-creating.cpp \
  graphic-board/clickedWithState/clicked-playing.cpp \
  graphic-board/get-clicked-point.cpp \
  graphic-board/ghost-mode.cpp \
  graphic-board/init-board.cpp \
  graphic-board/init-resources.cpp \
  graphic-board/redraw.cpp \
  logic/get-opponent-action.cpp \
  logic/logic.cpp \
  logic/network-data.cpp \
  logic/opponent-board-field-selected.cpp \
  logic/point.cpp \
  logic/randomize-board.cpp \
  logic/set-drowned-ship.cpp \
  logic/shooting.cpp \
  logic/start-game.cpp \
  main.cpp \
  application.cpp \
  pages/board-build-manual.cpp \
  pages/board-build-random.cpp \
  pages/board-build.cpp \
  pages/game-phase.cpp \
  pages/join-game.cpp \
  pages/main-menu.cpp \
  pages/start-server.cpp

HEADERS += \
  application.h \
  chat-window.h \
  graphic-board.h \
  logic/logic.h \
  logic/point.h

FORMS += \
  application.ui \
  chat-window.ui

RESOURCES += \
  resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
