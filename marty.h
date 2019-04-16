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

	int hello(uint8_t type);
	int walk(uint8_t steps, int8_t turn, uint16_t move_time, int8_t step_length, int8_t side);
	int enable_safeties();
};


#endif