#pragma once
#ifndef WLIB_DS4GYRO_HPP
#define WLIB_DS4GYRO_HPP

#include "hidapi/hidapi.h"

namespace wlib {

class DS4gyro {
public:
	enum ConectionMode {
		kUsb, kBluetooth
	};

	enum {
		kGyroRange = 1024,
		kAccelRange = 1024
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

private:

	enum struct IndicesUSB : size_t{
		kGyro_X = 14, kGyro_Y = 16, kGyro_Z = 18,
		kAccel_X = 20, kAccel_Y = 22, kAccel_Z = 24
	};
	enum struct IndicesBT : size_t {
		kGyro_X = 16, kGyro_Y = 18, kGyro_Z = 20,
		kAccel_X = 22, kAccel_Y = 24, kAccel_Z = 26
	};

	Vector3<int> raw_gyro_;
	Vector3<int> raw_accel_;
	hid_device * hid_device_;
	bool is_opening_;
	unsigned char buffer[1024];

	int readInt16LE(const int index);
	void calculate(void);

};

}

#endif
