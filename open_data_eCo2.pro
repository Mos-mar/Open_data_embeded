TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        datafetch.cpp \
        main.cpp
LIBS += -lgd -L/usr/include/gd.h
LIBS += -lcurl

HEADERS += \
    datafetch.h

