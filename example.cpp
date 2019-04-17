#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include "marty.h"



using namespace std;


int main(void){
	marty mymarty;
	if (mymarty.connect_ip("192.168.0.113") < 0){
		printf("Error connecting to Marty\n");
		return -1;
	}


	mymarty.hello(1);
	//mymarty.walk(2, 120, 2000, 40, SIDE_ANY);
	mymarty.lean(SIDE_FORWARD, 50, 1000);
	//mymarty.kick(SIDE_LEFT, 100, 2000);
	//mymarty.celebrate(5000);
	//mymarty.tap_foot(SIDE_RIGHT);
	//mymarty.arms(100, 100, 1000);
	//mymarty.sidestep(SIDE_LEFT, 2, 1000, 70);
	mymarty.stand_straight(1000);
	mymarty.play_sound(50, 2000, 1000);
	mymarty.move_joint(JOINT_EYES, -50, 500);
	mymarty.circle_dance(SIDE_LEFT, 1500);
	mymarty.disable_motors(0xFFFF, 1);			// disable all motors after finishing movements
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