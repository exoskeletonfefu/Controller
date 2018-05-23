QT += core network
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = exoskeleton

QMAKE_CXXFLAGS += -g
QMAKE_CXXFLAGS += -g -std=c++11

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
INCLUDEPATH += $$PWD/include /usr/local/include/
#INCLUDEPATH += ../../messages/messages/include

#LIBS += -L../../messages/build-messages-Desktop_Qt_5_9_1_clang_64bit-Debug
#LIBS += -lmessages
#/Users/ilyazuev/CommonUbuntuVB/exoskeleton/Qt/messages/build-messages-Desktop_Qt_5_9_1_clang_64bit-Debug/libmessages.dylib
macx {
    LIBS += -L/usr/local/lib
    LIBS += -ldxl_mac_cpp
}
linux {
    LIBS += -ldxl_x86_cpp
}

SOURCES += main.cpp $$PWD/src/*.cpp
HEADERS += $$PWD/include/*.h
DEFINES += QT_DEPRECATED_WARNINGS
