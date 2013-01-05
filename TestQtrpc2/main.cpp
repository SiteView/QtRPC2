#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QApplication>
#include <Server>
#include <ServerProtocolListenerTcp>
#include <QDebug>
#include <ServicePublisher>
#include "basicservice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Create a server object with default threading options
    Server srv;

    //Create a TCP listener object
    ServerProtocolListenerTcp tcp(&srv);

        qDebug() << "test123";
    //Listen on port 10123 on all network interfaces
    if(!tcp.listen(QHostAddress::Any, 10123))
    {
        //This function returns false if the port is busy
        qCritical() << "Failed to listen on port 10123!";
        return(1);
    }

    //Register a service. The template argument is the ServiceProxy class to use
    //The string argument is the name used to connect to the service
    //A new instance of the BasicService class is created each time a client connects
    //a pointer to an instance of the service is returned.
    ServiceProxy *service = srv.registerService<BasicService>("MyService");

    //Create a service publisher object based on the service object we just registered
    ServicePublisher pub(service);

    pub.setFriendlyName("MyService");
    //Set the port the service is on
    pub.setPort(10123);
    //Publish the service
    pub.publish();

    MainWindow w;
    w.show();

    return a.exec();
}
