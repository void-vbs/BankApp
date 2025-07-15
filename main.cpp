#include <iostream>
#include "bankdb.hpp"
#include "user.hpp"
#include "account.hpp"

int main() {
    BankDB db;
    auto user = db.crearUsuario("Elon", "Musk", "6969");
    auto account = db.crearCuenta(user->getId(), 200000.0);
    auto trans1 = db.registrarTransaccion(account->getId(), "deposito", 50000.0);
    auto trans2 = db.registrarTransaccion(account->getId(), "retiro", 30000.0);

    std::cout << "Usuario: " << user->to_string() << std::endl;
    std::cout << account->to_string() << std::endl;
    std::cout << trans1->to_string() << std::endl;
    std::cout << trans2->to_string() << std::endl;
return 0;
}