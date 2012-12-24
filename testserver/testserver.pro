#-------------------------------------------------
#
# Project created by QtCreator 2012-12-19T14:32:33
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = testserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../lib ../include

SOURCES += main.cpp \
    callerservice.cpp \
    testsyncroserver.cpp \
    testserver.cpp

HEADERS += \
    callerservice.h \
    testsyncroserver.h \
    testserver.h

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
