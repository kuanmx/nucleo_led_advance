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
			"compilerSwitches": "-std=c++14"
		}
	]
}
*/
#include "intelliSense.h"
#include "mbed.h"

Timer ledBrightness; 
Ticker reportBrightness; 
Ticker blinkingLed; 

InterruptIn usrBtn(USER_BUTTON); 

DigitalOut blinkLed(D13);
PwmOut glowLed(D9);

/* Baud rate: 9600 (default)
change baud rate at mbed_config.h*/
Serial serial(SERIAL_TX, SERIAL_RX); 

void flip() {
	blinkLed = !blinkLed;
}

void interruptFall() {
	serial.printf("User pressed button. \n"); 
	blinkingLed.detach(); 
	blinkLed = 1.0f; 
}

void interruptRise() {
	serial.printf("User released button. \n"); 
	blinkingLed.attach(&flip, 0.5);
}

void report() {
	serial.printf("ledBrightness: %f \n", glowLed.read());
}

int main() {
	// initialize 
	glowLed = 0.0f;
	ledBrightness.start();
	reportBrightness.attach(&report, 0.5);  // attach event to Ticker for time recurring interupt
	blinkingLed.attach(&flip, 0.5);			// attach event to Ticker for time recurring interupt

	usrBtn.fall(&interruptFall);
	usrBtn.rise(&interruptRise);

	serial.printf("System start. \n\n"); 
    while(1) {
		glowLed.write(ledBrightness.read()/2);
		float k = ledBrightness.read(); 
		if (ledBrightness.read() > 2) ledBrightness.reset();  // ledBrightness reset every 2 seconds
		
		/*
        blinkLed = 1; // LED is ON
        wait(0.2); // 200 ms
        blinkLed = 0; // LED is OFF
        wait(1.0); // 1 sec
		*/
    }
}
