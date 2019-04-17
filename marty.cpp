#include "marty.h"


marty::marty(){
	this->sock = 0;
	this->nbytes = 0;
}

// SOCKET & CONNECTION FUNCTIONS

int marty::connect_ip(const char *marty_ip_addr){
	printf("Marty c++ socket control demo\nInitialising socket...\n");

	if ((sock = socket(AF_INET, SOCK_STREAM, 0))<0){
		printf("Error creating socketn");
		//return -1;
	}

	memset(&this->marty_addr, 0, sizeof(this->marty_addr));

	this->marty_addr.sin_family = AF_INET;
	this->marty_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, marty_ip_addr, &(this->marty_addr.sin_addr))<=0)  { 
        printf("\nError in IP address form- please check  it has been entered correctly\n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&this->marty_addr, sizeof(this->marty_addr)) < 0){ 
        printf("\nConnection Failed - is there a Marty on that IP?\n"); 
        return -1; 
    } 

    //fcntl(sock, F_SETFL, O_NONBLOCK);
    printf("Connection established\n\r");

    // ENABLE SAFETIES
    this->enable_safeties();

    return 1;
}

void marty::disconnect(){
	close(sock);
}

int marty::send_cmd(std::vector<uint8_t> &cmd){
	return send(this->sock, &(*cmd.begin()), (int)cmd.size(), 0);
}

// UTILITIES

void marty::wait ( float seconds ){
  clock_t endwait;
  endwait = clock () + (int) (seconds * CLOCKS_PER_SEC);
  while (clock() < endwait) {}
}

void marty::milliwait(unsigned int milliseconds){
	// borrowed from timmurphy.org
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = milliseconds * 1000000L;
	nanosleep(&req, (struct timespec *)NULL);
}

// SENSOR READ COMMANDS
float marty::get_battery(){
	int bytes_read = 0;
	float battery = 0;
	std::vector<uint8_t> cmd;
	cmd_get_battery(cmd);
	this->send_cmd(cmd);
	bytes_read = read(this->sock, &battery, 1000);
	if (bytes_read != sizeof(battery)){
		return -1;
	}
	return battery;
}

float marty::get_accel(uint8_t axis){
	int bytes_read = 0;
	float accel = 0;
	std::vector<uint8_t> cmd;
	cmd_get_accel(cmd, axis);
	this->send_cmd(cmd);
	bytes_read = read(this->sock, &accel, 1000);
	if (bytes_read != sizeof(accel)){
		return -1;
	}
	return accel;
}

float marty::get_motor_current(uint8_t motorID){
	int bytes_read = 0;
	float current = 0;
	std::vector<uint8_t> cmd;
	cmd_get_motor_current(cmd, motorID);
	this->send_cmd(cmd);
	bytes_read = read(this->sock, &current, 1000);
	if (bytes_read != sizeof(current)){
		return -1;
	}
	return current;
}

float marty::get_gpio(uint8_t gpioID){
	int bytes_read = 0;
	float gpio = 0;
	std::vector<uint8_t> cmd;
	cmd_get_gpio(cmd, gpioID);
	this->send_cmd(cmd);
	bytes_read = read(this->sock, &gpio, 1000);
	if (bytes_read != sizeof(gpio)){
		return -1;
	}
	return gpio;
}

int marty::get_chatter(char *chatter){
	int bytes_read = 0;
	std::vector<uint8_t> cmd;
	cmd_get_chatter(cmd);
	this->send_cmd(cmd);
	bytes_read = read(this->sock, &chatter, 1000);
	return bytes_read;
}

int8_t marty::get_motor_position(uint8_t motorID){
	int bytes_read = 0;
	int8_t motor_position = 0;
	std::vector<uint8_t> cmd;
	cmd_get_motor_position(cmd, motorID);
	this->send_cmd(cmd);
	char *buffer;
	bytes_read = read(this->sock, &buffer, 1000);
	if (bytes_read != sizeof(motor_position)){
		return -1;
	}
	motor_position = (int8_t) buffer[0];
	return motor_position;
}

int8_t marty::get_motor_enabled(uint8_t motorID){
	int bytes_read = 0;
	uint8_t enabled = 0;
	std::vector<uint8_t> cmd;
	cmd_get_motor_enabled(cmd, motorID);
	this->send_cmd(cmd);
	char *buffer;
	bytes_read = read(this->sock, &buffer, 1000);
	if (bytes_read != sizeof(enabled)){
		return -1;
	}
	return buffer[0];
}

// COMMANDS

int marty::hello(uint8_t type){
	std::vector<uint8_t> cmd;
	cmd_hello(cmd, type);
	return this->send_cmd(cmd);
}

int marty::lean(uint8_t direction, int8_t amount, uint16_t move_time){
	std::vector<uint8_t> cmd;
	cmd_lean(cmd, direction, amount, move_time);
	return this->send_cmd(cmd);	
}

int marty::walk(uint8_t steps, int8_t turn, uint16_t move_time, int8_t step_length, int8_t side){
	std::vector<uint8_t> cmd;
	cmd_walk(cmd, steps, turn, move_time, step_length, side);
	return this->send_cmd(cmd);
}

int marty::kick(uint8_t side, int8_t twist, uint16_t move_time){
	std::vector<uint8_t> cmd;
	cmd_kick(cmd, side, twist, move_time);
	return this->send_cmd(cmd);
}

