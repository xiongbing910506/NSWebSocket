#include "websocketdata.h"
#include <QUuid>
#include <QDateTime>
#include <QCryptographicHash>
WebSocketData::WebSocketData(QWebSocket *webSocket, QObject *parent)
    : QObject(parent),m_webSocket(webSocket)
{
    m_webSocketKey = QUuid::createUuid().toString();
    m_connectTime = QDateTime::currentSecsSinceEpoch();
    connect(m_webSocket,SIGNAL(binaryMessageReceived(QByteArray)),this,SLOT(binaryMessageReceived(QByteArray)));
    connect(m_webSocket,SIGNAL(textMessageReceived(QString)),this,SLOT(textMessageReceived(QString)));
}

WebSocketData::~WebSocketData()
{
    this->closeWebSocket();
}

qint64 WebSocketData::connectTime()
{
    return m_connectTime;
}

QString WebSocketData::webSocketKey()
{
    return m_webSocketKey;
}

bool WebSocketData::isValid()
{
    return m_webSocket->isValid();
}

void WebSocketData::closeWebSocket()
{
    if(m_webSocket->isValid()){
        m_webSocket->close(QWebSocketProtocol::CloseCodeNormal,QString("数据处理机被释放..."));
    }
}

void WebSocketData::binaryMessageReceived(const QByteArray &message)
{
    QString md5 = QCryptographicHash::hash(m_webSocketKey.toUtf8(),QCryptographicHash::Md5).toHex();
    if(m_connectTime != -1){
        //连接校验
        if(QString(message) == md5){
            m_connectTime = -1;
            m_webSocket->sendTextMessage("连接成功,正式接通数据...");
        }else{
            this->closeWebSocket();
        }
    }
    else{
        //处理数据
    }
}

void WebSocketData::textMessageReceived(const QString &message)
{
    QString md5 = QCryptographicHash::hash(m_webSocketKey.toUtf8(),QCryptographicHash::Md5).toHex();
    if(m_connectTime != -1){
        //连接校验
        if(message == md5){
            m_connectTime = -1;
            m_webSocket->sendTextMessage("连接成功,正式接通数据...");
        }else{
            this->closeWebSocket();
        }
    }
    else{
        //处理数据
        qDebug()<<message;
    }
}

