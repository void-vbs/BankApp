#include "session_manager.hpp"

SessionManager& SessionManager::getInstance(){
    static SessionManager instance;
    return instance;
}

void SessionManager::login(const std::shared_ptr<User>& user) {
    currentUser_ = user;
}

void SessionManager::logout() {
    currentUser_.reset();
}

bool SessionManager::isLoggedIn() const {
    return currentUser_ != nullptr;
}

bool SessionManager::isAdmin() const {
    return currentUser_ && currentUser_->isAdmin();
}

std::shared_ptr<User> SessionManager::currentUser() const {
    return currentUser_;
}