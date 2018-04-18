/*

Copyright (c) 2018 Д.С. Андреев

Этот файл — часть Banderol.

Banderol - свободная программа: вы можете перераспространять ее и/или
изменять ее на условиях Стандартной общественной лицензии GNU в том виде,
в каком она была опубликована Фондом свободного программного обеспечения;
либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
версии.

Banderol распространяется в надежде, что она будет полезной,
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

Banderol is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Composer.  If not, see <http://www.gnu.org/licenses/>.

*/

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
    QQmlApplicationEngine engine;

    QQmlContext * context = engine.rootContext();
    if(context == NULL) { return EXIT_FAILURE; }

    context->setContextProperty("network",&network);

    engine.load(QUrl("qrc:/view.qml"));

    QObject * root = engine.rootObjects().first();
    if(root == NULL) { return EXIT_FAILURE; }

    QVariant init_result;
    QMetaObject::invokeMethod(root,"init",Q_RETURN_ARG(QVariant,init_result),Q_ARG(QVariant,bind_ok),Q_ARG(QVariant,nick));

    QObject::connect(&network,SIGNAL(recievedMessage(QVariant,QVariant)),root,SLOT(recieveMessage(QVariant,QVariant)));
    QObject::connect(root,SIGNAL(generatedMessage(QVariant,QVariant)),&network,SLOT(sendMessage(QVariant,QVariant)));
#endif

    int return_code = app.exec();

#if defined(AM_USING_QUICK)
    QVariant nick_result;
    QMetaObject::invokeMethod(root,"getNick",Q_RETURN_ARG(QVariant,nick_result));
    nick = nick_result.toString();
#endif
    
    settings.setValue("Service",service);
    settings.setValue("Target",target);
    settings.setValue("Port",port);
    settings.setValue("Nick",nick);
    
    return return_code;
    }
