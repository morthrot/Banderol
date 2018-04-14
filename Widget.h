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
