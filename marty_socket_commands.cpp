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

int cmd_get_motor_current(std::vector<uint8_t> &cmd, uint8_t motorID){
	return cmd_get_sensor(cmd, SENSOR_MOTOR_CURRENT, motorID);
}


int cmd_get_gpio(std::vector<uint8_t> &cmd, uint8_t gpioID){
	return cmd_get_sensor(cmd, SENSOR_GPIO, gpioID);
}

int cmd_get_chatter(std::vector<uint8_t> &cmd){
	return cmd_get_sensor(cmd, SENSOR_CHATTER, 0);
}

int cmd_get_motor_position(std::vector<uint8_t> &cmd, uint8_t motorID){
	return cmd_get_sensor(cmd, SENSOR_MOTOR_POSITION, motorID);
}

int cmd_get_motor_enabled(std::vector<uint8_t> &cmd, uint8_t motorID){
	return cmd_get_sensor(cmd, SENSOR_MOTOR_ENABLED, motorID);
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

int cmd_lean(std::vector<uint8_t> &cmd, uint8_t direction, int8_t amount, uint16_t move_time){
	// form is 0x02 0x05 0x00, uint8_t opcode, uint8_t direction, int8_t amount, uint16_t move_time
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x05);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_LEAN);
	cmd.push_back(direction);
	cmd.push_back(amount);
	cmd.push_back((uint8_t) (move_time & 0xFF));
	cmd.push_back((uint8_t) ((move_time>>8) & 0xFF));
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

int cmd_kick(std::vector<uint8_t> &cmd, uint8_t side, int8_t twist, uint16_t move_time){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x05);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_KICK);
	cmd.push_back(side);
	cmd.push_back((uint8_t) twist);
	cmd.push_back((uint8_t) (move_time & 0xFF));
	cmd.push_back((uint8_t) ((move_time>>8) & 0xFF));
	return 1;
}

int cmd_celebrate(std::vector<uint8_t> &cmd, uint16_t move_time){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x03);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_CELEBRATE);
	cmd.push_back((uint8_t) (move_time & 0xFF));
	cmd.push_back((uint8_t) ((move_time>>8) & 0xFF));
	return 1;
}

int cmd_tap_foot(std::vector<uint8_t> &cmd, int8_t side){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x02);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_TAP_FOOT);
	cmd.push_back((uint8_t) side);
	return 1;
}

int cmd_arms(std::vector<uint8_t> &cmd, int8_t r_angle, int8_t l_angle, uint16_t move_time){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x05);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_ARMS);
	cmd.push_back((uint8_t) r_angle);
	cmd.push_back((uint8_t) l_angle);
	cmd.push_back((uint8_t) (move_time & 0xFF));
	cmd.push_back((uint8_t) ((move_time>>8) & 0xFF));
	return 1;
}

int cmd_sidestep(std::vector<uint8_t> &cmd, int8_t side, int8_t num_steps, uint16_t move_time, int8_t step_length){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x06);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_SIDESTEP);
	cmd.push_back((uint8_t) side);
	cmd.push_back(num_steps);
	cmd.push_back((uint8_t) (move_time & 0xFF));
	cmd.push_back((uint8_t) ((move_time>>8) & 0xFF));
	cmd.push_back((uint8_t) step_length);
	return 1;
}

int cmd_stand_straight(std::vector<uint8_t> &cmd, uint16_t move_time){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x03);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_STAND_STRAIGHT);
	cmd.push_back((uint8_t) (move_time & 0xFF));
	cmd.push_back((uint8_t) ((move_time>>8) & 0xFF));
	return 1;
}

int cmd_play_sound(std::vector<uint8_t> &cmd, uint16_t freq_start, uint16_t freq_end, uint16_t duration){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x07);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_PLAY_SOUND);
	cmd.push_back((uint8_t) (freq_start & 0xFF));
	cmd.push_back((uint8_t) ((freq_start>>8) & 0xFF));
	cmd.push_back((uint8_t) (freq_end & 0xFF));
	cmd.push_back((uint8_t) ((freq_end>>8) & 0xFF));
	cmd.push_back((uint8_t) (duration & 0xFF));
	cmd.push_back((uint8_t) ((duration>>8) & 0xFF));
	return 1;
}

int cmd_stop(std::vector<uint8_t> &cmd, uint8_t stop_type){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x02);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_STOP);
	cmd.push_back(stop_type);
	return 1;
}

int cmd_move_joint(std::vector<uint8_t> &cmd, uint8_t jointID, int8_t position, uint16_t move_time){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x05);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_MOVE_JOINT);
	cmd.push_back(jointID);
	cmd.push_back((uint8_t) position);
	cmd.push_back((uint8_t) (move_time & 0xFF));
	cmd.push_back((uint8_t) ((move_time>>8) & 0xFF));
	return 1;
}

