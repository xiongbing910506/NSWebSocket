#include "websocektserver.h"
#include <QDebug>
#include <QDateTime>
#include "websocketpublic.h"

WebSocektServer::WebSocektServer(QObject *parent) : QObject(parent)
{
    m_webSocketServer = nullptr;
    m_time = startTimer(1000);
}

void WebSocektServer::initWebSocket()
{
    if(nullptr == m_webSocketServer){
        m_webSocketServer = new QWebSocketServer("websocket of roboot in NiceChina",QWebSocketServer::NonSecureMode);
        connect(m_webSocketServer,SIGNAL(newConnection()),this,SLOT(newConnection()));
    }
    bool result = m_webSocketServer->listen(QHostAddress::Any,NS_WEBSOCKET_PORT);
    if(result){
        qDebug()<<"初始化成功";
    }
}

void WebSocektServer::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_time){
        //定时清除不可用的连接，连接数
        int index = m_waitCheckedSocketList.size() - 1;
        //用来转移连接以及清除超时的连接
        while(index > -1){
            WebSocketData* data = m_waitCheckedSocketList.at(index);
            qint64 currentTime = QDateTime::currentSecsSinceEpoch();
            qint64 connectTime = data->connectTime();
            if(connectTime == -1 && data->isValid())
            {
               m_waitCheckedSocketList.removeAt(index);
               m_connectedSocketList.append(data);
            }else{
                if(!(data->isValid()) || (currentTime - connectTime > NS_OVERTIME_SEC)){
                    m_waitCheckedSocketList.removeAt(index);
                    delete data;
                }
            }
            index--;
        }
        //用来限制连接个数
        while(m_connectedSocketList.length() > NS_WEBSOCKET_COUNT){
            WebSocketData* data = m_connectedSocketList.takeFirst();
            delete data;
        }
    }
}

void WebSocektServer::newConnection()
{
    QWebSocket *webSocket = m_webSocketServer->nextPendingConnection();
    WebSocketData *webSocketData = new WebSocketData(webSocket);
    webSocket->sendTextMessage(webSocketData->webSocketKey());
    m_waitCheckedSocketList.append(webSocketData);
}
