#pragma once
#include <string>

class User {
public:
    User(std::string id, std::string name, std::string plainPin);

    const std::string& getId()   const { return id_; }
    const std::string& getName() const { return name_; }

    bool verifyPin(const std::string& plainPin) const;

private:
    std::string id_;
    std::string name_;
    std::string salt_;
    std::string pinHash_;

    static std::string randomSalt(size_t len = 16);
    static std::string hashPin(const std::string& pin,
                               const std::string& salt);
};
