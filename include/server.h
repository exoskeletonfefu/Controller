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
    void write(std::string data, qintptr descriptor);
private:
    std::map<qintptr, Client*> clients;
    float port;
protected:
    void incomingConnection(qintptr handke) override;
signals:
    void signNewConnection(int);
    void signReaded(QString);
public slots:
    void slotReaded(QString);
    void slotEraseClient(int);
};
