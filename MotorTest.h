
#ifndef STM32TEST2_MOTORTEST_H
#define STM32TEST2_MOTORTEST_H
#include "intelliSense.h"
#include "mbed.h"
#include <memory>

class MotorTest {
public:
	MotorTest() = delete;
	MotorTest(PinName inputPin, Serial& target);

	void printOnInput();
private:
	InterruptIn _interruptInput;
	Serial& _target;
	Timer timer;
	static const int _totalCount = 1000;
	void onRise();
	void onFall();
	void print();

	std::array<long long, _totalCount> riseTime;
	std::array<long long, _totalCount> fallTime;
	int riseCount = 0;
	int fallCount = 0;

};

#endif //STM32TEST2_MOTORTEST_H