#-------------------------------------------------
#
# Project created by QtCreator 2013-01-09T16:12:33
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = dnssdsample
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lws2_32
LIBS += -L./lib -ldnssd

DEFINES += WIN32 \
            _WIN32 \
            _DEBUG \
            _CONSOLE \
            NOT_HAVE_GETOPT \
            NOT_HAVE_SETLINEBUF \
            WIN32_LEAN_AND_MEAN \
            _CRT_SECURE_NO_DEPRECATE \
            _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES=1

SOURCES += \
    dns-sd.c \
    ClientCommon.c

HEADERS += \
    dns_sd.h \
    ClientCommon.h
