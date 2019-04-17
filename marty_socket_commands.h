#ifndef __MARTY_SOCKET_COMMANDS
#define __MARTY_SOCKET_COMMANDS

#include <stdlib.h>
#include <vector>
#include <stdint.h>
#include <string.h>

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

#define STOP_FINISH_CURRENT			0x00
#define STOP_FREEZE					0x01
#define STOP_FREEZE_DISABLE			0x02
#define STOP_FREEZE_ZERO			0x03
#define STOP_PAUSE					0x04
#define STOP_PAUSE_DISABLE			0x05

#define JOINT_LEFT_HIP				0x00
#define JOINT_LEFT_TWIST			0x01
#define JOINT_LEFT_KNEE				0x02
#define JOINT_RIGHT_HIP				0x03
#define JOINT_RIGHT_TWIST			0x04
#define JOINT_RIGHT_KNEE			0x05
#define JOINT_LEFT_ARM				0x06
#define JOINT_RIGHT_ARM				0x07
#define JOINT_EYES					0x08

// gets
int cmd_get_sensor(std::vector<uint8_t> &cmd, uint8_t sensor_code, uint8_t sensor_id);
int cmd_get_battery(std::vector<uint8_t> &cmd);
int cmd_get_accel(std::vector<uint8_t> &cmd, uint8_t axis);
int cmd_get_motor_current(std::vector<uint8_t> &cmd, uint8_t motorID);
int cmd_get_gpio(std::vector<uint8_t> &cmd, uint8_t gpioID);
int cmd_get_chatter(std::vector<uint8_t> &cmd);
int cmd_get_motor_position(std::vector<uint8_t> &cmd, uint8_t motorID);
int cmd_get_motor_enabled(std::vector<uint8_t> &cmd, uint8_t motorID);

// commands
int cmd_hello(std::vector<uint8_t> &cmd, uint8_t type);
int cmd_lean(std::vector<uint8_t> &cmd, uint8_t direction, int8_t amount, uint16_t move_time);
int cmd_walk(std::vector<uint8_t> &cmd, uint8_t steps, int8_t turn, uint16_t move_time, int8_t step_length, int8_t side);
int cmd_kick(std::vector<uint8_t> &cmd, uint8_t side, int8_t twist, uint16_t move_time);
int cmd_celebrate(std::vector<uint8_t> &cmd, uint16_t move_time);
int cmd_tap_foot(std::vector<uint8_t> &cmd, int8_t side);
int cmd_arms(std::vector<uint8_t> &cmd, int8_t r_angle, int8_t l_angle, uint16_t move_time);
int cmd_sidestep(std::vector<uint8_t> &cmd, int8_t side, int8_t num_steps, uint16_t move_time, int8_t step_length);
int cmd_stand_straight(std::vector<uint8_t> &cmd, uint16_t move_time);
int cmd_play_sound(std::vector<uint8_t> &cmd, uint16_t freq_start, uint16_t freq_end, uint16_t duration);
int cmd_stop(std::vector<uint8_t> &cmd, uint8_t stop_type);
int cmd_move_joint(std::vector<uint8_t> &cmd, uint8_t jointID, int8_t position, uint16_t move_time);
int cmd_enable_motors(std::vector<uint8_t> &cmd, uint16_t motor_flags, int8_t mode);
int cmd_enable_motors(std::vector<uint8_t> &cmd);
int cmd_disable_motors(std::vector<uint8_t> &cmd, uint16_t motor_flags, int8_t mode);
int cmd_disable_motors(std::vector<uint8_t> &cmd);
int cmd_fall_protection(std::vector<uint8_t> &cmd, bool enabled);
int cmd_motor_protection(std::vector<uint8_t> &cmd, bool enabled);
int cmd_low_battery_cutoff(std::vector<uint8_t> &cmd, bool enabled);
int cmd_buzz_prevention(std::vector<uint8_t> &cmd, bool enabled);
int cmd_set_io_type(std::vector<uint8_t> &cmd, uint8_t gpioID, int8_t type);
int cmd_io_write(std::vector<uint8_t> &cmd, uint8_t gpioID, float value);
int cmd_i2c_write(std::vector<uint8_t> &cmd, uint8_t data[], uint8_t num_bytes);
int cmd_circle_dance(std::vector<uint8_t> &cmd, uint8_t side, uint16_t move_time);
int cmd_lifelike_behaviours(std::vector<uint8_t> &cmd, bool enabled);
int cmd_enable_safeties(std::vector<uint8_t> &cmd);
int cmd_set_parameter(std::vector<uint8_t> &cmd, uint8_t paramID, uint8_t params[], uint8_t param_bytes);
int cmd_get_firmware_version(std::vector<uint8_t> &cmd);
int cmd_mute_esp_serial(std::vector<uint8_t> &cmd);
int cmd_clear_calibration(std::vector<uint8_t> &cmd);
int cmd_save_calibration(std::vector<uint8_t> &cmd);

#endif