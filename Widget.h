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

#ifndef _WIDGET_H
#define	_WIDGET_H

#include "stable.h"

#include "ui_Widget.h"

class Widget : public QWidget {
    Q_OBJECT
private:
    Ui::Widget ui;
    QSystemTrayIcon * _tray;
public:
    Widget(QString nick,QWidget * parent = 0);
    ~Widget(void);
public slots:    
    void keepAlive(void);
    void processInterface(void);

    void sendMessage(void);
    void recieveMessage(const QString & nick,const QString & message);
signals:
    void generatedMessage(QString,QString); // nick, message
    };

#endif /* _WIDGET_H */
