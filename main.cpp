#include <iostream>
#include "include/account.hpp"

int main() {
    Account acc{"0000001", "Admin", 100000.0};
    
    std::cout << acc.to_string() << "\n";
    acc.depositar(50000);
    std::cout << "Después de depositar: " << acc.to_string() << "\n";

    try{
        acc.retirar(200000);
    } catch (const std::exception& e) {
        std::cerr << "Error al retirar: " << e.what() << "\n";
    }

    acc.retirar(30000);
    std::cout << "Despues de retirar 30.000 Gs: " << acc.to_string() << "\n";
    return 0;

}