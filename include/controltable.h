#pragma once

//Control table
//namespace rx24 {
//enum Type {
//    ADDR_MODEL_NUMBER_L                = 0,        // Lowest byte of model number
//    ADDR_MODEL_NUMBER_H                = 1,        // Highest byte of model number
//    ADDR_VERSION_OF_FIRMWARE           = 2,        // Information on the version of firmware
//    ADDR_ID                            = 3,        // ID of Dynamixel
//    ADDR_BAUD_RATE                     = 4,        // Baud Rate of Dynamixel
//    ADDR_RETURN_DELAY_TIME             = 5,        // Return Delay Time
//    ADDR_CW_ANGLE_LIMIT_L              = 6,        // Lowest byte of clockwise Angle Limit
//    ADDR_CW_ANGLE_LIMIT_H              = 7,        // Highest byte of clockwise Angle Limit
//    ADDR_CCW_ANGLE_LIMIT_L             = 8,        // Lowest byte of counterclockwise Angle Limit
//    ADDR_CCW_ANGLE_LIMIT_H             = 9,        // Highest byte of counterclockwise Angle Limit
//    ADDR_THE_HIGHEST_LIMIT_TEMPERATURE = 11,       // Internal Limit Temperature
//    ADDR_THE_LOWEST_LIMIT_VOLTAGE      = 12,       // Lowest Limit Voltage
//    ADDR_THE_HIGHEST_LIMIT_VOLTAGE     = 13,       // Highest Limit Voltage
//    ADDR_MAX_TORQUE_L                  = 14,       // Lowest byte of Max. Torque
//    ADDR_MAX_TORQUE_H                  = 15,       // Highest byte of Max. Torque
//    ADDR_STATUS_RETURN_LEVEL           = 16,       // Status Return Level
//    ADDR_ALARM_LED                     = 17,       // LED for Alarm
//    ADDR_ALARM_SHUTDOWN                = 18,       // Shutdown for Alarm
//    ADDR_TORQUE_ENABLE                 = 24,       // Torque On/Off
//    ADDR_LED                           = 25,       // LED On/Off
//    ADDR_CW_COMPLIANCE_MARGIN          = 26,       // CW Compliance margin
//    ADDR_CCW_COMPLIANCE_MARGIN         = 27,       // CCW Compliance margin
//    ADDR_CW_COMPLIANCE_SLOPE           = 28,       // CW Compliance slope
//    ADDR_CCW_COMPLIANCE_SLOPE          = 29,       // CCW Compliance slope
//    ADDR_GOAL_POSITION_L               = 30,       // Lowest byte of Goal Position
//    ADDR_GOAL_POSITION_H               = 31,       // Highest byte of Goal Position
//    ADDR_MOVING_SPEED_L                = 32,       // Lowest byte of Moving Speed (Moving Velocity)
//    ADDR_MOVING_SPEED_H                = 33,       // Highest byte of Moving Speed (Moving Velocity)
//    ADDR_TORQUE_LIMIT_L                = 34,       // Lowest byte of Torque Limit (Goal Torque)
//    ADDR_TORQUE_LIMIT_H                = 35,       // Highest byte of Torque Limit (Goal Torque)
//    ADDR_PRESENT_POSITION_L            = 36,       // Lowest byte of Current Position (Present Velocity)
//    ADDR_PRESENT_POSITION_H            = 37,       // Highest byte of Current Position (Present Velocity)
//    ADDR_PRESENT_SPEED_L               = 38,       // Lowest byte of Current Speed
//    ADDR_PRESENT_SPEED_H               = 39,       // Highest byte of Current Speed
//    ADDR_PRESENT_LOAD_L                = 40,       // Lowest byte of Current Load
//    ADDR_PRESENT_LOAD_H                = 41,       // Highest byte of Current Load
//    ADDR_PRESENT_VOLTAGE               = 42,       // Current Voltage
//    ADDR_PRESENT_TEMPERATURE           = 43,       // Current Temperature
//    ADDR_REGISTERED                    = 44,       // Means if Instruction is registered
//    ADDR_MOVING                        = 46,       // Means if there is any movement
//    ADDR_LOCK                          = 47,       // Locking EEPROM
//    ADDR_PUNCH_L                       = 48,       // Lowest byte of Punch
//    ADDR_PUNCH_H                       = 49        // Highest byte of Punch
//};
//}

