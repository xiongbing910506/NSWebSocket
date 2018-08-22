#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDebug>
#include "encryptkeyofwebsocket.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<EncryptKeyOfWebSocket::encryptKeyOfWebSocket(QString("{5652c46a-adf6-4d4f-ab13-ad9a1cc6ae55}"));
    return a.exec();
}
