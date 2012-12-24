QT += network

TEMPLATE = lib

DEFINES += QTRPC2_BUILD_LIB

CONFIG -= debug \
        exceptions \
        stl

CONFIG += dll \
        release

INCLUDEPATH += ./lib ../include ./include

HEADERS += lib/returnvalue.h \
        lib/signature.h \
        lib/proxybase.h \
        lib/clientprotocolthread.h \
        lib/clientmessagebus.h \
        lib/clientprotocolbase.h \
        lib/clientproxy.h \
        lib/server.h \
        lib/serviceproxy.h \
        lib/clientprotocoltest.h \
        lib/serverprotocolinstancebase.h \
        lib/serverprotocollistenerbase.h \
        lib/serverthread.h \
        lib/serverprotocollistenertcp.h \
        lib/serverprotocolinstanceiodevice.h \
        lib/message.h \
        lib/serverprotocolinstancetcp.h \
        lib/clientprotocoltcp.h \
        lib/clientprotocoliodevice.h \
        lib/serverprotocollistenerprocess.h \
        lib/servicefactory.h \
        lib/servicepublisher.h \
        lib/servicepublisher_p.h \
        lib/servicefinder.h \
        lib/servicefinder_p.h \
        lib/server_p.h \
        lib/clientproxy_p.h \
        lib/clientmessagebus_p.h \
        lib/clientprotocolbase_p.h \
        lib/clientprotocoliodevice_p.h \
        lib/clientprotocoltcp_p.h \
        lib/clientprotocolthread_p.h \
        lib/message_p.h \
        lib/proxybase_p.h \
        lib/returnvalue_p.h \
        lib/serverprotocolinstancebase_p.h \
        lib/serverprotocolinstanceiodevice_p.h \
        lib/serverprotocolinstancetcp_p.h \
        lib/serverprotocollistenerbase_p.h \
        lib/serverprotocollistenerprocess_p.h \
        lib/serverprotocollistenertcp_p.h \
        lib/serverthread_p.h \
        lib/signature_p.h \
        lib/serviceproxy_p.h \
        lib/clientprotocoltest_p.h \
        lib/qtrpcprivate.h \
        lib/authtoken.h \
        lib/authtoken_p.h \
        lib/servicefactoryparent_p.h \
        lib/automaticmetatyperegistry.h \
        lib/qxtdiscoverableservice.h \
        lib/qxtdiscoverableservicename.h \
        lib/qxtdiscoverableservice_p.h \
        lib/qxtservicebrowser.h \
        lib/qxtservicebrowser_p.h \
        lib/qxtzeroconf.h \
        lib/qxtmdns.h \
        lib/sleeper.h \
        lib/qtrpcglobal.h


SOURCES += lib/returnvalue.cpp \
        lib/signature.cpp \
        lib/proxybase.cpp \
        lib/clientmessagebus.cpp \
        lib/clientprotocolthread.cpp \
        lib/clientprotocolbase.cpp \
        lib/clientproxy.cpp \
        lib/server.cpp \
        lib/serviceproxy.cpp \
        lib/clientprotocoltest.cpp \
        lib/serverprotocolinstancebase.cpp \
        lib/serverprotocollistenerbase.cpp \
        lib/serverthread.cpp \
        lib/serverprotocollistenertcp.cpp \
        lib/serverprotocolinstanceiodevice.cpp \
        lib/message.cpp \
        lib/serverprotocolinstancetcp.cpp \
        lib/clientprotocoltcp.cpp \
        lib/clientprotocoliodevice.cpp \
        lib/serverprotocollistenerprocess.cpp \
        lib/servicepublisher.cpp \
        lib/servicefinder.cpp \
        lib/authtoken.cpp \
        lib/servicefactoryparent.cpp \
        lib/qxtdiscoverableservice.cpp \
        lib/qxtdiscoverableservicename.cpp \
        lib/qxtservicebrowser.cpp

unix { \
LIBS += -ldns_sd
SOURCES += lib/qxtmdns_avahi.cpp \
        lib/qxtavahipoll.cpp
HEADERS += lib/qxtmdns_avahi.h \
        lib/qxtmdns_avahi_p.h \
        lib/qxtavahipoll.h \
        lib/qxtavahipoll_p.h
LIBS += -lavahi-client -lavahi-common

SOURCES += lib/clientprotocolsocket.cpp \
        lib/serverprotocollistenersocket.cpp \
        lib/serverprotocolinstancesocket.cpp
HEADERS += serverprotocollistenersocket_p.h \
        serverprotocolinstancesocket_p.h \
        clientprotocolsocket_p.h \
        serverprotocollistenersocket.h \
        serverprotocolinstancesocket.h \
        clientprotocolsocket.h
}

win32 { \
    SOURCES += lib/qxtmdns_bonjour.cpp
    HEADERS += lib/qxtmdns_bonjour.h
    INCLUDEPATH += $$quote("C:/Program Files/Bonjour SDK/Include/")
    #LIBS += -L./lib/x64 -ldnssd
    #LIBS += $$quote(C:/rds/qtrpc2/dnssd.dll)
}

DISTFILES += include/ReturnValue \
        include/Signature \
        include/TmpArgument \
        include/ClientProtocolThread \
        include/ClientMessageBus \
        include/ClientProtocolBase \
        include/ProxyBase \
        include/ClientProtocolTest \
        include/Server \
        include/ServiceProxy \
        include/ServerProtocolListenerBase \
        include/ServerProtocolInstanceBase \
        include/ServerThread \
        include/ServerProtocolListenerTcp \
        include/Message \
        include/ServerProtocolInstanceIODevice \
        include/ServerProtocolInstanceTcp \
        include/ClientProtocolTcp \
        include/ClientProtocolIODevice \
        include/ClientProtocolSocket \
        include/ServerProtocolListenerProcess \
        include/ServiceFactory \
        include/ServicePublisher \
        include/ServiceFinder \
        include/QSharedPointer \
        include/AuthToken \
        include/QtRpcSharedPointer \
        include/AutomaticMetatypeRegistry
