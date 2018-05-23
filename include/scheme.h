#pragma once
#include "message.h"

namespace Message {

#define NUMB(value) value, sizeof(value), (&value)

namespace baud_rate {
enum Type {
    B1000000 = 1,
    B500000  = 3,
    B400000  = 4,
    B250000  = 7,
    B200000  = 9,
    B115200  = 16,
    B57600   = 34,
    B19200   = 103,
    B9600    = 207
};
}

namespace status_return_level {
enum Type {
    ReturnNo   = 0,
    ReturnRead = 1,
    ReturnAll  = 2
};
}

namespace torque_enable {
enum Type {
    Off = 0,
    On  = 1
};
}

namespace led {
enum Type {
    Off = 0,
    On  = 1
};
}

namespace registered_instruction {
enum Type {
    No = 0,
    Yes  = 1
};
}

namespace moving {
enum Type {
    Completed = 0,
    InProgress  = 1
};
}

namespace lock {
enum Type {
    No  = 0,
    Yes = 1
};
}

namespace move_command {
enum Type {
    First  = 0,
    Second = 1,
    Third  = 2
};
}

#define BAUD_RATE_LIST \
    .add(baud_rate::B1000000, "1000000") \
    .add(baud_rate::B500000,  "500000") \
    .add(baud_rate::B400000,  "400000") \
    .add(baud_rate::B250000,  "250000") \
    .add(baud_rate::B200000,  "200000") \
    .add(baud_rate::B115200,  "115200") \
    .add(baud_rate::B57600,   "57600") \
    .add(baud_rate::B19200,   "19200") \
    .add(baud_rate::B9600,    "9600")

#define STATUS_RETURN_LEVEL \
    .add(status_return_level::ReturnNo,   "return no") \
    .add(status_return_level::ReturnRead, "return read") \
    .add(status_return_level::ReturnAll,  "return all") \

#define TORQUE_ENABLE_LIST \
    .add(torque_enable::Off, "off") \
    .add(torque_enable::On,  "on")

#define LED_LIST \
    .add(led::Off, "off") \
    .add(led::On,  "on")

#define REGISTERED_LIST \
    .add(registered_instruction::No,  "no") \
    .add(registered_instruction::Yes, "yes")

#define MOVING_LIST \
    .add(moving::Completed,  "completed") \
    .add(moving::InProgress, "in progress")

#define LOCK_LIST \
    .add(lock::No,  "no") \
    .add(lock::Yes, "yes")

#define MOVE_COMMAND_LIST \
    .add(move_command::First,  "first") \
    .add(move_command::Second, "second") \
    .add(move_command::Third,  "third")

class Scheme {
public:
    template<class T>
    void setFieldValue(int name, T value) {
        auto &field = fields.at(name);
        for (int i = field.second - 1; i >= 0; i--) {
            *((char*)field.first + i) = (value >> (8 * i)) & 0xff;
        }
    }
    virtual Message message(Command::Type command) = 0;
protected:
    std::map<int, std::pair<void*, int>> fields;
};

class Id : public Scheme {
public:
    uint8_t id;

    Message message(Command::Type command) {
        return Message(command, &fields).setTitle("id")
                .add(Number(NUMB(id)).setTitle("id"));
    }
};

class Specification : public Scheme {
public:
    uint16_t modelNumber;
    uint8_t versionOfFirmware;

    Message message(Command::Type command) {
        return Message(command, &fields).setTitle("specification")
                .add(Number(NUMB(modelNumber)).setTitle("model number"))
                .add(Number(NUMB(versionOfFirmware)).setTitle("firmware"));
    }
};

class TorqueEnable : public Scheme {
public:
    uint8_t torqueEnable = 0;

    Message message(Command::Type command) {
        return Message(command, &fields).setTitle("torque enable")
                .add(Enum(NUMB(torqueEnable)).setTitle("torque enable") TORQUE_ENABLE_LIST);
    }
};

class GoalPosition : public Scheme {
public:
    uint16_t goalPosition = 0;

    Message message(Command::Type command) {
        return Message(command, &fields).setTitle("goal position")
                .add(Number(NUMB(goalPosition)).setTitle("goal position").setMin(0).setMax(2047));
    }
};

class Move : public Scheme {
public:
    move_command::Type moveCommand;

    Message message(Command::Type command) {
        return Message(command, &fields).setTitle("move")
                .add(Enum(NUMB(moveCommand)).setTitle("move command") MOVE_COMMAND_LIST);
    }
};

class MarginSlope : public Scheme {
public:
    uint8_t cwComplianceMargin;
    uint8_t ccwComplianceMargin;
    uint8_t acceleratingSpeed;
    uint8_t deceleratingSpeed;

    Message message(Command::Type command) {
        return Message(command, &fields).setTitle("margin accelerating")
                .add(Number(NUMB(cwComplianceMargin)).setTitle("cw margin").setMin(0).setMax(255))
                .add(Number(NUMB(ccwComplianceMargin)).setTitle("ccw margin").setMin(0).setMax(255))
                .add(Number(NUMB(acceleratingSpeed)).setTitle("accelerating speed").setMin(0).setMax(255))
                .add(Number(NUMB(deceleratingSpeed)).setTitle("decelerating speed").setMin(0).setMax(255));
    }
};

class MovingSpeed : public Scheme {
public:
    uint16_t movingSpeed;

