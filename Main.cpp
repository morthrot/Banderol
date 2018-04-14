#include <QtCore>
#include <QtNetwork>
#include <QtGui>

#ifdef AM_USING_QT5
#include <QtWidgets>
#endif

#include "Network.h"
#include "Widget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
#ifdef AM_USING_QT4
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
    app.setWindowIcon(QIcon(":/icon.png"));
   
    QCoreApplication::setApplicationName("Banderol");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCoreApplication::setOrganizationName("AD-Software");
    QCoreApplication::setOrganizationDomain("ad.org");
    
    srand(QDateTime::currentDateTime().toMSecsSinceEpoch());
    
    QSettings settings;
    QString service = settings.value("Service","Banderol").toString();
    QString target = settings.value("Target","255.255.255.255").toString();
    quint16 port = settings.value("Port",6888).toUInt();
    QString nick = settings.value("Nick",QString("Гость-%1").arg(rand()%65536)).toString();
    
    Network network(service,QHostAddress(target),port);
    
    bool bind_ok = network.bind();
    if(bind_ok == false) {
        QMessageBox::critical(NULL,"Ошибка сети",QString("Ошибка привязки к порту %1").arg(port),"OK");
        return EXIT_FAILURE;
        }
    
    nick = QInputDialog::getText(NULL,"Вход","Введите погоняло:",QLineEdit::Normal,nick);
    if(nick.isEmpty() == true) { return EXIT_FAILURE; }
    
    Widget widget(nick);
    QObject::connect(&network,SIGNAL(recievedMessage(QString,QString)),&widget,SLOT(recieveMessage(QString,QString)));
    QObject::connect(&widget,SIGNAL(generatedMessage(QString,QString)),&network,SLOT(sendMessage(QString,QString)));
    
    widget.show();
    
    int return_code = app.exec();
    
    settings.setValue("Service",service);
    settings.setValue("Target",target);
    settings.setValue("Port",port);
    settings.setValue("Nick",nick);
    
    return return_code;
    }
