#ifndef __MARTY_SOCKET_COMMANDS
#define __MARTY_SOCKET_COMMANDS

#include <stdlib.h>
#include <vector>
#include <stdint.h>

#define GET_PACKET 	0x01
#define CMD_PACKET 	0x02

#define SENSOR_BATTERY			0x01
#define SENSOR_ACCEL			0x02
#define SENSOR_MOTOR_CURRENT	0x03
#define SENSOR_GPIO				0x04
#define SENSOR_CHATTER			0x05
#define SENSOR_MOTOR_POSITION	0x06
#define SENSOR_MOTOR_ENABLED	0x07

#define SIDE_LEFT 		0x00
#define SIDE_RIGHT 		0x01
#define SIDE_FORWARD 	0x02
#define SIDE_BACKWARD	0x03
#define SIDE_ANY		0x04

#define OPCODE_HELLO				0x00
#define OPCODE_LEAN					0x02
#define OPCODE_WALK					0x03
#define OPCODE_KICK 				0x05
#define OPCODE_CELEBRATE			0x08
#define OPCODE_TAP_FOOT				0x0A
#define OPCODE_ARMS					0x0B
#define OPCODE_SIDESTEP				0x0E
#define OPCODE_STAND_STRAIGHT		0x0F
#define OPCODE_PLAY_SOUND			0x10
#define OPCODE_STOP					0x11
#define OPCODE_MOVE_JOINT			0x12
#define OPCODE_ENABLE_MOTORS		0x13
#define OPCODE_DISABLE_MOTORS		0x14
#define OPCODE_FALL_PROTECTION		0x15
#define OPCODE_MOTOR_PROTECTION		0x16
#define OPCODE_LOW_BATTERY_CUTOFF	0x17
#define OPCODE_BUZZ_PREVENTION		0x18
#define OPCODE_SET_IO_TYPE			0x19
#define OPCODE_IO_WRITE				0x1A
#define OPCODE_I2C_WRITE			0x1B
#define OPCODE_CIRCLE_DANCE			0x1C
#define OPCODE_LIFELIKE_BEHAVIOURS	0x1D
#define OPCODE_ENABLE_SAFETIES		0x1E
#define OPCODE_SET_PARAMETER		0x1F
#define OPCODE_GET_FIRMWARE_VERSION	0x20
#define OPCODE_MUTE_ESP_SERIAL		0x21
#define OPCODE_CLEAR_CALIBRATION	0xFE
#define OPCODE_SAVE_CALIBRATION		0xFF

// gets
int cmd_get_sensor(std::vector<uint8_t> &cmd, uint8_t sensor_code, uint8_t sensor_id);
int cmd_get_battery(std::vector<uint8_t> &cmd);
int cmd_get_accel(std::vector<uint8_t> &cmd, uint8_t axis);

// commands
int cmd_hello(std::vector<uint8_t> &cmd, uint8_t type);
int cmd_walk(std::vector<uint8_t> &cmd, uint8_t steps, int8_t turn, uint16_t move_time, int8_t step_length, int8_t side);
int cmd_enable_safeties(std::vector<uint8_t> &cmd);

#endif