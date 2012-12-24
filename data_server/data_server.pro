#-------------------------------------------------
#
# Project created by QtCreator 2012-12-19T16:21:08
#
#-------------------------------------------------

QT       += core network gui

TARGET = data_server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../include ../lib


SOURCES += main.cpp \
    dataservice.cpp \
    basicservice.cpp

HEADERS += \
    dataservice.h \
    basicservice.h

LIBS += -L../debug -lqtrpc2

DISTFILES += ../include/ReturnValue \
        ../include/Signature \
        ../include/TmpArgument \
        ../include/ClientProtocolThread \
        ../include/ClientMessageBus \
        ../include/ClientProtocolBase \
        ../include/ProxyBase \
        ../include/ClientProtocolTest \
        ../include/Server \
        ../include/ServiceProxy \
        ../include/ServerProtocolListenerBase \
        ../include/ServerProtocolInstanceBase \
        ../include/ServerThread \
        ../include/ServerProtocolListenerTcp \
        ../include/Message \
        ../include/ServerProtocolInstanceIODevice \
        ../include/ServerProtocolInstanceTcp \
        ../include/ClientProtocolTcp \
        ../include/ClientProtocolIODevice \
        ../include/ClientProtocolSocket \
        ../include/ServerProtocolListenerProcess \
        ../include/ServiceFactory \
        ../include/ServicePublisher \
        ../include/ServiceFinder \
        ../include/QSharedPointer \
        ../include/AuthToken \
        ../include/QtRpcSharedPointer \
        ../include/AutomaticMetatypeRegistry
