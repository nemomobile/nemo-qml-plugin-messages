TARGET = nemomessages-internal
PLUGIN_IMPORT_PATH = org/nemomobile/messages/internal
TEMPLATE = lib
CONFIG += qt plugin hide_symbols

CONFIG += link_pkgconfig

equals(QT_MAJOR_VERSION, 4) {
    PKGCONFIG += TelepathyQt4
    QT += declarative
    target.path = $$[QT_INSTALL_IMPORTS]/$$PLUGIN_IMPORT_PATH
}
equals(QT_MAJOR_VERSION, 5) {
    PKGCONFIG += TelepathyQt5 
    QT += qml
    target.path = $$[QT_INSTALL_QML]/$$PLUGIN_IMPORT_PATH
} 

SOURCES += plugin.cpp \
    src/accountsmodel.cpp \
    src/conversationchannel.cpp \
    src/clienthandler.cpp \
    src/declarativeaccount.cpp

HEADERS += src/accountsmodel.h \
    src/conversationchannel.h \
    src/clienthandler.h \
    src/declarativeaccount.h

INSTALLS += target

qmldir.files += $$PWD/qmldir
qmldir.path +=  $$target.path
INSTALLS += qmldir
