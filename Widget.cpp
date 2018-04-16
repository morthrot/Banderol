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

#include "Widget.h"

Widget::Widget(QString nick,QWidget * parent) : QWidget(parent) {
    ui.setupUi(this);
    ui.lNick->setText(nick);
    
    connect(ui.leMessage,SIGNAL(textChanged(QString)),this,SLOT(processInterface()));
    connect(ui.leMessage,SIGNAL(returnPressed()),this,SLOT(sendMessage()));
    connect(ui.pbSend,SIGNAL(clicked()),this,SLOT(sendMessage()));
    
    _tray = new QSystemTrayIcon(this);
    _tray->setIcon(QIcon(":/icon.png"));
    _tray->show();
    
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(keepAlive()));
    timer->start(1000);
    
    processInterface();
    keepAlive();
    }

Widget::~Widget(void) {
    }

void Widget::keepAlive(void) {
    ui.lTime->setText( QTime::currentTime().toString("HH:mm:ss") );
    }

void Widget::processInterface(void) {
    ui.pbSend->setEnabled( ui.leMessage->text().isEmpty() == false );
    }

void Widget::sendMessage(void) {
    QString nick = ui.lNick->text();
    QString message = ui.leMessage->text();
    
    if(nick.isEmpty() == true || message.isEmpty() == true) { return; }
    
    emit generatedMessage(nick,message);
    
    ui.leMessage->clear();
    }

void Widget::recieveMessage(const QString & nick,const QString & message) {
    if(nick.isEmpty() == true) { return; }
    if(message.isEmpty() == true) { return; }
    
    QString dt = QTime::currentTime().toString("HH:mm:ss");
    
    ui.tbChat->append( QString("<i>%1</i> - <b>%2</b> %3").arg(dt,nick,message) );    
    if(isMinimized() == true) { _tray->showMessage(QString("%1 %2").arg(dt,nick),message); }
    }
