#ifndef ENCRYPTKEYOFWEBSOCKET_H
#define ENCRYPTKEYOFWEBSOCKET_H
#include <QString>

class Q_DECL_EXPORT EncryptKeyOfWebSocket
{

public:
    static QString encryptKeyOfWebSocket(QString key);
private:
    EncryptKeyOfWebSocket();
};

#endif // ENCRYPTKEYOFWEBSOCKET_H
