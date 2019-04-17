#ifndef __MARTYROBOT
#define __MARTYROBOT

#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>


#include "marty_socket_commands.h"

#define PORT 24

class marty {
private:
	int sock;
	struct sockaddr_in marty_addr;
	ssize_t nbytes;
	int send_cmd(std::vector<uint8_t> &cmd);
public:
	marty();
	int connect_ip(const char *marty_ip_addr);
	void disconnect();

	void wait( float seconds);
	void milliwait(unsigned int milliseconds);

	float get_battery();
	float get_accel(uint8_t axis);
	float get_motor_current(uint8_t motorID);
	float get_gpio(uint8_t gpioID);
	int get_chatter(char *chatter);
	int8_t get_motor_position(uint8_t motorID);
	int8_t get_motor_enabled(uint8_t motorID);

	int hello(uint8_t type);
	int lean(uint8_t direction, int8_t amount, uint16_t move_time);
	int walk(uint8_t steps, int8_t turn, uint16_t move_time, int8_t step_length, int8_t side);
	int kick(uint8_t side, int8_t twist, uint16_t move_time);
	int celebrate(uint16_t move_time);
	int tap_foot(int8_t side);
	int arms(int8_t r_angle, int8_t l_angle, uint16_t move_time);
	int sidestep(int8_t side, int8_t num_steps, uint16_t move_time, int8_t step_length);
	int stand_straight(uint16_t move_time);
	int play_sound(uint16_t freq_start, uint16_t freq_end, uint16_t duration);
	int stop(uint8_t stop_type);
	int move_joint(uint8_t jointID, int8_t position, uint16_t move_time);
	int enable_motors(uint16_t motor_flags, int8_t mode);
	int enable_motors();
	int disable_motors(uint16_t motor_flags, int8_t mode);
	int disable_motors();
	int fall_protection(bool enabled);
	int motor_protection(bool enabled);
	int low_battery_cutoff(bool enabled);
	int buzz_prevention(bool enabled);
	int set_io_type(uint8_t gpioID, int8_t type);
	int io_write(uint8_t gpioID, float value);
	int i2c_write(uint8_t data[], uint8_t num_bytes);
	int circle_dance(uint8_t side, uint16_t move_time);
	int lifelike_behaviours(bool enabled);
	int enable_safeties();
	int set_parameter(uint8_t paramID, uint8_t params[], uint8_t param_bytes);
	int get_firmware_version();
	int mute_esp_serial();
	int clear_calibration();
	int save_calibration();

};


#endif