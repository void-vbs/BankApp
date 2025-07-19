#pragma once
#include <memory>
#include "user.hpp"

class SessionManager {
    public:
        static SessionManager& getInstance();
        
        void login(const std::shared_ptr<User>& user);
        void logout();

        bool isLoggedIn() const;
        bool isAdmin() const;
        std::shared_ptr<User> currentUser() const;

    private:
        SessionManager() = default;
        std::shared_ptr<User> currentUser_;
};