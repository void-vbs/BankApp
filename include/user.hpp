#pragma once
#include <string>

class User {
public:
    User(std::string id, std::string nombre, std::string apellido, std::string plainPin);

    const std::string& getId()   const { return id_; }
    const std::string& getName() const { return nombre_; }

    bool verifyPin(const std::string& plainPin) const;
    bool isAdmin() const { return isAdmin_; }
    std::string to_string() const;
    void setAdmin(bool admin) { isAdmin_ = admin; }

private:
    std::string id_;
    std::string nombre_;
    std::string apellido_;
    std::string salt_;
    std::string pinHash_;
    bool isAdmin_ = false;

    static std::string randomSalt(size_t len = 16);
    static std::string hashPin(const std::string& pin,
                               const std::string& salt);
};
