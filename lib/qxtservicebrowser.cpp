/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtWeb module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/

#include "qxtservicebrowser.h"
#include "qxtservicebrowser_p.h"
#include "qxtdiscoverableservice_p.h"
#include <QSocketNotifier>
#include <QThread>
#include <QLibrary>

/*!
\class QxtServiceBrowser

\inmodule QxtZeroconf

\brief The QxtServiceBrowser class locates Zeroconf-enabled services on the network

QxtServiceBrowser is a tool for locating Zeroconf-enabled services on the local network. When starting
to browse, all existing services reachable on the local network matching the specified search parameters
will be announced with the serviceAdded() signal. Afterward, while browsing, new services apearing on
the network will be announced with the same signal, and services that are closed will be announced with
the serviceRemoved() signal.

Services on the network are identified by a service type and may be further disambiguated by service
subtypes. If any service subtypes are added to the QxtServiceBrowser, only services offering the
specified subtypes will be found. Use the properties inherited from QxtDiscoverableServiceName to
configure the search parameters.

For more information about Zeroconf, see the documentation available on www.zeroconf.org.

\sa QxtDiscoverableService
\sa QxtDiscoverableServiceName
*/

/**
 * Constructs a QxtServiceBrowser that will search for services with the specified type.
 * The service type may be a plain type name, which will default to searching for a UDP
 * service, or it may be provided in the standard format specified by the Zeroconf
 * specification.
 */
QxtServiceBrowser::QxtServiceBrowser(const QString& serviceType, QObject* parent)
		: QObject(parent), QxtDiscoverableServiceName(QString(), serviceType, QString())
{
	QXT_INIT_PRIVATE(QxtServiceBrowser);
	qxt_zeroconf_parse_subtypes(&qxt_d(), serviceType.toUtf8());
}

/**
 * Constructs a QxtServiceBrowser that will search for services with the specified type
 * and socket type.
 */
QxtServiceBrowser::QxtServiceBrowser(const QString& serviceType, QAbstractSocket::SocketType socketType, QObject* parent)
		: QObject(parent), QxtDiscoverableServiceName(QString(), serviceType, QString(), socketType)
{
	QXT_INIT_PRIVATE(QxtServiceBrowser);
	qxt_zeroconf_parse_subtypes(&qxt_d(), serviceType.toUtf8());
}

QxtServiceBrowser::~QxtServiceBrowser()
{
	if (isBrowsing())
		stopBrowsing();
}

bool QxtServiceBrowser::isBrowsing() const
{
	return bool(qxt_d().notifier);
}

void QxtServiceBrowser::browse(/* int iface */)
{
	QStringList subtypes = qxt_d().serviceSubTypes;
	subtypes.prepend(fullServiceType());

        DNSServiceErrorType err;

        QLibrary *lib = new QLibrary("dnssd");
        lib->load();
        if (lib->isLoaded())
        {
            qDebug() << "load success browse";
        }
        else
        {
            qDebug() << "load failed";
        }
        qDebug() << "DNSServiceBrowse service";
        typedef DNSServiceErrorType (*Fun)(DNSServiceRef *,DNSServiceFlags,unsigned int,const char *,const char *,DNSServiceBrowseReply, void*);
        Fun test = (Fun)lib->resolve("DNSServiceBrowse");

        //qDebug() << "qxt-d service:" << qxt_d().service->sockfd << " op:" << qxt_d().service->op;
        if (test)
        {
            qDebug() << "DNSServiceBrowse";
            const char            *regtype = qPrintable(subtypes.join(",_"));
            const char *domain1 =  qPrintable(domain());
//            const char *domain1 =  domain().toStdString().c_str();
//            const char            *regtype = subtypes.join(",_").toStdString().c_str();
            err = test(&(qxt_d().service),
                                   0,
                                   qxt_d().iface,
                                   regtype,
                                   domain1,
                                   QxtServiceBrowserPrivate::browseServiceCallback,
                                   &qxt_d());

            //qDebug() << "err:" << err;
        }

        //lib->unload();

//	err = DNSServiceBrowse(&(qxt_d().service),
//	                       0,
//	                       qxt_d().iface,
//                               qPrintable(subtypes.join(",_")),
//                               qPrintable(domain()),
//                               QxtServiceBrowserPrivate::browseServiceCallback,
//	                       &qxt_d());
	if (err)
	{
		qWarning() << "QxtServiceBrowser: Error browsing" << err;
		emit browsingFailed(err);
	}
	else
        {

//            QLibrary *lib = new QLibrary("dnssd");
//            lib->load();
//            if (lib->isLoaded())
//            {
//                qDebug() << "load success DNSServiceRefSockFD";
//            }
//            else
//            {
//                qDebug() << "load failed";
//            }

            typedef int (*Fun)(DNSServiceRef);
            Fun test1 = (Fun)lib->resolve("DNSServiceRefSockFD");


            qDebug() << "address:" << qxt_d().service;
            qDebug() << "qxd_fd" << qxt_d().service->sockfd << " op" << qxt_d().service->op;

            qDebug() << "testxxx";
            if (test1)
            {
                qDebug() << "before";
                int socket = test1(qxt_d().service);
                qDebug() << "after";
                qxt_d().notifier = new QSocketNotifier(socket, QSocketNotifier::Read, this);
                QObject::connect(qxt_d().notifier, SIGNAL(activated(int)), &qxt_d(), SLOT(socketData()));
            }
            //DNSServiceProcessResult(service);

            lib->unload();

                //qxt_d().notifier = new QSocketNotifier(DNSServiceRefSockFD(qxt_d().service), QSocketNotifier::Read, this);
                //QObject::connect(qxt_d().notifier, SIGNAL(activated(int)), &qxt_d(), SLOT(socketData()));
	}
}

