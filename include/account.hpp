#pragma once
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>

class Account {
public:
    Account(std::string id, std::string userId, double saldoInicial = 0.0);

    const std::string& getId()      const { return id_; }
    const std::string& getUserId()  const { return userId_; }
    double getSaldo()               const { return saldo_; }

    void depositar(double monto);
    void retirar(double monto);

    std::string to_string() const;

private:
    std::string id_;       
    std::string userId_;  
    double saldo_;         
};
