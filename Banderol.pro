CONFIG += use_quick

greaterThan(QT_MAJOR_VERSION, 4) {
    DEFINES += AM_USING_QT5

    use_widgets {
        DEFINES += AM_USING_WIDGETS
        QT += widgets

        FORMS += Widget.ui
        HEADERS += Widget.h
        SOURCES += Widget.cpp
        }

    use_quick {
        DEFINES += AM_USING_QUICK
        QT += quick

        RESOURCES += quick.qrc
        }
    }

else {
    DEFINES += AM_USING_QT4 AM_USING_WIDGETS

    FORMS += Widget.ui
    HEADERS += Widget.h
    SOURCES += Widget.cpp
    }

TEMPLATE		= app
CONFIG			+= qt warn_off release precompile_header
CONFIG			-=
QT			+= network

PRECOMPILED_HEADER	= stable.h

HEADERS			+= stable.h \
                           Network.h

SOURCES			+= Main.cpp \
                           Network.cpp

RESOURCES		+= main.qrc
win32:RC_FILE		+= metainfo.rc
macx:ICON		+= icon.icns

TARGET			= Banderol
OBJECTS_DIR		= .temp
MOC_DIR			= .temp
UI_DIR			= .temp
UI_HEADERS_DIR		= .temp
UI_SOURCES_DIR		= .temp
