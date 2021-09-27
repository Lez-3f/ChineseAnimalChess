QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets gui network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AboutWnd.cpp \
    ChooseGameMode.cpp \
    CtrlPanel.cpp \
    GameWnd.cpp \
    Main.cpp \
    MultiGameMode.cpp \
    NetWorkGameMode.cpp \
    SingleGameMode.cpp \
    StartGameWnd.cpp \
    Step.cpp \
    Stone.cpp \
    Board.cpp

HEADERS += \
    AboutWnd.h \
    Board.h \
    ChooseGameMode.h \
    CtrlPanel.h \
    GameWnd.h \
    MultiGameMode.h \
    NetWorkGameMode.h \
    SingleGameMode.h \
    StartGameWnd.h \
    Step.h \
    Stone.h

FORMS += \
    AboutWnd.ui \
    Board.ui \
    StartGameWnd.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    animals.png

RESOURCES += \
    image.qrc
