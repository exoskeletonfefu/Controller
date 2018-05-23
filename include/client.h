#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <string>
#include <memory>

class Client: public QObject {
    Q_OBJECT
public:
    Client(qintptr descriptor, QObject *parent = 0);
    void init();
//    void run();
    qint64 write(std::string data);
private:
    QTcpSocket *socket;
    quint16 blockSize;
    QByteArray currentBlock;
    int descriptor;
signals:
    void signDeleted(int);
    void signReaded(QString);
public slots:
//    void slotWrite(std::string data);
    void slotConnected();
    void slotDisconnected();
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
};
typedef std::shared_ptr<Client> PClient;
