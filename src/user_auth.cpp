#include "user_auth.hpp"
#include "session_manager.hpp"
#include <iostream>

UserAuth::UserAuth(BankDB& db) : db_(db) {}

bool UserAuth::registerUser(const std::string& nombre, const std::string& apellido, const std::string& pin) {
    std::string id = db_.generateUniqueUserId();
    auto user = std::make_shared<User>(id, nombre, apellido, pin);
    db_.addUser(user);
    std::cout << "Usario registrado exitosamente. ID: " << id << std::endl;
    return true;
}

bool UserAuth::login(const std::string& userId, const std::string& pin) {
    auto user = db_.getUsuario(userId);
    if (!user) {
        std::cout << "Usuario no encontrado." << std::endl;
        return false;
    }
    if (!user->verifyPin(pin)) {
        std::cout << "PIN incorrecto." << std::endl;
        return false;
    }
    SessionManager::getInstance().login(user);
    std::cout << "Inicio de sesión exitoso. Usuario: " << user->getName() << "!" << std::endl;
    return true;
}