/*

Copyright (c) 2018 Д.С. Андреев

Этот файл — часть Banderol.

jam - свободная программа: вы можете перераспространять ее и/или
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

jam is free software: you can redistribute it and/or modify
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

#ifndef NETWORK_H
#define	NETWORK_H

#include "stable.h"

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

