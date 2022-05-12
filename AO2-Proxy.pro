QT -= gui
QT += network websockets

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/main.cpp \
        src/tcpsocketclient.cpp \
        src/tcpsocketserver.cpp \
        src/websocketclient.cpp \
        src/configmanager.cpp

HEADERS += \
    include/tcpsocketclient.h \
    include/tcpsocketserver.h \
    include/websocketclient.h \
    include/configmanager.h


CONFIG -= \
        copy_dir_files \
        debug_and_release \
        debug_and_release_target

DESTDIR = $$PWD/bin

INCLUDEPATH = $$PWD/include
