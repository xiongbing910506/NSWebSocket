#include "encryptkeyofwebsocket.h"

#include <QCryptographicHash>
QString EncryptKeyOfWebSocket::encryptKeyOfWebSocket(QString key)
{
    return QCryptographicHash::hash(key.toUtf8(),QCryptographicHash::Md5).toHex();
}

EncryptKeyOfWebSocket::EncryptKeyOfWebSocket()
{
}
