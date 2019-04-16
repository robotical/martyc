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

    if(inet_pton(AF_INET, marty_ip_addr, &(this->marty_addr.sin_addr))<=0)  
    { 
        printf("\nError in IP address form- please check  it has been entered correctly\n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&this->marty_addr, sizeof(this->marty_addr)) < 0) 
    { 
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

// COMMANDS

int marty::hello(uint8_t type){
	std::vector<uint8_t> cmd;
	cmd_hello(cmd, type);
	return this->send_cmd(cmd);
}

int marty::walk(uint8_t steps, int8_t turn, uint16_t move_time, int8_t step_length, int8_t side){
	std::vector<uint8_t> cmd;
	cmd_walk(cmd, steps, turn, move_time, step_length, side);
	return this->send_cmd(cmd);
}

int marty::enable_safeties(){
	std::vector<uint8_t> cmd;
	cmd_enable_safeties(cmd);
	return this->send_cmd(cmd);
}