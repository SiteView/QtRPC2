/***************************************************************************
 *  Copyright (c) 2011, Resara LLC                                         *
 *  All rights reserved.                                                   *
 *                                                                         *
 *  Redistribution and use in source and binary forms, with or without     *
 *  modification, are permitted provided that the following conditions are *
 *  met:                                                                   *
 *      * Redistributions of source code must retain the above copyright   *
 *        notice, this list of conditions and the following disclaimer.    *
 *      * Redistributions in binary form must reproduce the above          *
 *        copyright notice, this list of conditions and the following      *
 *        disclaimer in the documentation and/or other materials           *
 *        provided with the distribution.                                  *
 *      * Neither the name of Resara LLC nor the names of its              *
 *        contributors may be used to endorse or promote products          *
 *        derived from this software without specific prior written        *
 *        permission.                                                      *
 *                                                                         *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    *
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  *
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL RESARA LLC BE   *
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR    *
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF   *
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR        *
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,  *
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE   *
 *  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN *
 *  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                          *
 *                                                                         *
 ***************************************************************************/
#ifndef RETURNVALUE_P_H
#define RETURNVALUE_P_H

#include <QxtPimpl>
#include <QSharedData>
#include <ServiceProxy>
#include <QPointer>
#include <QSharedPointer>
#include "clientproxy_p.h"
#include "returnvalue.h"
#include <qtrpcprivate.h>

namespace QtRpc
{


/**
	@author Chris Vickery <chris@resara.com>
 */
class ReturnValueData : public QSharedData
{
public:
	~ReturnValueData()
	{
		// I guess this doesn't need to be done, because it should be done by whatever is reveiving the pointer..
// 		if (service.isNull() && rawServicePointer != 0)
// 			delete rawServicePointer;
	}
	enum ReturnValueType
	{
		Variant,
		Error,
		Service,
		Asyncronous
	};
	ReturnValueData();
	ReturnValueType type;
	uint number;
	QString string;
	ServiceProxy* rawServicePointer;
	QSharedPointer<ServiceProxy> service; //private api.... This is the server side holder for service's weak pointers...
	QSharedPointer<ServiceData> serviceData; //private api... This is the client side service thing, not service proxy
	quint32 serviceId;
};

/**
	@author Chris Vickery <chris@resara.com>
*/
class ReturnValuePrivate : public QxtPrivate<ReturnValue>
{
public:
	ReturnValuePrivate()
	{
	}
	QSharedDataPointer<ReturnValueData> data;

private:
	Q_DISABLE_COPY(ReturnValuePrivate);

};
}
#endif
