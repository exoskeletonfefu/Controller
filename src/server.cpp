#include <unistd.h>
#include <iostream>

#include "server.h"

using namespace std;

Server::Server(int port, QObject *parent) :
    port(port),
    QTcpServer(parent) {}

void Server::start() {
    if(this->listen(QHostAddress::Any, port)) {
        qDebug() << "Server started";
    }
    else {
        qDebug() << "Server did not start!";
    }
}

void Server::incomingConnection(qintptr handle) {
    Client *client = new Client(handle);
    clients.emplace(handle, client);
    connect(client, SIGNAL(signDeleted(int)), this, SLOT(slotEraseClient(int)));
}

void Server::slotEraseClient(int descriptor) {
    clients.erase(descriptor);
}

void Server::write(std::string data) {
    for (auto &client: clients)
        client.second->write(data);
}
