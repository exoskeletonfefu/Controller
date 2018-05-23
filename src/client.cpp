#include "client.h"

using namespace std;

Client::Client(qintptr descriptor, QObject *parent) :
    QObject(parent) {
    this->descriptor = descriptor;
    blockSize = 0;
    init();
}

void Client::init() {
    socket = new QTcpSocket();
//    socket->setParent(this);
    qDebug() << "A new socket created!";

//    connect(socket, SIGNAL(connected()), this, SLOT(slotConnected()), Qt::DirectConnection);
//    connect(socket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()), Qt::DirectConnection);
//    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::DirectConnection);
//    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)), Qt::DirectConnection);

    connect(socket, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
//    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

    socket->setSocketDescriptor(descriptor);

//    emit signConnected(this);

    qDebug() << "Client connected at " << descriptor;

//    exec();
}

void Client::slotConnected() {
    qDebug() << "Client connected event";
}

void Client::slotDisconnected() {
    qDebug() << "Client. Disconnected";
//    socket->deleteLater();
//    exit(0);
    emit signDeleted(this->descriptor);
}

void Client::slotReadyRead() {
    qDebug() << "MyClient::readyRead()";

    QByteArray data = socket->readAll();
    int index = 0;
    while (true) {
        if (blockSize == 0) {
            if (data.size() - index < 2)
                return;
            currentBlock.clear();
            blockSize = quint16((unsigned char)(data[index]) << 8 | (unsigned char)(data[index + 1]));
            index += 2;
        }
        if (data.size() - index < blockSize) {
            currentBlock.append(data.mid(index, -1));
            blockSize -= data.size() - index;
            return;
        }
        currentBlock.append(data.mid(index, blockSize));
        index += blockSize;
        blockSize = 0;

        qDebug() << currentBlock;
        emit signReaded(currentBlock);
    }
}

void Client::slotError(QAbstractSocket::SocketError socketError) {
    switch (socketError) {
//        case QAbstractSocket::RemoteHostClosedError: {
//            log.append("Client. Error. Some");
//            qDebug() << "Error. Some";
//            break;
//        }
//        case QAbstractSocket::HostNotFoundError: {
//            log.append("Client. Error. The host was not found");
//            qDebug() << "Error. The host was not found";
//            break;
//        }
//        case QAbstractSocket::ConnectionRefusedError: {
//            log.append("Client. Error. The connection was refused by the peer.");
//            qDebug() << "Error. The connection was refused by the peer.";
//            break;
//        }
        default: {
            qDebug() << "Error. The following error occurred: " + socket->errorString();
        }
    }
}

qint64 Client::write(std::string data) {
    return socket->write(data.data(), data.size());
}
