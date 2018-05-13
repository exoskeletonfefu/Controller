#include <QObject>

#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent) {
    outId = new Message::Id;
    outTest = new Message::Test;

    server = new Server;
    server->startServer();

    timer = PTimer(new Timer());
    connect(timer.get(), SIGNAL(finished()), timer.get(), SLOT(deleteLater()));
    connect(timer.get(), SIGNAL(signTimed()), this, SLOT(slotWriteStatus()));
    timer->start();
}

void Controller::slotWriteStatus() {
    outId->id = 5;
    server->write(outId->message().getData());
    server->write(outTest->message().getData());
}
