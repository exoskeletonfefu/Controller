#include <QObject>
#include <QCoreApplication>
#include <iostream>
#include <vector>

#include "controller.h"

#include <rapidjson/filereadstream.h>
#define BAUDRATE                        57600
using namespace rapidjson;

Controller::Controller(QObject *parent) :
    QObject(parent) {

    server = new Server(port);
    timer = PTimer(new Timer());

    connect(timer.get(), SIGNAL(finished()), timer.get(), SLOT(deleteLater()));
    connect(timer.get(), SIGNAL(signTimed()), this, SLOT(slotWriteStatus()));
    messageController = new MessageController(server);
    inMove = new Message::Move;
    messageController->addScheme(inMove, Message::Command::CONTROL);

    portHandler = dynamixel::PortHandler::getPortHandler(deviceName.data());
    packetHandler = dynamixel::PacketHandler::getPacketHandler(protocolVersion);

    if (portHandler->openPort())
        qDebug() << "Succeeded to open the port!\n";
    else
        qDebug() << "Failed to open the port!\n";

    if (portHandler->setBaudRate(BAUDRATE))
        qDebug() << "Succeeded to change the baudrate!\n";
    else
        qDebug() << "Failed to change the baudrate!\n";

//    qDebug() << servoId;
//    inId->id = servoId;

    server->start();
    timer->start();
}

void Controller::slotWriteStatus() {
    outId->id = 5;
    server->write(outId->message().getData());
    server->write(outTest->message().getData());
}
