#include "user.hpp"
#include "picosha2.h"
#include <random>
#include <sstream>  
#include <iomanip>

std::string User::randomSalt(size_t len) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist (0, 255);
    std::ostringstream ss;
    for (size_t i = 0; i < len; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << dist(rd);
    return ss.str();
}

std::string User::hashPin(const std::string& pin, const std::string& salt) {
    return picosha2::hash256_hex_string(pin + salt);

}

User::User(std::string id, std::string nombre, std::string apellido, std::string plainPin)
    : id_(std::move(id)), nombre_(std::move(nombre)), apellido_(std::move(apellido)) {
        salt_ = randomSalt(16);
        pinHash_ = hashPin(plainPin, salt_);
    }

    std::string User::to_string() const {
    std::ostringstream oss;
    oss << id_ << " - " << nombre_ << " " << apellido_;
    if (isAdmin_) oss << " [Admin]";
    return oss.str();
}

bool User::verifyPin(const std::string& plainPin) const {
    return hashPin(plainPin, salt_) == pinHash_;
}
