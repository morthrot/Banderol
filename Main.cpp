#include "stable.h"

#include "Network.h"

#ifdef AM_USING_WIDGETS
#include "Widget.h"
#endif

int main(int argc, char *argv[]) {
#if defined(AM_USING_QT4)
    QApplication app(argc,argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#elif defined(AM_USING_QT5)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    
#if defined(AM_USING_WIDGETS)    
    QApplication app(argc,argv);
#elif defined(AM_USING_QUICK)
    QGuiApplication app(argc,argv);
#endif

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

#if defined(AM_USING_WIDGETS)
    if(bind_ok == false) {
        QMessageBox::critical(NULL,"Ошибка сети",QString("Ошибка привязки к порту %1").arg(port),"OK");
        return EXIT_FAILURE;
        }

    nick = QInputDialog::getText(NULL,"Вход","Введите погоняло:",QLineEdit::Normal,nick,NULL,Qt::Popup);
    if(nick.isEmpty() == true) { return EXIT_FAILURE; }
    
    Widget widget(nick);
    QObject::connect(&network,SIGNAL(recievedMessage(QString,QString)),&widget,SLOT(recieveMessage(QString,QString)));
    QObject::connect(&widget,SIGNAL(generatedMessage(QString,QString)),&network,SLOT(sendMessage(QString,QString)));
    
    widget.show();
#elif defined(AM_USING_QUICK)
    QQuickView view;
    view.setSource(QUrl("qrc:/view.ui.qml"));

    view.show();
#endif

    int return_code = app.exec();
    
    settings.setValue("Service",service);
    settings.setValue("Target",target);
    settings.setValue("Port",port);
    settings.setValue("Nick",nick);
    
    return return_code;
    }
