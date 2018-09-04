#include "DS4gyro.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor & Destructor
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wlib::DS4gyro::DS4gyro(const int vendor_id, const int product_id, const ConectionMode mode) noexcept
	: kVendorID(vendor_id), kProductID(product_id), kConectionMode(mode) {}
wlib::DS4gyro::~DS4gyro(void) noexcept {}

void wlib::DS4gyro::update(void) noexcept
{
}

void wlib::DS4gyro::close(void) noexcept
{
}

bool wlib::DS4gyro::isDS4Found(void) const noexcept
{
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// System Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Accessor
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int wlib::DS4gyro::getRawGryoX(void) const noexcept { return this->getRawGyro().x; }
int wlib::DS4gyro::getRawGryoY(void) const noexcept { return this->getRawGyro().y; }
int wlib::DS4gyro::getRawGyroZ(void) const noexcept { return this->getRawGyro().z; }
int wlib::DS4gyro::getRawAccelX(void) const noexcept { return this->getRawAccel().x; }
int wlib::DS4gyro::getRawAccelY(void) const noexcept { return this->getRawAccel().y; }
int wlib::DS4gyro::getRawAccelZ(void) const noexcept { return this->getRawAccel().z; }
double wlib::DS4gyro::getGryoX(const double & internal_bias) const noexcept { return this->getGyro().x * internal_bias; }
double wlib::DS4gyro::getGryoY(const double & internal_bias) const noexcept { return this->getGyro().y * internal_bias; }
double wlib::DS4gyro::getGyroZ(const double & internal_bias) const noexcept { return this->getGyro().z * internal_bias; }
double wlib::DS4gyro::getAccelX(const double & internal_bias) const noexcept { return this->getAccel().x * internal_bias; }
double wlib::DS4gyro::getAccelY(const double & internal_bias) const noexcept { return this->getAccel().y * internal_bias; }
double wlib::DS4gyro::getAccelZ(const double & internal_bias) const noexcept { return this->getAccel().z * internal_bias; }
wlib::DS4gyro::Vector3<int> wlib::DS4gyro::getRawGyro(void) const noexcept { return this->raw_gyro_; }
wlib::DS4gyro::Vector3<int> wlib::DS4gyro::getRawAccel(void) const noexcept { return this->raw_accel_; }
wlib::DS4gyro::Vector3<double> wlib::DS4gyro::getGyro(const Vector3<double> & internal_bias) const noexcept{
	const auto raw = this->getRawGyro();
	return Vector3<double>(static_cast<double>(raw.x) / kGyroRange * internal_bias.x, static_cast<double>(raw.y) / kGyroRange * internal_bias.y, static_cast<double>(raw.z) / kGyroRange * internal_bias.z);
}
wlib::DS4gyro::Vector3<double> wlib::DS4gyro::getAccel(const Vector3<double> & internal_bias) const noexcept {
	const auto raw = this->getRawAccel();
	return Vector3<double>(static_cast<double>(raw.x) / kGyroRange * internal_bias.x, static_cast<double>(raw.y) / kGyroRange * internal_bias.y, static_cast<double>(raw.z) / kGyroRange * internal_bias.z);
}