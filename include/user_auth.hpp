#pragma once
#include <memory>
#include <string>
#include "user.hpp"
#include "bankdb.hpp"

class UserAuth {
    public:
        UserAuth(BankDB& db);

        bool registerUser(const std::string& nombre, const std::string& apellido, const std::string& pin);
        bool login(const std::string& userId, const std::string& pin);

    private:
        BankDB& db_;
};
