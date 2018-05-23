#include "iostream"

#include "servo.h"

Servo::Servo(MessageController *messageController, dynamixel::PortHandler *portHandler, dynamixel::PacketHandler *packetHandler) :
    messageController(messageController),
    portHandler(portHandler),
    packetHandler(packetHandler) {}

void Servo::init() {
    outStatus = new Message::Status;
//    inId = new Message::Id;
    inTorqueEnable = new Message::TorqueEnable;
    inGoalPosition = new Message::GoalPosition;
    inMarginSlope  = new Message::MarginSlope;
    inMovingSpeed  = new Message::MovingSpeed;
    inAngleLimit   = new Message::AngleLImit;

    this->messageController->addScheme(outStatus, Message::Command::STATE);
//    this->messageController->addScheme(inId, Message::Command::CONTROL);
    this->messageController->addScheme(inTorqueEnable, Message::Command::CONTROL);
    this->messageController->addScheme(inGoalPosition, Message::Command::CONTROL);
    this->messageController->addScheme(inMarginSlope, Message::Command::CONTROL);
    this->messageController->addScheme(inMovingSpeed, Message::Command::CONTROL);
    this->messageController->addScheme(inAngleLimit, Message::Command::CONTROL);
}

void Servo::setId(int id) {
    this->id = id;
}

uint8_t *Servo::checkId(uint8_t id) throw(std::string) {
    this->id = id;
    return readTxRx(sr518::ADDR_ID, 1);
}