    Message message(Command::Type command) {
        return Message(command, &fields).setTitle("moving speed")
                .add(Number(NUMB(movingSpeed)).setTitle("moving speed").setMin(0).setMax(1023));
    }
};

class AngleLImit : public Scheme {
public:
    uint16_t cwAngleLimit;
    uint16_t ccwAngleLimit;

    Message message(Command::Type command) {
        return Message(command, &fields).setTitle("angle limit")
                .add(Number(NUMB(cwAngleLimit)).setTitle("cw angle limit"))
                .add(Number(NUMB(ccwAngleLimit)).setTitle("ccw angle limit"));
    }
};

class Status : public Scheme {
public:
    uint8_t versionOfFirmware;
    uint8_t id;
    uint8_t baudRate;
    uint8_t returnDelayTime;
    uint16_t cwAngleLimit;
    uint16_t ccwAngleLimit;
    uint8_t highestLimitTemperature;
    uint8_t lowestLimitVoltage;
    uint8_t highestLimitVoltage;
    uint16_t maxTorque;
    uint8_t statusReturnLevel;
    uint8_t alarmLed;
    uint8_t unloadCondition;
    uint8_t torqueEnable;
    uint8_t led;
    uint8_t cwComplianceMargin;
    uint8_t ccwComplianceMargin;
    uint8_t cwRatio;
    uint8_t ccwRatio;
    uint16_t goalPosition;
    uint16_t movingSpeed;
    uint8_t acceleratingSpeed;
    uint8_t deceleratingSpeed;
    uint16_t presentPosition;
    uint16_t presentSpeed;
    uint16_t presentLoad;
    uint8_t presentVoltage;
    uint8_t presentTempure;
    uint8_t regWriteMark;
    uint8_t inOperation;
    uint8_t lock;
    uint16_t minimumPwm;

    Message message(Command::Type command) {
        return Message(command, &fields).setTitle("status")
//                .add(Number(NUMB(versionOfFirmware)).setTitle("firmawer"))
                .add(Number(NUMB(id)).setTitle("id").setMin(0).setMax(254))
                .add(Enum(NUMB(baudRate)).setTitle("baud rate") BAUD_RATE_LIST)
                .add(Number(NUMB(returnDelayTime)).setTitle("delay time").setMin(0).setMax(254))
                .add(Number(NUMB(cwAngleLimit)).setTitle("cw angle limit"))
                .add(Number(NUMB(ccwAngleLimit)).setTitle("ccw angle limit"))
//                .add(Number(NUMB(highestLimitTemperature)).setTitle("max temperature"))
//                .add(Number(NUMB(lowestLimitVoltage)).setTitle("min voltage").setMin(50).setMax(250))
//                .add(Number(NUMB(highestLimitVoltage)).setTitle("max voltage").setMin(50).setMax(250))
                .add(Number(NUMB(maxTorque)).setTitle("max torque").setMin(0).setMax(1023))
//                .add(Enum(NUMB(statusReturnLevel)).setTitle("return level") STATUS_RETURN_LEVEL)
//                .add(Number(NUMB(alarmLed)).setTitle("alarm led"))
                .add(Number(NUMB(unloadCondition)).setTitle("unload condition"))
                .add(Enum(NUMB(torqueEnable)).setTitle("torque enable") TORQUE_ENABLE_LIST)
//                .add(Enum(NUMB(led)).setTitle("led") LED_LIST)
                .add(Number(NUMB(cwComplianceMargin)).setTitle("cw margin").setMin(0).setMax(255))
                .add(Number(NUMB(ccwComplianceMargin)).setTitle("ccw margin").setMin(0).setMax(255))
                .add(Number(NUMB(cwRatio)).setTitle("cw slope").setMin(0).setMax(255))
                .add(Number(NUMB(ccwRatio)).setTitle("ccw slope").setMin(0).setMax(255))
                .add(Number(NUMB(goalPosition)).setTitle("goal position").setMin(0).setMax(1023))
                .add(Number(NUMB(movingSpeed)).setTitle("moving speed").setMin(0).setMax(2047))
                .add(Number(NUMB(acceleratingSpeed)).setTitle("accelerating speed").setMin(0).setMax(255))
                .add(Number(NUMB(deceleratingSpeed)).setTitle("decelerating speed").setMin(0).setMax(255))
                .add(Number(NUMB(presentPosition)).setTitle("present position").setMin(0).setMax(1023))
                .add(Number(NUMB(presentSpeed)).setTitle("present speed").setMin(0).setMax(2047))
                .add(Number(NUMB(presentLoad)).setTitle("present load").setMin(0).setMax(2047))
                .add(Number(NUMB(presentVoltage)).setTitle("present voltage"))
                .add(Number(NUMB(presentTempure)).setTitle("present temperature"))
//                .add(Enum(NUMB(regWriteMark)).setTitle("reg write mark") REGISTERED_LIST)
//                .add(Enum(NUMB(inOperation)).setTitle("in operation") MOVING_LIST)
//                .add(Enum(NUMB(lock)).setTitle("lock") LOCK_LIST)
                .add(Number(NUMB(minimumPwm)).setTitle("minimum pwm").setMin(32).setMax(1023));
    }
};
}
