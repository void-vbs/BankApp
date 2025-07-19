#include <iostream>
#include <memory>
#include <string>
#include "bankdb.hpp"
#include "user_auth.hpp"
#include "session_manager.hpp"

void menuUsuarioNormal(BankDB& db) {
    auto user = SessionManager::getInstance().currentUser();
    std::cout << "\nBienvenido, " << user->getName() << "!" << std::endl;

    SessionManager::getInstance().logout();  
}

void menuAdmin(BankDB& db) {
    while (true) {
        std::cout << "\n--- Menú Administrador ---\n";
        std::cout << "1. Crear nuevo usuario\n";
        std::cout << "2. Cerrar sesión\n";
        std::cout << "3. Salir del sistema\n";
        std::cout << "Seleccione una opción: ";

        int opcion;
        std::cin >> opcion;
        std::cin.ignore();

        if (opcion == 1) {
            std::string nombre, apellido, pin;
            std::cout << "Nombre: ";
            std::getline(std::cin, nombre);
            std::cout << "Apellido: ";
            std::getline(std::cin, apellido);
            std::cout << "PIN (4 dígitos): ";
            std::getline(std::cin, pin);

            auto auth = UserAuth(db);
            if (auth.registerUser(nombre, apellido, pin)) {
                std::cout << "Usuario creado con éxito.\n";
            } else {
                std::cout << "Error al crear el usuario.\n";
            }

        } else if (opcion == 2) {
            SessionManager::getInstance().logout();
            break;
        } else if (opcion == 3) {
            std::exit(0);
        } else {
            std::cout << "Opción inválida.\n";
        }
    }
}

int main() {
    BankDB db;
    db.initDefaultAdmin();  

    UserAuth auth(db);

    while (true) {
        if (!SessionManager::getInstance().isLoggedIn()) {
            std::cout << "\n--- Sistema Bancario ---\n";
            std::cout << "1. Iniciar sesión\n";
            std::cout << "2. Salir\n";
            std::cout << "Seleccione una opción: ";

            int opcion;
            std::cin >> opcion;
            std::cin.ignore();  

            if (opcion == 1) {
                std::string userId, pin;
                std::cout << "ID de usuario: ";
                std::getline(std::cin, userId);
                std::cout << "PIN: ";
                std::getline(std::cin, pin);

                if (auth.login(userId, pin)) {
                    std::cout << "Inicio de sesión exitoso.\n";
                } else {
                    std::cout << "ID o PIN incorrecto.\n";
                }
            } else if (opcion == 2) {
                break;
            } else {
                std::cout << "Opción no válida.\n";
            }
        } else {
            if (SessionManager::getInstance().isAdmin()) {
                menuAdmin(db);
            } else {
                menuUsuarioNormal(db);
            }
        }
    }

    return 0;
}
