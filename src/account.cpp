#include "account.hpp"

Account::Account(std::string id, std::string userId, double saldoInicial)
    : id_(std::move(id)), userId_(std::move(userId)), saldo_(saldoInicial)
{
    if (saldoInicial < 0.0)
        throw std::invalid_argument("El saldo inicial no puede ser negativo");
}

void Account::depositar(double monto) {
    if (monto <= 0.0)
        throw std::invalid_argument("El monto a depositar debe ser mayor que cero");
    saldo_ += monto;
}

void Account::retirar(double monto) {
    if (monto <= 0.0)
        throw std::invalid_argument("El monto a retirar debe ser mayor que cero");
    if (monto > saldo_)
        throw std::runtime_error("Fondos insuficientes");
    saldo_ -= monto;
}

std::string Account::to_string() const {
    std::ostringstream oss;
    oss << "Cuenta Nº[" << id_ << "] de usuario " << userId_
        << " Saldo: " << std::fixed << std::setprecision(2) << saldo_ << " Gs";
    return oss.str();
}
