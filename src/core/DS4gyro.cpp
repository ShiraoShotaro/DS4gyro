#include "DS4gyro.hpp"
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor & Destructor
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wlib::DS4gyro::DS4gyro(const int vendor_id, const int product_id, const ConectionMode mode) noexcept
	: kVendorID(vendor_id), kProductID(product_id), kConectionMode(mode), hid_device_(nullptr), is_opening_(false){
	if ((this->hid_device_ = hid_open(this->kVendorID, this->kProductID, nullptr)) != nullptr){
		this->is_opening_ = true;
		this->update();
		this->buffer[0] = 0x02;
		int ret = hid_get_feature_report(this->hid_device_, this->buffer, sizeof(this->buffer));
		if (ret < 0) std::cerr << "Error has occured." << std::endl;
	}
}
wlib::DS4gyro::~DS4gyro(void) noexcept {}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// System Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void wlib::DS4gyro::update(void) noexcept{
	if (this->is_opening_) {
		int read_bytes = hid_read(this->hid_device_, this->buffer, sizeof(this->buffer));
		if (read_bytes < 0) std::cerr << "HID receive error" << std::endl; else this->calculate();
	} else std::cerr << "BAD Request update with hid closing." << std::endl;
}
void wlib::DS4gyro::close(void) noexcept{
	if (this->is_opening_) { hid_close(this->hid_device_); hid_exit(); }
	this->is_opening_ = false;
}
bool wlib::DS4gyro::isOpening(void) const noexcept{ return this->is_opening_; }

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
	return Vector3<double>(static_cast<double>(raw.x) / kAccelRange * internal_bias.x, static_cast<double>(raw.y) / kAccelRange * internal_bias.y, static_cast<double>(raw.z) / kAccelRange * internal_bias.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int wlib::DS4gyro::readInt16LE(const int index){ return static_cast<int>(static_cast<short>(this->buffer[index + 1] << 8 | this->buffer[index])); }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Calculate
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void wlib::DS4gyro::calculate(void){
	this->raw_gyro_.x = this->readInt16LE(kConectionMode == kUsb ? static_cast<size_t>(IndicesUSB::kGyro_X) : static_cast<size_t>(IndicesBT::kGyro_X));
	this->raw_gyro_.y = this->readInt16LE(kConectionMode == kUsb ? static_cast<size_t>(IndicesUSB::kGyro_Y) : static_cast<size_t>(IndicesBT::kGyro_Y));
	this->raw_gyro_.z = this->readInt16LE(kConectionMode == kUsb ? static_cast<size_t>(IndicesUSB::kGyro_Z) : static_cast<size_t>(IndicesBT::kGyro_Z));
	this->raw_accel_.x = this->readInt16LE(kConectionMode == kUsb ? static_cast<size_t>(IndicesUSB::kAccel_X) : static_cast<size_t>(IndicesBT::kAccel_X));
	this->raw_accel_.y = this->readInt16LE(kConectionMode == kUsb ? static_cast<size_t>(IndicesUSB::kAccel_Y) : static_cast<size_t>(IndicesBT::kAccel_Y));
	this->raw_accel_.z = this->readInt16LE(kConectionMode == kUsb ? static_cast<size_t>(IndicesUSB::kAccel_Z) : static_cast<size_t>(IndicesBT::kAccel_Z));
}
