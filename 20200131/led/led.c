#include<stdio.h>
#include<wiringPi.h>

#define LED 4 //BCM_GPIO 23

int main(void)
{
	if(wiringPiSetup () == -1)
	return 1;
	
	pinMode (LED, OUTPUT);
	
	for (;;)
	{
	digitalWrite (LED, 1); //on
	delay (1000);
	
	digitalWrite(LED, 0); //off
	delay(1000);
	}
	return 0;
}
