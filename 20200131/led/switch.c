#include<stdio.h>
#include<wiringPi.h>

#define SW 6 //BCM_GPIO 25
#define LED 4 //BCM_GPIO 23

int main(void){

	if(wiringPiSetup() == -1)
	return -1;	
	
	pinMode(SW,INPUT)	;
	pinMode('A', OUTPUT);
	
	for(;;)
	{
		if(digitalRead(SW) == 0)
		{
			digitalWrite(LED, 1);
		}
		else {
			digitalWrite(LED, 0);
		}
	}
	return 0;
}
