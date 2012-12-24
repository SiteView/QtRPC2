#-------------------------------------------------
#
# Project created by QtCreator 2012-12-19T14:48:48
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = basic_server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    basicservice.cpp

HEADERS += \
    basicservice.h

DISTFILES += ../../include/ReturnValue \
        ../../include/Signature \
        ../../include/TmpArgument \
        ../../include/ClientProtocolThread \
        ../../include/ClientMessageBus \
        ../../include/ClientProtocolBase \
        ../../include/ProxyBase \
        ../../include/ClientProtocolTest \
        ../../include/Server \
        ../../include/ServiceProxy \
        ../../include/ServerProtocolListenerBase \
        ../../include/ServerProtocolInstanceBase \
        ../../include/ServerThread \
        ../../include/ServerProtocolListenerTcp \
        ../../include/Message \
        ../../include/ServerProtocolInstanceIODevice \
        ../../include/ServerProtocolInstanceTcp \
        ../../include/ClientProtocolTcp \
        ../../include/ClientProtocolIODevice \
        ../../include/ClientProtocolSocket \
        ../../include/ServerProtocolListenerProcess \
        ../../include/ServiceFactory \
        ../../include/ServicePublisher \
        ../../include/ServiceFinder \
        ../../include/QSharedPointer \
        ../../include/AuthToken \
        ../../include/QtRpcSharedPointer \
        ../../include/AutomaticMetatypeRegistry
