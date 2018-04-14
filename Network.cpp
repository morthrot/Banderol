#include "Network.h"

Network::Network(QString service,QHostAddress target,quint16 port,QObject * parent) : QObject(parent) {
    _service = service;
    _target = target;
    _port = port;

    _channel = new QUdpSocket(this);
    connect(_channel,SIGNAL(readyRead()),this,SLOT(recieveDatagram()));
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
        
        QDataStream ds(bytes);
        ds.setVersion(QDataStream::Qt_4_7);
        
        QVariantMap map;
        ds >> map;
        
        if(map.value("service").toString() != _service) { continue; }
        
        emit recievedPacket(map);
        }
    }

bool Network::sendPacket(QVariantMap map) {
    if(_channel->state() != QAbstractSocket::BoundState) { return false; }

    map["service"] = _service;
    
    QByteArray bytes;
    
    QDataStream ds(&bytes,QIODevice::WriteOnly);
    ds.setVersion(QDataStream::Qt_4_7);
    ds << map;
    
    _channel->writeDatagram(bytes,_target,_port);
    return true;
    }
