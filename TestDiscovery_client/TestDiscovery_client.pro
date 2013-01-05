#-------------------------------------------------
#
# Project created by QtCreator 2012-12-25T13:17:23
#
#-------------------------------------------------

QT       += core network gui

TARGET = TestDiscovery_client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    testobject.cpp \
    basicservice.cpp

HEADERS  += mainwindow.h \
    testobject.h \
    basicservice.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../include ../lib

LIBS += -L../Debug -lqtrpc2

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

