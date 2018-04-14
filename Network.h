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
public:
    Network(QString service,QHostAddress target = QHostAddress::Broadcast,quint16 port = 6888,QObject * parent = 0);
    ~Network(void);
public slots:
    bool bind(void);    
    void recieveDatagram(void);
    bool sendPacket(QVariantMap map);
signals:
    void recievedPacket(QVariantMap);
    };

#endif /* NETWORK_H */

