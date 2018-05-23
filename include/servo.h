#include <QObject>

#include "messagecontroller.h"
#include "controltable.h"

#include "dynamixel_sdk.h"

class Servo {
public:
    Servo(MessageController *messageController, dynamixel::PortHandler *portHandler, dynamixel::PacketHandler *packetHandler);
    void write();
    void read();
    void readStatusMsg();
    uint8_t *checkId(uint8_t id) throw(std::string);
    uint8_t *readTxRx(uint8_t addr, uint16_t length) throw(std::string);
    uint8_t *readTxRxCatch(uint8_t addr, uint16_t length);
    int writeTxRx(uint8_t addr, uint16_t length, uint8_t *data) throw(std::string);
    int writeTxRxCatch(uint8_t addr, uint16_t length, uint8_t *data);
    int writeTxOnly(uint8_t addr, uint16_t length, uint8_t* data);
    void init();
    void setId(int id);
private:
    int id;
    MessageController *messageController;
//    Message::Id *inId;
    Message::Status *outStatus;
    Message::TorqueEnable *inTorqueEnable;
    Message::GoalPosition *inGoalPosition;
    Message::MarginSlope *inMarginSlope;
    Message::MovingSpeed *inMovingSpeed;
    Message::AngleLImit *inAngleLimit;

    dynamixel::PortHandler *portHandler;
    dynamixel::PacketHandler *packetHandler;
};
