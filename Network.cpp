/*

Copyright (c) 2018 Д.С. Андреев

Этот файл — часть Banderol.

Banderol - свободная программа: вы можете перераспространять ее и/или
изменять ее на условиях Стандартной общественной лицензии GNU в том виде,
в каком она была опубликована Фондом свободного программного обеспечения;
либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
версии.

Письмуй распространяется в надежде, что она будет полезной,
но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
общественной лицензии GNU.

Вы должны были получить копию Стандартной общественной лицензии GNU
вместе с этой программой. Если это не так, см.
<http://www.gnu.org/licenses/>.)


This file is part of Banderol.

Banderol is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Composer is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Composer.  If not, see <http://www.gnu.org/licenses/>.

*/

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
        else { _uid = uid; }

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
