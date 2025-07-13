#include <iostream>
#include "include/user.hpp"

int main() {
    User u {"001", "Admin", "1234"};
    std::string entered;
    std::cout << "Ingresa tu PIN: ";
    std::cin >> entered;
    if (u.verifyPin(entered))
        std::cout << "Pin correcto.\n";
    else
        std::cout << "Pin incorrecto.\n";
    return 0;

}