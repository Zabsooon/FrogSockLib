#include "Socket.h"
#include "Address.h"

#include <iostream>

int main() {
    Address address("127.0.0.1", "42069");
    // Test if all methods work:
    std::cout << address.getAddressFamily() << std::endl;
    std::cout << address.getAddressLength() << std::endl;
    return;
}