greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    DEFINES += AM_USING_QT5
    }
else {
    DEFINES += AM_USING_QT4
    }

TEMPLATE		= app
CONFIG			+= qt warn_off release
CONFIG			-=
QT			+= network

FORMS			= Widget.ui

HEADERS			= Network.h \
			  Widget.h

SOURCES			= Main.cpp \
			  Network.cpp \
			  Widget.cpp

RESOURCES		= main.qrc
win32:RC_FILE		+= metainfo.rc
macx:ICON		+= icon.icns

TARGET			= Banderol
OBJECTS_DIR		= .temp
MOC_DIR			= .temp
UI_DIR			= .temp
UI_HEADERS_DIR		= .temp
UI_SOURCES_DIR		= .temp
