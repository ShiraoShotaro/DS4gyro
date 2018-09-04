#pragma once
#ifndef WLIB_DS4GYRO_HPP
#define WLIB_DS4GYRO_HPP

#include "hidapi/hidapi.h"

#include <windows.h>


#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>

//****************************  DEVICE ID  ****************************//
/*
// Address the correct HID using it's vendor and product IDs
*/
#define VENDOR_ID 1356		// The vendor & product ID of HID device to be used:
#define PRODUCT_ID 1476		//		(Currently setup for PS4 controller)

//****************************  SENSOR DETAILS  ****************************//
/*
// Values for the ranges of sensors, and factors to map sensor units into SI units
// These have been worked out from a combination of guess work and info contained
// at:
//	1) https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMI055-DS000-08.pdf (IMU datasheet)
//	2) http://gamedev.stackexchange.com/questions/87106/accessing-dualshock-4-motion-sensor-in-windows-ideally-unity
//  3) https://github.com/Flafla2/Unity-DS4
*/
#define ACC_FACTOR 9.8 / 8100.		// No' of m/s2 per arb unit of acceleration

#define GYRO_FACTOR 1. / 1024.		// No of rad/s per arb unit of angular velocity
#define GYRO_ERROR 0.001			// Estimated error on gyroscope measurement in rad/s

#define TIME_FACTOR 0.00125 / 188.	// No' of secs per arb unit of time 


//****************************  MEMORY ADDRESSES  ****************************//
/*
// The location of relevant bytes within the HID read buffer. All the motion sensors
// use 16bit memory space, and values here refer to the byte with smaller index. Note that
// byte order is reversed for all of the IMU outputs. Values here have come from:
// 1) https://gist.github.com/johndrinkwater/7708901
// 2) http://eleccelerator.com/wiki/index.php?title=DualShock_4
// 3) https://github.com/ehd/node-ds4
// The coordinate sys used by the IMU is right handed, and oriented as shown in
// - \GyroProject\docs\DS4-axis.pdf
*/


// Indices for controller connected via USB
#define GX_INDEX_USB 14		
#define GY_INDEX_USB 16
#define GZ_INDEX_USB 18
#define DX_INDEX_USB 20
#define DY_INDEX_USB 22
#define DZ_INDEX_USB 24
#define TIME_INDEX_USB 11 //Index of the timestamp byte

// Indices for controller connected via Bluetooth
#define GX_INDEX_BLUETOOTH 16
#define GY_INDEX_BLUETOOTH 18
#define GZ_INDEX_BLUETOOTH 20
#define DX_INDEX_BLUETOOTH 22
#define DY_INDEX_BLUETOOTH 24
#define DZ_INDEX_BLUETOOTH 26
#define TIME_INDEX_BLUETOOTH 13


//****************************   ALGO' SETTING    ****************************//
/*
//  We use Seb Madgwick's IMU sensor fusion algo' to couple the gro' and accelerometer
// sensor readings from the controller. For more detail, refer to Seb's website:
// http://www.x-io.co.uk/open-source-ahrs-with-x-imu/.
//
// My understanding of what Beta does is to dictate how much attention is paid to the
// accelerometer data in the sensor fusion process. This define specifies it's default
// value - it can also be changed via a set method within the class.
*/
#define BETA 0.5

enum ConectionMode { USB, BLUETOOTH };

namespace wlib {

class DS4gyro {
public:
	enum ConectionMode {
		kUsb, kBluetooth
	};

	template <typename T> struct Vector3 {
		T x, y, z;
		Vector3(void) noexcept : x(0.0), y(0.0), z(0.0) {}
		Vector3(T _x, T _y, T _z) noexcept : x(_x), y(_y), z(_z) {}
	};

	struct Quaternion : public Vector3<double> {
		double w;
		Quaternion(void) noexcept : Vector3(), w(0.0) {}
		Quaternion(double _x, double _y, double _z, double _w) Vector3(_x, _y, _z), w(_w) {}
	};

	DS4gyro(const int vendor_id, const int product_id, const ConectionMode mode = kUsb) noexcept;

	~DS4gyro(void) noexcept;

	void update(void) noexcept;

	void close(void) noexcept;

	bool isDS4Found(void) const noexcept;

	int getRawGryoX(void) const noexcept;

	int getRawGryoY(void) const noexcept;

	int getRawGyroZ(void) const noexcept;

	int getRawAccelX(void) const noexcept;

	int getRawAccelY(void) const noexcept;

	int getRawAccelZ(void) const noexcept;

	virtual double getGryoX(const double & internal_bias = 1.0) const noexcept;

	virtual double getGryoY(const double & internal_bias = 1.0) const noexcept;

	virtual double getGyroZ(const double & internal_bias = 1.0) const noexcept;

	virtual double getAccelX(const double & internal_bias = 1.0) const noexcept;

	virtual double getAccelY(const double & internal_bias = 1.0) const noexcept;

	virtual double getAccelZ(const double & internal_bias = 1.0) const noexcept;

	virtual Vector3<int> getRawGyro(void) const noexcept;

	virtual Vector3<int> getRawAccel(void) const noexcept;

	virtual Vector3<double> getGyro(const Vector3<double> & internal_bias = Vector3<double>(1.0, 1.0, 1.0)) const noexcept;

	virtual Vector3<double> getAccel(const Vector3<double> & internal_bias = Vector3<double>(1.0, 1.0, 1.0)) const noexcept;


	//#####よくわからない者たち
	void setBeta(const float beta);

	int getRawTimestamp();
	float getTimestamp();
	float getTime();

	int getArbPair(int index);
	int getArbSingle(int index);

private:



	Vector3<int> raw_gyro_;
	Vector3<int> raw_accel_;

	int readInt16LE(const int index);
	int readInt16LEUnsigned(const int index);
	int readInt8(const int index);

	void updateHID();
	void updateTimeStep();
	void updateAHRS(float dt, float gx, float gy, float gz, float ax, float ay, float az);



	hid_device* _hidDevice;
	unsigned char _buffer[256];
	int _resultFlag;

	float _previousTimestamp;
	float _timeStep;
	float _time;

	float _quaternion[4];
	float _beta;

	int GX_Index;
	int GY_Index;
	int GZ_Index;
	int DX_Index;
	int DY_Index;
	int DZ_Index;
	int TIME_Index;

};

}

#endif