namespace sr518 {
enum Type {
    ADDR_VERSION_OF_FIRMWARE           = 2,        // Information on the version of firmware
    ADDR_ID                            = 3,        // ID of Dynamixel
    ADDR_BAUD_RATE                     = 4,        // Baud Rate of Dynamixel
    ADDR_RETURN_DELAY_TIME             = 5,        // Return Delay Time
    ADDR_CW_ANGLE_LIMIT_L              = 6,        // Lowest byte of clockwise Angle Limit
    ADDR_CW_ANGLE_LIMIT_H              = 7,        // Highest byte of clockwise Angle Limit
    ADDR_CCW_ANGLE_LIMIT_L             = 8,        // Lowest byte of counterclockwise Angle Limit
    ADDR_CCW_ANGLE_LIMIT_H             = 9,        // Highest byte of counterclockwise Angle Limit
    ADDR_THE_HIGHEST_LIMIT_TEMPERATURE = 11,       // Internal Limit Temperature
    ADDR_THE_LOWEST_LIMIT_VOLTAGE      = 12,       // Lowest Limit Voltage
    ADDR_THE_HIGHEST_LIMIT_VOLTAGE     = 13,       // Highest Limit Voltage
    ADDR_MAX_TORQUE_L                  = 14,       // Lowest byte of Max. Torque
    ADDR_MAX_TORQUE_H                  = 15,       // Highest byte of Max. Torque
    ADDR_STATUS_RETURN_LEVEL           = 16,       // Status Return Level
    ADDR_ALARM_LED                     = 17,       // LED for Alarm
    ADDR_UNLOAD_CONDITION              = 18,       // Shutdown for Alarm
    ADDR_TORQUE_ENABLE                 = 24,       // Torque On/Off
    ADDR_LED                           = 25,       // LED On/Off
    ADDR_CW_COMPLIANCE_MARGIN          = 26,       // CW Compliance margin
    ADDR_CCW_COMPLIANCE_MARGIN         = 27,       // CCW Compliance margin
    ADDR_CW_RATIO                      = 28,
    ADDR_CCW_RATIO                     = 29,
    ADDR_GOAL_POSITION_L               = 30,       // Lowest byte of Goal Position
    ADDR_GOAL_POSITION_H               = 31,       // Highest byte of Goal Position
    ADDR_MOVING_SPEED_L                = 32,       // Lowest byte of Moving Speed (Moving Velocity)
    ADDR_MOVING_SPEED_H                = 33,       // Highest byte of Moving Speed (Moving Velocity)
    ADDR_ACCELERATING_SPEED            = 34,
    ADDR_DECELERATING_SPEED            = 35,
    ADDR_PRESENT_POSITION_L            = 36,       // Lowest byte of Current Position (Present Velocity)
    ADDR_PRESENT_POSITION_H            = 37,       // Highest byte of Current Position (Present Velocity)
    ADDR_PRESENT_SPEED_L               = 38,       // Lowest byte of Current Speed
    ADDR_PRESENT_SPEED_H               = 39,       // Highest byte of Current Speed
    ADDR_PRESENT_LOAD_L                = 40,       // Lowest byte of Current Load
    ADDR_PRESENT_LOAD_H                = 41,       // Highest byte of Current Load
    ADDR_PRESENT_VOLTAGE               = 42,       // Current Voltage
    ADDR_PRESENT_TEMPERATURE           = 43,       // Current Temperature
    ADDR_REGWRITE_MARK                 = 44,       // Means if Instruction is registered
    ADDR_IN_OPERATION                  = 46,       // Means if there is any movement
    ADDR_LOCK                          = 47,       // Locking EEPROM
    ADDR_MINIMUM_PWM_L                 = 48,       // Lowest byte of Punch
    ADDR_MINIMUM_PWM_H                 = 49        // Highest byte of Punch
};
}
