QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Client/AppClient.cpp \
    Client/helpers/SocketClient.cpp \
    Deserializer/SocketDeserializer.cpp \
    Message/AuthorizedMessage.cpp \
    Message/FileMessage.cpp \
    Message/MessagePack.cpp \
    Message/RequestMessage.cpp \
    Message/TextMessage.cpp \
    Observer/ConnResetEvent.cpp \
    Observer/IObservable.cpp \
    Observer/MessagesUpdateEvent.cpp \
    Serializer/SocketSerializer.cpp \
    Viewer/main.cpp \
    Viewer/mainwindow.cpp \
    helpers/File.cpp \
    helpers/Socket/Socket.cpp \
    helpers/Socket/SocketException.cpp

HEADERS += \
    Client/AppClient.h \
    Client/IClonable.h \
    Client/helpers/SocketClient.h \
    Deserializer/Deserializer.h \
    Deserializer/DeserializerOperators.h \
    Deserializer/SocketDeserializer.h \
    Message/AuthorizedMessage.h \
    Message/FileMessage.h \
    Message/IMessage.h \
    Message/IMessagePack.h \
    Message/MessagePack.h \
    Message/RequestMessage.h \
    Message/TextMessage.h \
    Observer/ConnResetEvent.h \
    Observer/Event.h \
    Observer/IObservable.h \
    Observer/IObserver.h \
    Observer/MessagesUpdateEvent.h \
    ResponseBuilder/IConvertableToHttp.h \
    Serializer/Serializer.h \
    Serializer/SerializerOperators.h \
    Serializer/SocketSerializer.h \
    Viewer/mainwindow.h \
    helpers/File.h \
    helpers/Socket/ConnResetException.h \
    helpers/Socket/Socket.h \
    helpers/Socket/SocketException.h \
    helpers/UtilFile.h \
    helpers/UtilString.h

FORMS += \
    Viewer/mainwindow.ui

LIBS += Ws2_32.lib
#LIBS += -lws2_32

INCLUDEPATH += Client Deserializer helpers Message Observer ResponseBuilder Serializer


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
