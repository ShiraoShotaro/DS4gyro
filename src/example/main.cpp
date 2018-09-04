#include "core\DS4gyro.hpp"
#include <iostream>
int main(void){
	
	wlib::DS4gyro ds4gyro(0x054C, 0x09CC);

	while (true) {
	
		ds4gyro.update();

		std::cout << "GX: " << ds4gyro.getRawGyroX();
		std::cout << " GY: " << ds4gyro.getRawGyroY();
		std::cout << " GZ: " << ds4gyro.getRawGyroZ();
		std::cout << " AX: " << ds4gyro.getRawAccelX();
		std::cout << " AY: " << ds4gyro.getRawAccelY();
		std::cout << " AZ: " << ds4gyro.getRawAccelZ() << std::endl;
	
	}

	ds4gyro.close();
}