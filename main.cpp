/* intelliSense correctio for gcc-arm 
Include intelliSense.h for proper working with intelliSense
for cpp14 feature (ie auto)
go to Project -> Edit Settings -> CppProperties.json and paste the following
{
	"configurations": [
		{
			"inheritEnvironments": [
				"gcc-arm"
			],
			"name": "gccarm",
			"includePath": [
				"${env.INCLUDE}"
			],
			"defines": [

			],
			"compilerSwitches": "-std=c++14",
			"intelliSenseMode": "linux-gcc-arm"
		}
	]
}
*/
#include "intelliSense.h"
#include "mbed.h"

Timer timer_fast; 
Timer timer_slow; 

InterruptIn usrBtn(USER_BUTTON); 

DigitalOut blinkLed(D13);
PwmOut glowLed(D9);

/* Baud rate: 9600 (default)
change baud rate at mbed_config.h*/
Serial serial(SERIAL_TX, SERIAL_RX); 

void interruptRise() {

}

int main() {
	glowLed = 0.0f;
	serial.printf("System start. "); 
	timer_fast.start(); 
	timer_slow.start(); 
    while(1) {
		auto val1 = timer_fast.read_us(); 
		auto val2 = timer_slow.read_us();

		serial.printf("Timer_fast: %d ", val1);
		serial.printf("Timer_slow: %d \n", val2);

		wait(0.5); 
		/*
        blinkLed = 1; // LED is ON
        wait(0.2); // 200 ms
        blinkLed = 0; // LED is OFF
        wait(1.0); // 1 sec
		*/
    }
}
