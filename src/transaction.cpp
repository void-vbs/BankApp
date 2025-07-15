#include "transaction.hpp"
#include <sstream>
#include <iomanip>

Transaction::Transaction(std::string id, std::string accountId, std::string tipo, double monto)
    : id_(std::move(id)), accountId_(std::move(accountId)), tipo_(std::move(tipo)), monto_(monto)
{
    fechaHora_ = std::time(nullptr); // guarda hora actual
}

std::string Transaction::getFechaHora() const {
    std::tm* tm_ptr = std::localtime(&fechaHora_);
    std::ostringstream oss;
    oss << std::put_time(tm_ptr, "%d/%m/%Y %H:%M:%S");
    return oss.str();
}

std::string Transaction::to_string() const {
    std::ostringstream oss;
    oss << "ID de Transacción: " << id_ << " "
        << tipo_ << " de " << std::fixed << std::setprecision(2) << monto_
        << " Gs en cuenta " << accountId_
        << " (" << getFechaHora() << ")";
    return oss.str();
}