/***************************************************************************
 *  Copyright (c) 2010, Resara LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Resara LLC nor the
 *       names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL RESARA LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***************************************************************************/
#include "basicservice.h"
#include <QDebug>

//This is run after a client connects, but before authentication takes place.
//You can do initializtion here, but do nothing that requires authentication.
BasicService::BasicService(QObject *parent) :
    ServiceProxy(parent)
{
}

//Authentication function. Check for a username and password.
//If either is incorrect, an error is returned.
//
//To return an authentication failure, use
//return(ReturnValue(1,"Incorrect username or password"));
//The first argument is the error number, the second is the error string.
//Both values can be set to anything, and only have value to the application
ReturnValue BasicService::auth(QString user, QString pass)
{
    if((user == "joe") && (pass == "secret"))
        return(true);
    else
        return(ReturnValue(1,"Incorrect username or password."));
}

//Adds two numbers, and returns the result. This function is called by the client.
//If for some reason a failure needs to be returned
//Use the same process as the auth() function uses.
ReturnValue BasicService::addNumbers(int a, int b)
{
    qDebug() << "addNumbers() called.";
    return(a + b);
}

//This function returns an error. Errors can be generated by the application
//such as in this case, or they can be generated by the library.
ReturnValue BasicService::returnError()
{
    return(ReturnValue(123, "Function Not Implemented"));
}
