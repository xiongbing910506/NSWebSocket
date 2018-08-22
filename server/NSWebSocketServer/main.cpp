#include <QCoreApplication>
#include "websocektserver.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WebSocektServer webSocketServer;
    webSocketServer.initWebSocket();
    return a.exec();
}
