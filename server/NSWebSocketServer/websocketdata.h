#ifndef WEBSOCKETDATA_H
#define WEBSOCKETDATA_H

#include <QObject>
#include <QWebSocket>
/**
 * @brief The WebSocketData class : 处理每一个连接的数据
 */
class WebSocketData : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketData(QWebSocket* webSocket,QObject *parent = nullptr);
    ~WebSocketData();

    /**
     * @brief connectTime 获取连接时间点，如果是-1则永久有效，除非客户端自动断开
     * @return
     */
    qint64 connectTime();

    /**
     * @brief webSocketKey 连接的口令，用来识别客户端是否认识
     * @return
     */
    QString webSocketKey();

    /**
     * @brief isValid 连接是否有效
     * @return
     */
    bool isValid();
private:
    void closeWebSocket();
signals:

public slots:
    void binaryMessageReceived(const QByteArray &message);
    void textMessageReceived(const QString &message);
private:
    QWebSocket* const m_webSocket;     //连接的WebSocket
    qint64 m_connectTime;                 //连接时间
    QString m_webSocketKey;            //连接唯一性标识
};

#endif // WEBSOCKETDATA_H