int marty::celebrate(uint16_t move_time){
	std::vector<uint8_t> cmd;
	cmd_celebrate(cmd, move_time);
	return this->send_cmd(cmd);
}

int marty::tap_foot(int8_t side){
	std::vector<uint8_t> cmd;
	cmd_tap_foot(cmd, side);
	return this->send_cmd(cmd);
}

int marty::arms(int8_t r_angle, int8_t l_angle, uint16_t move_time){
	std::vector<uint8_t> cmd;
	cmd_arms(cmd, r_angle, l_angle, move_time);
	return this->send_cmd(cmd);
}

int marty::sidestep(int8_t side, int8_t num_steps, uint16_t move_time, int8_t step_length){
	std::vector<uint8_t> cmd;
	cmd_sidestep(cmd, side, num_steps, move_time, step_length);
	return this->send_cmd(cmd);
}

int marty::stand_straight(uint16_t move_time){
	std::vector<uint8_t> cmd;
	cmd_stand_straight(cmd, move_time);
	return this->send_cmd(cmd);
}

int marty::play_sound(uint16_t freq_start, uint16_t freq_end, uint16_t duration){
	std::vector<uint8_t> cmd;
	cmd_play_sound(cmd, freq_start, freq_end, duration);
	return this->send_cmd(cmd);
}

int marty::stop(uint8_t stop_type){
	std::vector<uint8_t> cmd;
	cmd_stop(cmd, stop_type);
	return this->send_cmd(cmd);
}

int marty::move_joint(uint8_t jointID, int8_t position, uint16_t move_time){
	std::vector<uint8_t> cmd;
	cmd_move_joint(cmd, jointID, position, move_time);
	return this->send_cmd(cmd);
}

int marty::enable_motors(uint16_t motor_flags, int8_t mode){
	std::vector<uint8_t> cmd;
	cmd_enable_motors(cmd, motor_flags, mode);
	return this->send_cmd(cmd);
}

int marty::enable_motors(){
	std::vector<uint8_t> cmd;
	cmd_enable_motors(cmd, 0xFFFF, 0);
	return this->send_cmd(cmd);
}

int marty::disable_motors(uint16_t motor_flags, int8_t mode){
	std::vector<uint8_t> cmd;
	cmd_disable_motors(cmd, motor_flags, mode);
	return this->send_cmd(cmd);
}

int marty::disable_motors(){
	std::vector<uint8_t> cmd;
	cmd_disable_motors(cmd, 0xFFFF, 0);
	return this->send_cmd(cmd);
}

int marty::fall_protection(bool enabled){
	std::vector<uint8_t> cmd;
	cmd_fall_protection(cmd, enabled);
	return this->send_cmd(cmd);
}

int marty::motor_protection(bool enabled){
	std::vector<uint8_t> cmd;
	cmd_motor_protection(cmd, enabled);
	return this->send_cmd(cmd);
}

int marty::low_battery_cutoff(bool enabled){
	std::vector<uint8_t> cmd;
	cmd_low_battery_cutoff(cmd, enabled);
	return this->send_cmd(cmd);
}

int marty::buzz_prevention(bool enabled){
	std::vector<uint8_t> cmd;
	cmd_buzz_prevention(cmd, enabled);
	return this->send_cmd(cmd);
}

int marty::set_io_type(uint8_t gpioID, int8_t type){
	std::vector<uint8_t> cmd;
	cmd_set_io_type(cmd, gpioID, type);
	return this->send_cmd(cmd);
}

int marty::io_write(uint8_t gpioID, float value){
	std::vector<uint8_t> cmd;
	cmd_io_write(cmd, gpioID, value);
	return this->send_cmd(cmd);
}

int marty::i2c_write(uint8_t data[], uint8_t num_bytes){
	std::vector<uint8_t> cmd;
	cmd_i2c_write(cmd, data, num_bytes);
	return this->send_cmd(cmd);
}

int marty::circle_dance(uint8_t side, uint16_t move_time){
	std::vector<uint8_t> cmd;
	cmd_circle_dance(cmd, side, move_time);
	return this->send_cmd(cmd);
}

int marty::lifelike_behaviours(bool enabled){
	std::vector<uint8_t> cmd;
	cmd_lifelike_behaviours(cmd, enabled);
	return this->send_cmd(cmd);
}

int marty::enable_safeties(){
	std::vector<uint8_t> cmd;
	cmd_enable_safeties(cmd);
	return this->send_cmd(cmd);
}

int marty::set_parameter(uint8_t paramID, uint8_t params[], uint8_t param_bytes){
	std::vector<uint8_t> cmd;
	cmd_set_parameter(cmd, paramID, params, param_bytes);
	return this->send_cmd(cmd);
}

int marty::get_firmware_version(){
	std::vector<uint8_t> cmd;
	cmd_get_firmware_version(cmd);
	return this->send_cmd(cmd);
}

int marty::mute_esp_serial(){
	std::vector<uint8_t> cmd;
	cmd_mute_esp_serial(cmd);
	return this->send_cmd(cmd);
}

int marty::clear_calibration(){
	std::vector<uint8_t> cmd;
	cmd_clear_calibration(cmd);
	return this->send_cmd(cmd);
}

int marty::save_calibration(){
	std::vector<uint8_t> cmd;
	cmd_save_calibration(cmd);
	return this->send_cmd(cmd);
}
