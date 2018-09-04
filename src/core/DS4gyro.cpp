#include "DS4gyro.hpp"

//

wlib::DS4gyro::DS4gyro(const int vendor_id, const int product_id, const ConectionMode mode) noexcept
{
}

wlib::DS4gyro::~DS4gyro(void) noexcept
{
}

int wlib::DS4gyro::getRawGryoX(void) const noexcept
{
	return 0;
}

int wlib::DS4gyro::getRawGryoY(void) const noexcept
{
	return 0;
}

int wlib::DS4gyro::getRawGyroZ(void) const noexcept
{
	return 0;
}

int wlib::DS4gyro::getRawAccelX(void) const noexcept
{
	return 0;
}

int wlib::DS4gyro::getRawAccelY(void) const noexcept
{
	return 0;
}

int wlib::DS4gyro::getRawAccelZ(void) const noexcept
{
	return 0;
}

double wlib::DS4gyro::getGryoX(const double & internal_bias) const noexcept
{
	return 0.0;
}

double wlib::DS4gyro::getGryoY(const double & internal_bias) const noexcept
{
	return 0.0;
}

double wlib::DS4gyro::getGyroZ(const double & internal_bias) const noexcept
{
	return 0.0;
}

double wlib::DS4gyro::getAccelX(const double & internal_bias) const noexcept
{
	return 0.0;
}

double wlib::DS4gyro::getAccelY(const double & internal_bias) const noexcept
{
	return 0.0;
}

double wlib::DS4gyro::getAccelZ(const double & internal_bias) const noexcept
{
	return 0.0;
}

wlib::DS4gyro::Vector3<int> wlib::DS4gyro::getRawGyro(void) const noexcept
{
	return Vector3<int>();
}

wlib::DS4gyro::Vector3<int> wlib::DS4gyro::getRawAccel(void) const noexcept
{
	return Vector3<int>();
}

wlib::DS4gyro::Vector3<double> wlib::DS4gyro::getGyro(const Vector3<double> & internal_bias = Vector3<double>(1.0, 1.0, 1.0)) const noexcept
{
	return Vector3<double>();
}

wlib::DS4gyro::Vector3<double> wlib::DS4gyro::getAccel(const Vector3<double> & internal_bias = Vector3<double>(1.0, 1.0, 1.0)) const noexcept
{
	return Vector3<double>();
}
