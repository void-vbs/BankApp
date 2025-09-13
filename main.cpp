#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "include/bankdb.hpp"
#include "user_auth.hpp"
#include "session_manager.hpp"

// nombre (no ID)
std::shared_ptr<User> buscarUsuarioPorNombre(const BankDB& db, const std::string& nombre) {
    for (int i = 1; i < 1000000; ++i) {
        std::ostringstream oss;
        oss << std::setw(6) << std::setfill('0') << i;
        auto user = db.getUsuario(oss.str());
        if (user && user->getName() == nombre) {
            return user;
        }
    }
    auto admin = db.getUsuario("Admin");
    if (admin && admin->getName() == nombre) return admin;
    return nullptr;
}

std::vector<std::shared_ptr<Account>> cuentasDeUsuario(const BankDB& db, const std::string& userId) {
    std::vector<std::shared_ptr<Account>> cuentas;
    for (int i = 1; i < 1000000; ++i) {
        std::ostringstream oss;
        oss << std::setw(6) << std::setfill('0') << i;
        auto cuenta = db.getCuenta(oss.str());
        if (cuenta && cuenta->getUserId() == userId) {
            cuentas.push_back(cuenta);
        }
    }
    return cuentas;
}

void menuUsuarioNormal(BankDB& db) {
    auto user = SessionManager::getInstance().currentUser();
    std::cout << "\nBienvenido, " << user->getName() << "!" << std::endl;

    while (true) {
        std::cout << "\n--- Menú Usuario ---\n";
        std::cout << "1. Ver cuentas y saldo\n";
        std::cout << "2. Depositar dinero\n";
        std::cout << "3. Retirar dinero\n";
        std::cout << "4. Transferir a otra cuenta\n";
        std::cout << "5. Cerrar sesión\n";
        std::cout << "6. Salir\n";
        std::cout << "Seleccione una opción: ";

        int opcion;
        std::cin >> opcion;
        std::cin.ignore();

        if (opcion == 1) {
            auto cuentas = cuentasDeUsuario(db, user->getId());
            if (cuentas.empty()) {
                std::cout << "No tienes cuentas asociadas.\n";
            } else {
                for (const auto& c : cuentas) {
                    std::cout << c->to_string() << std::endl;
                }
            }
        } else if (opcion == 2) {
            // Depósito
            auto cuentas = cuentasDeUsuario(db, user->getId());
            if (cuentas.empty()) {
                std::cout << "No tienes cuentas para depositar.\n";
                continue;
            }
            std::cout << "Seleccione cuenta (ID): ";
            for (const auto& c : cuentas) std::cout << c->getId() << " ";
            std::cout << "\nCuenta: ";
            std::string cuentaId; std::getline(std::cin, cuentaId);
            auto cuenta = db.getCuenta(cuentaId);
            if (!cuenta || cuenta->getUserId() != user->getId()) {
                std::cout << "Cuenta inválida.\n";
                continue;
            }
            std::cout << "Monto a depositar: ";
            double monto; std::cin >> monto; std::cin.ignore();
            try {
                cuenta->depositar(monto);
                db.registrarTransaccion(cuentaId, "Depósito", monto);
                std::cout << "Depósito exitoso.\n";
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        } else if (opcion == 3) {
            // Retiro
            auto cuentas = cuentasDeUsuario(db, user->getId());
            if (cuentas.empty()) {
                std::cout << "No tienes cuentas para retirar.\n";
                continue;
            }
            std::cout << "Seleccione cuenta (ID): ";
            for (const auto& c : cuentas) std::cout << c->getId() << " ";
            std::cout << "\nCuenta: ";
            std::string cuentaId; std::getline(std::cin, cuentaId);
            auto cuenta = db.getCuenta(cuentaId);
            if (!cuenta || cuenta->getUserId() != user->getId()) {
                std::cout << "Cuenta inválida.\n";
                continue;
            }
            std::cout << "Monto a retirar: ";
            double monto; std::cin >> monto; std::cin.ignore();
            try {
                cuenta->retirar(monto);
                db.registrarTransaccion(cuentaId, "Retiro", monto);
                std::cout << "Retiro exitoso.\n";
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        } else if (opcion == 4) {
            // Transferencia
            auto cuentas = cuentasDeUsuario(db, user->getId());
            if (cuentas.empty()) {
                std::cout << "No tienes cuentas para transferir.\n";
                continue;
            }
            std::cout << "Seleccione tu cuenta origen (ID): ";
            for (const auto& c : cuentas) std::cout << c->getId() << " ";
            std::cout << "\nCuenta origen: ";
            std::string cuentaOrigenId; std::getline(std::cin, cuentaOrigenId);
            auto cuentaOrigen = db.getCuenta(cuentaOrigenId);
            if (!cuentaOrigen || cuentaOrigen->getUserId() != user->getId()) {
                std::cout << "Cuenta inválida.\n";
                continue;
            }
            std::cout << "Nombre del destinatario: ";
            std::string nombreDest; std::getline(std::cin, nombreDest);
            auto userDest = buscarUsuarioPorNombre(db, nombreDest);
            if (!userDest || userDest->getId() == user->getId() || userDest->isAdmin()) {
                std::cout << "Usuario destino inválido.\n";
                continue;
            }
            auto cuentasDest = cuentasDeUsuario(db, userDest->getId());
            if (cuentasDest.empty()) {
                std::cout << "El destinatario no tiene cuentas.\n";
                continue;
            }
            std::cout << "Seleccione cuenta destino (ID): ";
            for (const auto& c : cuentasDest) std::cout << c->getId() << " ";
            std::cout << "\nCuenta destino: ";
            std::string cuentaDestId; std::getline(std::cin, cuentaDestId);
            auto cuentaDest = db.getCuenta(cuentaDestId);
            if (!cuentaDest || cuentaDest->getUserId() != userDest->getId()) {
                std::cout << "Cuenta destino inválida.\n";
                continue;
            }
            std::cout << "Monto a transferir: ";
            double monto; std::cin >> monto; std::cin.ignore();
            try {
                cuentaOrigen->retirar(monto);
                cuentaDest->depositar(monto);
                db.registrarTransaccion(cuentaOrigenId, "Transferencia salida", monto);
                db.registrarTransaccion(cuentaDestId, "Transferencia entrada", monto);
                std::cout << "Transferencia exitosa.\n";
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        } else if (opcion == 5) {
            SessionManager::getInstance().logout();
            break;
        } else if (opcion == 6) {
            std::exit(0);
        } else {
            std::cout << "Opción inválida.\n";
        }
    }
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

            UserAuth auth(db);
            if (auth.registerUser(nombre, apellido, pin)) {
                // Buscar el usuario recién creado y crearle una cuenta bancaria
                auto user = buscarUsuarioPorNombre(db, nombre);
                if (user) {
                    db.crearCuenta(user->getId(), 0.0);
                    std::cout << "Usuario y cuenta bancaria creados con éxito.\n";
                } else {
                    std::cout << "Usuario creado, pero no se pudo crear la cuenta bancaria.\n";
                }
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
                std::string nombre, pin;
                std::cout << "Nombre de usuario: ";
                std::getline(std::cin, nombre);
                std::cout << "PIN: ";
                std::getline(std::cin, pin);

                auto user = buscarUsuarioPorNombre(db, nombre);
                if (!user) {
                    std::cout << "Usuario no encontrado.\n";
                    continue;
                }
                if (!user->verifyPin(pin)) {
                    std::cout << "PIN incorrecto.\n";
                    continue;
                }
                SessionManager::getInstance().login(user);
                std::cout << "Inicio de sesión exitoso.\n";
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
