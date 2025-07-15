#pragma once
#include <string>
#include <chrono>
#include <ctime>

class Transaction {
    public:
        Transaction(std::string id, std::string accountId, std::string tipo, double monto);
        
        const std::string& getId() const        { return id_; }
        const std::string& getaccountId() const { return accountId_;}
        const std::string& getTipo() const      { return tipo_; }
        const double getMonto() const           { return monto_; }
        std::string getFechaHora() const;

        std::string to_string() const;

    private:
        std::string id_;
        std::string accountId_;
        std::string tipo_;          // deposito o retiro
        double monto_;
        std::time_t fechaHora_;
};