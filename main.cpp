#include <iostream>
#include "transaction.hpp"

int main() {
    Transaction t1{"012345", "ACC001", "deposito", 50000};
    Transaction t2{"012346", "ACC002", "retiro", 30000};

    std::cout << t1.to_string() << std::endl;
    std::cout << t2.to_string() << std::endl;
  
return 0;
}