void QxtServiceBrowser::stopBrowsing()
{
	if (qxt_d().notifier)
	{
            QLibrary *lib = new QLibrary("dnssd");
            lib->load();
            if (lib->isLoaded())
            {
                qDebug() << "load success stopBrowsing";
            }
            else
            {
                qDebug() << "load failed";
            }

            typedef void (*Fun)(DNSServiceRef);
            Fun test = (Fun)lib->resolve("DNSServiceRefDeallocate");

            if (test)
            {
                test(qxt_d().service);
            }
            //DNSServiceProcessResult(service);

            lib->unload();

            //DNSServiceRefDeallocate(qxt_d().service);
            qxt_d().notifier->deleteLater();
	}
	qxt_d().notifier = 0;
}

QStringList QxtServiceBrowser::serviceSubTypes() const
{
	return qxt_d().serviceSubTypes;
}

void QxtServiceBrowser::setServiceSubTypes(const QStringList& subtypes)
{
	if (isBrowsing())
		qWarning() << "QxtServiceBrowser: Setting service subtypes while browsing has no effect";
	qxt_d().serviceSubTypes = subtypes;
}

void QxtServiceBrowser::addServiceSubType(const QString& subtype)
{
	if (isBrowsing())
		qWarning() << "QxtServiceBrowser: Setting service subtypes while browsing has no effect";
	qxt_d().serviceSubTypes << subtype;
}

void QxtServiceBrowser::removeServiceSubType(const QString& subtype)
{
	if (isBrowsing())
		qWarning() << "QxtServiceBrowser: Setting service subtypes while browsing has no effect";
	qxt_d().serviceSubTypes.removeAll(subtype);
}

bool QxtServiceBrowser::hasServiceSubType(const QString& subtype)
{
	return qxt_d().serviceSubTypes.contains(subtype);
}

void QxtServiceBrowserPrivate::socketData()
{
    QLibrary *lib = new QLibrary("dnssd");
    lib->load();
    if (lib->isLoaded())
    {
        qDebug() << "load success QxtServiceBrowserPrivate::socketData";
    }
    else
    {
        qDebug() << "load failed";
    }

    typedef DNSServiceErrorType (*Fun)(DNSServiceRef);
    Fun test = (Fun)lib->resolve("DNSServiceProcessResult");

    //qDebug() << "service:" << service->sockfd;
    if (test)
    {
        qDebug() << "service";
        test(service);
        qDebug() << "service1";
    }

    lib->unload();

    //DNSServiceProcessResult(service);
}

void QxtServiceBrowserPrivate::browseServiceCallback(DNSServiceRef service, DNSServiceFlags flags, quint32 iface,
        DNSServiceErrorType errCode, const char* serviceName, const char* regtype, const char* replyDomain, void* context)
{
	Q_UNUSED(service);
        Q_UNUSED(iface);
	Q_UNUSED(regtype);
	QxtServiceBrowserPrivate* self = reinterpret_cast<QxtServiceBrowserPrivate*>(context);
	if (errCode == kDNSServiceErr_NoError)
	{
		if (flags & kDNSServiceFlagsAdd)
			emit self->qxt_p().serviceAdded(serviceName, replyDomain);
		else
			emit self->qxt_p().serviceRemoved(serviceName, replyDomain);
	}
	else
	{
		emit self->qxt_p().stopBrowsing();
		
		qWarning() << "QxtServiceBrowser: Error browsing" << errCode;
		emit self->qxt_p().browsingFailed(errCode);
	}
}
