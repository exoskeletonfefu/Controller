#pragma once
#include <QObject>
#include <QThread>
//#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>
#include <QThreadPool>
#include <map>
#include <string>

#include "client.h"
//#include "timer.h"
//#include "message.h"
//#include "messagecontroller.h"

class Server: public QTcpServer {
    Q_OBJECT
public:
    Server(int port, QObject *parent = 0);
    void start();
    void write(std::string data);
private:
    std::map<qintptr, Client*> clients;
    float port;
protected:
    void incomingConnection(qintptr handke) override;
signals:
public slots:
    void slotEraseClient(int);
};