uint8_t *Servo::readTxRx(uint8_t addr, uint16_t length) throw(std::string) {
    uint8_t dxl_error = 0;
    uint8_t *dxl_data = new uint8_t[length];
    int dxl_comm_result = COMM_TX_FAIL;
    dxl_comm_result = packetHandler->readTxRx(portHandler, id, addr, length, dxl_data, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
        throw(std::string(packetHandler->getTxRxResult(dxl_comm_result)));
    else if (dxl_error != 0)
        throw(std::string(packetHandler->getRxPacketError(dxl_error)));
    return dxl_data;
}

uint8_t *Servo::readTxRxCatch(uint8_t addr, uint16_t length) {
    try {
        return readTxRx(addr, length);
    }
    catch(std::string e) {
        std::cout << "Read. " << e << std::endl;
        return 0;
    }
}

int Servo::writeTxRx(uint8_t addr, uint16_t length, uint8_t *data) throw(std::string) {
    int dxl_comm_result = COMM_TX_FAIL;
    uint8_t dxl_error = 0;
    dxl_comm_result = packetHandler->writeTxRx(portHandler, id, addr, length, data, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
        throw(std::string(packetHandler->getTxRxResult(dxl_comm_result)));
    else if (dxl_error != 0)
        throw(std::string(packetHandler->getRxPacketError(dxl_error)));
    return dxl_comm_result;
}

int Servo::writeTxRxCatch(uint8_t addr, uint16_t length, uint8_t *data) {
    try {
        return writeTxRx(addr, length, data);
    }
    catch(std::string e) {
        std::cout << "Write. " << e << std::endl;
        return 0;
    }
}

int Servo::writeTxOnly(uint8_t addr, uint16_t length, uint8_t* data) {
    return packetHandler->writeTxOnly(portHandler, id, addr, length, data);
}

void Servo::write() {
    if (messageController->isUpdated(inTorqueEnable)) {
        writeTxRxCatch(sr518::ADDR_TORQUE_ENABLE, 1, &inTorqueEnable->torqueEnable);
    }
    if (messageController->isUpdated(inGoalPosition)) {
        writeTxRxCatch(sr518::ADDR_GOAL_POSITION_L, 2, (uint8_t*)&inGoalPosition->goalPosition);
    }
    if (messageController->isUpdated(inMarginSlope)) {
        writeTxRxCatch(sr518::ADDR_CW_COMPLIANCE_MARGIN, 1, &inMarginSlope->cwComplianceMargin);
        writeTxRxCatch(sr518::ADDR_CCW_COMPLIANCE_MARGIN, 1, &inMarginSlope->ccwComplianceMargin);
        writeTxRxCatch(sr518::ADDR_ACCELERATING_SPEED, 1, &inMarginSlope->acceleratingSpeed);
        writeTxRxCatch(sr518::ADDR_DECELERATING_SPEED, 1, &inMarginSlope->deceleratingSpeed);
    }
    if (messageController->isUpdated(inMovingSpeed)) {
        writeTxRxCatch(sr518::ADDR_MOVING_SPEED_L, 2, (uint8_t*)&inMovingSpeed->movingSpeed);
    }
    if (messageController->isUpdated(inAngleLimit)) {
        writeTxRxCatch(sr518::ADDR_CW_ANGLE_LIMIT_L, 2, (uint8_t*)&inAngleLimit->cwAngleLimit);
        writeTxRxCatch(sr518::ADDR_CCW_ANGLE_LIMIT_L, 2, (uint8_t*)&inAngleLimit->ccwAngleLimit);
    }
//    if (messageController->isUpdated(inId)) {
//        writeTxOnly(id, rx24::ADDR_ID, 1, &inId->id);
//        id = inId->id;
//    }
}

void Servo::read() {
    readStatusMsg();
}

void Servo::readStatusMsg() {
    uint8_t *data;
    try {
        data = readTxRx(0, 50);
    }
    catch(std::string e) {
        std::cout << "Read. " << e << std::endl;
        return;
    }

    outStatus->versionOfFirmware       = *((uint8_t*)(data + sr518::ADDR_VERSION_OF_FIRMWARE));
    outStatus->id                      = *((uint8_t*)(data + sr518::ADDR_ID));
    outStatus->baudRate                = *((uint8_t*)(data + sr518::ADDR_BAUD_RATE));
    outStatus->returnDelayTime         = *((uint8_t*)(data + sr518::ADDR_RETURN_DELAY_TIME));
    outStatus->highestLimitTemperature = *((uint8_t*)(data + sr518::ADDR_THE_HIGHEST_LIMIT_TEMPERATURE));
    outStatus->lowestLimitVoltage      = *((uint8_t*)(data + sr518::ADDR_THE_LOWEST_LIMIT_VOLTAGE));
    outStatus->highestLimitVoltage     = *((uint8_t*)(data + sr518::ADDR_THE_HIGHEST_LIMIT_VOLTAGE));
    outStatus->statusReturnLevel       = *((uint8_t*)(data + sr518::ADDR_STATUS_RETURN_LEVEL));
    outStatus->alarmLed                = *((uint8_t*)(data + sr518::ADDR_ALARM_LED));
    outStatus->unloadCondition         = *((uint8_t*)(data + sr518::ADDR_UNLOAD_CONDITION));
    outStatus->torqueEnable            = *((uint8_t*)(data + sr518::ADDR_TORQUE_ENABLE));
    outStatus->led                     = *((uint8_t*)(data + sr518::ADDR_LED));
    outStatus->cwComplianceMargin      = *((uint8_t*)(data + sr518::ADDR_CW_COMPLIANCE_MARGIN));
    outStatus->ccwComplianceMargin     = *((uint8_t*)(data + sr518::ADDR_CCW_COMPLIANCE_MARGIN));
    outStatus->cwRatio                 = *((uint8_t*)(data + sr518::ADDR_CW_RATIO));
    outStatus->ccwRatio                = *((uint8_t*)(data + sr518::ADDR_CCW_RATIO));
    outStatus->presentVoltage          = *((uint8_t*)(data + sr518::ADDR_PRESENT_VOLTAGE));
    outStatus->presentTempure          = *((uint8_t*)(data + sr518::ADDR_PRESENT_TEMPERATURE));
    outStatus->regWriteMark            = *((uint8_t*)(data + sr518::ADDR_REGWRITE_MARK));
    outStatus->inOperation             = *((uint8_t*)(data + sr518::ADDR_IN_OPERATION));
    outStatus->lock                    = *((uint8_t*)(data + sr518::ADDR_LOCK));
    outStatus->acceleratingSpeed       = *((uint8_t*)(data + sr518::ADDR_ACCELERATING_SPEED));
    outStatus->deceleratingSpeed       = *((uint8_t*)(data + sr518::ADDR_DECELERATING_SPEED));
    outStatus->minimumPwm              = *((uint16_t*)(data + sr518::ADDR_MINIMUM_PWM_L));
    outStatus->maxTorque               = *((uint16_t*)(data + sr518::ADDR_MAX_TORQUE_L));
    outStatus->cwAngleLimit            = *((uint16_t*)(data + sr518::ADDR_CW_ANGLE_LIMIT_L));
    outStatus->ccwAngleLimit           = *((uint16_t*)(data + sr518::ADDR_CCW_ANGLE_LIMIT_L));
    outStatus->goalPosition            = *((uint16_t*)(data + sr518::ADDR_GOAL_POSITION_L));
    outStatus->movingSpeed             = *((uint16_t*)(data + sr518::ADDR_MOVING_SPEED_L));
    outStatus->presentPosition         = *((uint16_t*)(data + sr518::ADDR_PRESENT_POSITION_L));
    outStatus->presentSpeed            = *((uint16_t*)(data + sr518::ADDR_PRESENT_SPEED_L));
    outStatus->presentLoad             = *((uint16_t*)(data + sr518::ADDR_PRESENT_LOAD_L));
}
