#pragma once
#include "user.hpp"
#include "account.hpp"
#include "transaction.hpp"
#include <unordered_map>
#include <memory>
#include <string>

class BankDB {
    public:
        BankDB();

        std::shared_ptr<User> crearUsuario(const std::string& nombre, const std::string& apellido, const std::string& pin);
        std::shared_ptr<Account> crearCuenta(const std::string& userId, double saldoInicial = 0.0);
        std::shared_ptr<Transaction> registrarTransaccion(const std::string& accountId, const std::string& tipo, double monto);

        std::shared_ptr<User> getUsuario(const std::string& id) const;
        std::shared_ptr<Account> getCuenta(const std::string& id) const;
    
    private:
        std::unordered_map<std::string, std::shared_ptr<User>> usuarios_;
        std::unordered_map<std::string, std::shared_ptr<Account>> cuentas_;
        std::unordered_map<std::string, std::shared_ptr<Transaction>> transacciones_;

        int userCounter_;
        int accountCounter_;
        int transactionCounter_;

        std::string generarId(const std::string& prefix, int contador) const;
};
