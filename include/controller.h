#pragma once
#include <QObject>
#include <QThread>
//#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>
#include <QThreadPool>

#include "server.h"
#include "timer.h"
#include "message.h"

class Controller: public QObject {
    Q_OBJECT
public:
    Controller(QObject *parent = 0);
    Message::Id *outId;
    Message::Test *outTest;
private:
    void write();
    Server *server;
    PTimer timer;
public slots:
    void slotWriteStatus();
};
