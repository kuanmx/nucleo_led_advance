//
// Created by poh14 on 2/24/2018.
//

#include "MotorTest.h"

MotorTest::MotorTest(PinName inputPin, Serial& target)
	:_interruptInput(inputPin), _target(target)
{
	_interruptInput.rise(callback(this, &MotorTest::onRise));
	_interruptInput.fall(callback(this, &MotorTest::onFall));
	timer.start();
}
void MotorTest::onRise()
{
	if (riseCount<_totalCount) {
		riseTime[riseCount++] = timer.read_high_resolution_us();
	}
}
void MotorTest::onFall()
{
	if (fallCount<_totalCount) {
		fallTime[fallCount++] = timer.read_high_resolution_us();
	}
}

inline void MotorTest::print()
{
	_target.printf("\nRise count: %d", riseCount);
	_target.printf("\nPrinting rise:\n");
	for (auto& val : riseTime) {
		_target.printf("%llu, ", val);
	}
	_target.printf("\nFall count: %d", riseCount);
	_target.printf("\nPrinting fall:\n");
	for (auto& val : fallTime) {
		_target.printf("%llu, ", val);
	}
}

void MotorTest::printOnInput()
{
	if (_target.readable()) {
		print();
	}
}
//MotorTest::MotorTest(PinName inputPin)
//: _interruptInput(inputPin), _target(Serial(SERIAL_TX, SERIAL_RX, 115200))
//{
//}