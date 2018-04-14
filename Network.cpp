#include "Network.h"

Network::Network(QString service,QHostAddress target,quint16 port,QObject * parent) : QObject(parent) {
    _service = service;
    _target = target;
    _port = port;

    _channel = new QUdpSocket(this);
    connect(_channel,SIGNAL(readyRead()),this,SLOT(recieveDatagram()));

    _uid = rand();
    }

Network::~Network(void) {
    }

bool Network::bind(void) {
    if(_channel->state() != QAbstractSocket::UnconnectedState) { return false; }
    
    bool bind_ok = _channel->bind(QHostAddress::Any,_port,QUdpSocket::ShareAddress);
    if(bind_ok == false) { return false; }
    
    return true;
    }

void Network::recieveDatagram(void) {
    while(_channel->hasPendingDatagrams() == true) {
        QByteArray bytes(_channel->pendingDatagramSize(),0x00);
        _channel->readDatagram(bytes.data(),bytes.length(),NULL,NULL);
        
        emit recievedDatagram(bytes);

        QDataStream ds(bytes);
        ds.setVersion(QDataStream::Qt_4_7);
        
        QVariantMap map;
        ds >> map;
        
        if(map.value("service").toString() != _service) { continue; }
        
        emit recievedPacket(map);

        if(map.contains("uid") == false) { continue; }

        unsigned int uid = map.value("uid").toUInt();
        if(uid == _uid) { continue; }

        _uid = uid;

        QString nick = map.value("nick").toString();
        if(nick.isEmpty() == true) { continue; }

        QString message = map.value("message").toString();
        if(message.isEmpty() == true) { continue; }

        emit recievedMessage(nick,message);
        }
    }

bool Network::sendDatagram(const QByteArray & bytes) {
    if(_channel->state() != QAbstractSocket::BoundState) { return false; }
    qint64 written = _channel->writeDatagram(bytes,_target,_port);
    return (written == bytes.length() ? true : false);
    }

bool Network::sendPacket(const QVariantMap & map) {
    QByteArray bytes;
    
    QDataStream ds(&bytes,QIODevice::WriteOnly);
    ds.setVersion(QDataStream::Qt_4_7);
    ds << map;
    
    return sendDatagram(bytes);
    }

bool Network::sendMessage(const QString & nick,const QString & message) {
    QVariantMap map;

    map["uid"] = rand();
    map["service"] = _service;
    map["nick"] = nick;
    map["message"] = message;

    return sendPacket(map);
    }
