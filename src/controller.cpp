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
    parseConfig(CONFIG);

    server = new Server(port);
    timer = PTimer(new Timer());

    connect(timer.get(), SIGNAL(finished()), timer.get(), SLOT(deleteLater()));
    connect(timer.get(), SIGNAL(signTimed()), this, SLOT(slotWriteState()));
    connect(server, SIGNAL(signNewConnection(int)), this, SLOT(slotWriteInit(int)), Qt::DirectConnection);
    connect(server, SIGNAL(signReaded(QString)), this, SLOT(slotReaded(QString)), Qt::DirectConnection);

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
    pingServos();

    server->start();
    timer->start();
}

void Controller::pingServos() {
    for (uint8_t i = 0; i < 255; i++) {
        Servo *servo = new Servo(messageController, portHandler, packetHandler);
        try {
            int servoId;
            servoId = *(uint8_t*)servo->checkId(i);
            servo->init();
            servo->setId(servoId);
            servos.push_back(servo);
            qDebug() << servoId;
        }
        catch(std::string e) {
            delete servo;
            continue;
        }
    }
}

void Controller::parseConfig(std::string fileName) {
    FILE* input = fopen(fileName.c_str(), "rb");
    char buffer[65536];
    FileReadStream *is;
    try {
        is = new FileReadStream(input, buffer, sizeof(buffer));
    }
    catch(...) {
        std::cout << "Config file not exist" << std::endl;
        return;
    }

    Document document;
    document.ParseStream<0, UTF8<>, FileReadStream>(*is);
    document.GetObject();
    deviceName = document["devicename"].GetString();
    protocolVersion = document["protocolversion"].GetFloat();
    port = document["port"].GetInt();
}


void Controller::slotReaded(QString data) {
    messageController->updateControl(data);
    for (auto &servo: servos) {
        servo->write();
    }
    if (messageController->isUpdated(inMove)) {
        for (auto &servo: servos) {
//            int writeTxRxCatch(uint8_t id, rx24::Type addr, uint16_t length, uint8_t *data);
            switch (inMove->moveCommand) {
            case Message::move_command::First: {
                uint16_t value = 0;
                servo->writeTxRxCatch(sr518::ADDR_GOAL_POSITION_L, 2, (uint8_t*)&value);
                break;
            }
            case Message::move_command::Second: {
                uint16_t value = 500;
                servo->writeTxRxCatch(sr518::ADDR_GOAL_POSITION_L, 2, (uint8_t*)&value);
                break;
            }
            case Message::move_command::Third: {
                uint16_t value = 1000;
                servo->writeTxRxCatch(sr518::ADDR_GOAL_POSITION_L, 2, (uint8_t*)&value);
                break;
            }
            }
        }
    }
}

void Controller::slotWriteState() {
    for (auto &servo: servos) {
        servo->read();
    }
    messageController->writeStates();
}

void Controller::slotWriteInit(int descriptor) {
    messageController->writeInits(descriptor);
}

