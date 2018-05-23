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
#include "messagecontroller.h"
#include "controltable.h"
#include "servo.h"
#include "dynamixel_sdk.h"

class Controller: public QObject {
    Q_OBJECT
public:
    Controller(QObject *parent = 0);
//    Message::Id *outId;
//    Message::Id *inId;
private:
    Server *server;
    PTimer timer;
    MessageController *messageController;
    dynamixel::PortHandler *portHandler;
    dynamixel::PacketHandler *packetHandler;
    std::vector<Servo*> servos;

    Message::Move *inMove;

    std::string deviceName;
    float protocolVersion;
    int port;
public slots:
    void slotWriteStatus();
};
