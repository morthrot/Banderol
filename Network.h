#ifndef NETWORK_H
#define	NETWORK_H

#include <QtCore>
#include <QtNetwork>

class Network : public QObject {
    Q_OBJECT
private:
    QString _service;
    QHostAddress _target;
    quint16 _port;
    QUdpSocket * _channel;
    unsigned int _uid;
public:
    Network(QString service,QHostAddress target = QHostAddress::Broadcast,quint16 port = 6888,QObject * parent = 0);
    ~Network(void);
public slots:
    bool bind(void);    
    void recieveDatagram(void);

    bool sendDatagram(const QByteArray & bytes);
    bool sendPacket(const QVariantMap & map);
    bool sendMessage(const QString & nick,const QString & message);
signals:
    void recievedDatagram(QByteArray); // bytes
    void recievedPacket(QVariantMap); // map
    void recievedMessage(QString,QString); // nick, message
    };

#endif /* NETWORK_H */

