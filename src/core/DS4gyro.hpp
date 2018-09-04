﻿#pragma once
#ifndef WLIB_DS4GYRO_HPP
#define WLIB_DS4GYRO_HPP

#include "hidapi/hidapi.h"

#include <windows.h>


#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>

#define VENDOR_ID 1356		// The vendor & product ID of HID device to be used:
#define PRODUCT_ID 1476		//		(Currently setup for PS4 controller)

#define ACC_FACTOR 9.8 / 8100.		// No' of m/s2 per arb unit of acceleration

#define GYRO_FACTOR 1. / 1024.		// No of rad/s per arb unit of angular velocity
#define GYRO_ERROR 0.001			// Estimated error on gyroscope measurement in rad/s

#define TIME_FACTOR 0.00125 / 188.	// No' of secs per arb unit of time 


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

namespace wlib {

class DS4gyro {
public:
	enum ConectionMode {
		kUsb, kBluetooth
	};

	enum {
		kGyroRange = 1024
	};

	template <typename T> struct Vector3 {
		T x, y, z;
		Vector3(void) noexcept : x(0), y(0), z(0) {}
		Vector3(T _x, T _y, T _z) noexcept : x(_x), y(_y), z(_z) {}
	};

	struct Quaternion : public Vector3<double> {
		double w;
		Quaternion(void) noexcept : Vector3(), w(0.0) {}
		Quaternion(double _x, double _y, double _z, double _w) : Vector3<double>(_x, _y, _z), w(_w) {}
	};

	const int kVendorID;
	const int kProductID;
	const ConectionMode kConectionMode;

	DS4gyro(const int vendor_id, const int product_id, const ConectionMode mode = kUsb) noexcept;

	~DS4gyro(void) noexcept;

	void update(void) noexcept;

	void close(void) noexcept;

	bool isOpening(void) const noexcept;

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
	hid_device * hid_device_;
	bool is_opening_;
	unsigned char buffer[1024];

	int readInt16LE(const int index);
	
	unsigned int readInt16LEUnsigned(const int index);
	
	int readInt8(const int index);

	void calculate(void);

};

}

#endif
