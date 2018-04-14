#ifndef _WIDGET_H
#define	_WIDGET_H

#include <QtCore>
#include <QtGui>

#ifdef AM_USING_QT5
#include <QtWidgets>
#endif

#include "ui_Widget.h"

class Widget : public QWidget {
    Q_OBJECT
private:
    unsigned int _uid;
    Ui::Widget ui;
    QSystemTrayIcon * _tray;
public:
    Widget(QString nick,QWidget * parent = 0);
    ~Widget(void);
public slots:    
    void keepAlive(void);
    void processInterface(void);

    void sendMessage(void);
    void recievePacket(QVariantMap map);
signals:
    void generatedPacket(QVariantMap);
    };

#endif /* _WIDGET_H */