int cmd_enable_motors(std::vector<uint8_t> &cmd, uint16_t motor_flags, int8_t mode){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x04);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_ENABLE_MOTORS);
	cmd.push_back((uint8_t) (motor_flags & 0xFF));
	cmd.push_back((uint8_t) ((motor_flags>>8) & 0xFF));
	cmd.push_back((uint8_t) mode);
	return 1;
}

int cmd_enable_motors(std::vector<uint8_t> &cmd){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x01);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_ENABLE_MOTORS);
	return 1;
}

int cmd_disable_motors(std::vector<uint8_t> &cmd, uint16_t motor_flags, int8_t mode){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x04);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_DISABLE_MOTORS);
	cmd.push_back((uint8_t) (motor_flags & 0xFF));
	cmd.push_back((uint8_t) ((motor_flags>>8) & 0xFF));
	cmd.push_back((uint8_t) mode);
	return 1;
}

int cmd_disable_motors(std::vector<uint8_t> &cmd){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x01);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_DISABLE_MOTORS);
	return 1;
}

int cmd_fall_protection(std::vector<uint8_t> &cmd, bool enabled){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x02);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_FALL_PROTECTION);
	cmd.push_back((uint8_t) enabled);
	return 1;
}

int cmd_motor_protection(std::vector<uint8_t> &cmd, bool enabled){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x02);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_MOTOR_PROTECTION);
	cmd.push_back((uint8_t) enabled);
	return 1;
}

int cmd_low_battery_cutoff(std::vector<uint8_t> &cmd, bool enabled){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x02);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_LOW_BATTERY_CUTOFF);
	cmd.push_back((uint8_t) enabled);
	return 1;
}

int cmd_buzz_prevention(std::vector<uint8_t> &cmd, bool enabled){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x02);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_BUZZ_PREVENTION);
	cmd.push_back((uint8_t) enabled);
	return 1;
}

int cmd_set_io_type(std::vector<uint8_t> &cmd, uint8_t gpioID, int8_t type){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x03);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_SET_IO_TYPE);
	cmd.push_back(gpioID);
	cmd.push_back((uint8_t) type);
	return 1;
}

int cmd_io_write(std::vector<uint8_t> &cmd, uint8_t gpioID, float value){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x06);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_IO_WRITE);
	cmd.push_back(gpioID);
	cmd.push_back(0);
	cmd.push_back(0);
	cmd.push_back(0);
	cmd.push_back(0);
	memcpy(&cmd[5], &value, sizeof(value));
	return 1;
}

int cmd_i2c_write(std::vector<uint8_t> &cmd, uint8_t data[], uint8_t num_bytes){
	//TODO: cope with writes larger than 254 bytes
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x01 + num_bytes);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_I2C_WRITE);
	for (int i=0; i<num_bytes; i++){
		cmd.push_back(data[i]);
	}
	return 1;
}

int cmd_circle_dance(std::vector<uint8_t> &cmd, uint8_t side, uint16_t move_time){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x04);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_CIRCLE_DANCE);
	cmd.push_back(side);
	cmd.push_back((uint8_t) (move_time & 0xFF));
	cmd.push_back((uint8_t) ((move_time>>8) & 0xFF));
	return 1;
}

int cmd_lifelike_behaviours(std::vector<uint8_t> &cmd, bool enabled){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x02);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_LIFELIKE_BEHAVIOURS);
	cmd.push_back((uint8_t) enabled);
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

int cmd_set_parameter(std::vector<uint8_t> &cmd, uint8_t paramID, uint8_t params[], uint8_t param_bytes){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x02 + param_bytes);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_SET_PARAMETER);
	for (int i=0; i<param_bytes; i++){
		cmd.push_back(params[i]);
	}
	return 1;
}

int cmd_get_firmware_version(std::vector<uint8_t> &cmd){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x01);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_GET_FIRMWARE_VERSION);
	return 1;
}

int cmd_mute_esp_serial(std::vector<uint8_t> &cmd){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x01);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_MUTE_ESP_SERIAL);
	return 1;
}

int cmd_clear_calibration(std::vector<uint8_t> &cmd){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x01);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_CLEAR_CALIBRATION);
	return 1;
}

int cmd_save_calibration(std::vector<uint8_t> &cmd){
	cmd.clear();
	cmd.push_back(CMD_PACKET);
	cmd.push_back(0x01);
	cmd.push_back(0x00);
	cmd.push_back(OPCODE_SAVE_CALIBRATION);
	return 1;
}
