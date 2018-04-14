#include "Widget.h"

Widget::Widget(QString nick,QWidget * parent) : QWidget(parent) {
    _uid = rand();
    
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
    
    QVariantMap map;
    map["uid"] = rand();
    map["nick"] = nick;
    map["message"] = message;
    
    emit generatedPacket(map);
    
    ui.leMessage->clear();
    }

void Widget::recievePacket(QVariantMap map) {
    if(map.contains("uid") == false) { return; }
    
    unsigned int uid = map.value("uid").toUInt();
    if(uid == _uid) { return; }
    
    QString nick = map.value("nick").toString();
    if(nick.isEmpty() == true) { return; }
    
    QString message = map.value("message").toString();
    if(message.isEmpty() == true) { return; }
    
    QString dt = QTime::currentTime().toString("HH:mm:ss");
    
    ui.tbChat->append( QString("<i>%1</i> - <b>%2</b> %3").arg(dt,nick,message) );    
    if(isMinimized() == true) { _tray->showMessage(QString("%1 %2").arg(dt,nick),message); }
    
    _uid = uid;
    }
