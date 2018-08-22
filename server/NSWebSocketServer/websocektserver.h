#ifndef WEBSOCEKTSERVER_H
#define WEBSOCEKTSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QTimerEvent>
#include "websocketdata.h"
//校验机制将连接口令交个客户端，客户端给与MD5加密值然后返回，如果超时10s直接断开连接
class WebSocektServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocektServer(QObject *parent = nullptr);

    void initWebSocket();
protected:
    void timerEvent(QTimerEvent *event);
signals:

public slots:
    void newConnection();
private:
    QWebSocketServer* m_webSocketServer;
    QList<WebSocketData*> m_waitCheckedSocketList; //等待校验的SOCKET
    QList<WebSocketData*> m_connectedSocketList;
    QWebSocket* m_webSocket;
    int m_time;
};

#endif // WEBSOCEKTSERVER_H
