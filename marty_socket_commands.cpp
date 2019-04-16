#include "marty_socket_commands.h"

int cmd_get_battery(std::vector<uint8_t> &cmd){
	// form is 0x01 sensor_code 0xXX
	cmd.clear();
	cmd.push_back(GET_PACKET);
	cmd.push_back(SENSOR_BATTERY);
	cmd.push_back(0x00);
	return 1;
}

int cmd_get_sensor(std::vector<uint8_t> &cmd, uint8_t sensor_code, uint8_t sensor_id){
	// form is 0x01 sensor_code 0xXX
	cmd.clear();
	cmd.push_back(GET_PACKET);
	cmd.push_back(sensor_code);
	cmd.push_back(sensor_id);
	return 1;
}

int cmd_get_accel(std::vector<uint8_t> &cmd, uint8_t axis){
	return cmd_get_sensor(cmd, SENSOR_ACCEL, axis);
}

int cmd_hello(std::vector<uint8_t> &cmd, uint8_t type){
	// form is 0x02, 0x02, 0x00, uint8_t opcode, uint8_t type
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x02);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_HELLO);
	cmd.push_back(type);
	return 1;
}

int cmd_walk(std::vector<uint8_t> &cmd, uint8_t steps, int8_t turn, uint16_t move_time, int8_t step_length, int8_t side){
	// form is 0x02, 0x07, 0x00, opcode=0x03, uint8 steps, uint8 turn, uint16 move_time, int8 step_length, int8 side
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x07);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_WALK);
	cmd.push_back(steps);
	cmd.push_back((uint8_t) turn);
	cmd.push_back((uint8_t) (move_time & 0xFF));
	cmd.push_back((uint8_t) ((move_time>>8) & 0xFF));
	cmd.push_back((uint8_t) step_length);
	cmd.push_back((uint8_t) side);
	return 1;
}

int cmd_enable_safeties(std::vector<uint8_t> &cmd){
	// 0x02 0x01 0x00 uint8_t opcode
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x01);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_ENABLE_SAFETIES);
	return 1;
}