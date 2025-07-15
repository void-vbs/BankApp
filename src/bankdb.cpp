#include "bankdb.hpp"
#include <sstream>
#include <iomanip>
#include <stdexcept>

BankDB::BankDB() : userCounter_(1), accountCounter_(1), transactionCounter_(1) {}
std::string BankDB::generarId(const std::string& prefix, int contador) const {
    std::ostringstream oss;
    oss << prefix << std::setw(6) << std::setfill('0') << contador;
    return oss.str();
}

std::shared_ptr<User> BankDB::crearUsuario(const std::string& nombre, const std::string& apellido, const std::string& pin) {
    std::string id = generarId("", userCounter_ ++);
    auto user = std::make_shared<User>(id, nombre, apellido, pin);
    usuarios_[id] = user;
    return user;
}

std::shared_ptr<Account> BankDB::crearCuenta(const std::string& userId, double saldoInicial) {
    if (usuarios_.find(userId) == usuarios_.end()) 
        throw std::invalid_argument("Usuario no encontrado");
    std::string id = generarId("", accountCounter_ ++);
    auto cuenta = std::make_shared<Account>(id, userId, saldoInicial);
    cuentas_[id] = cuenta;
    return cuenta;
}

std::shared_ptr<Transaction> BankDB::registrarTransaccion(const std::string& accountId, const std::string& tipo, double monto) {
    if (cuentas_.find(accountId) == cuentas_.end()) 
        throw std::invalid_argument("Cuenta no encontrada");
    std::string id = generarId("",transactionCounter_++);
    auto trans = std::make_shared<Transaction>(id, accountId, tipo, monto);
    transacciones_[id] = trans;
    return trans;
}

std::shared_ptr<User> BankDB::getUsuario(const std::string& id) const {
    auto it = usuarios_.find(id);
    return (it != usuarios_.end()) ? it->second : nullptr;
}

std::shared_ptr<Account> BankDB::getCuenta(const std::string& id) const {
    auto it = cuentas_.find(id);
    return (it != cuentas_.end()) ? it->second : nullptr;
}