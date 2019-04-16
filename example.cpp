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

#include "marty.h"



using namespace std;


int main(void){
	marty mymarty;
	if (mymarty.connect_ip("192.168.0.113") < 0){
		printf("Error connecting to Marty\n");
		return -1;
	}


	mymarty.hello(1);
	mymarty.walk(2, 120, 2000, 40, SIDE_ANY);
	mymarty.wait(2);

	float batt = mymarty.get_battery();
	printf("Battery: %.2f\n", batt);


	for (int i=0; i<100; i++){
		float accel = mymarty.get_accel(0);
		printf("Accel 0: %.2f\n", accel);
		mymarty.milliwait(100);
	}

	mymarty.disconnect();

}