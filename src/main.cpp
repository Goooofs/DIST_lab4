#include <iostream>
#include <string>
#include "../include/singleton.h"

void printUsage() {
    std::cout << "Использование:\n"
              << "./main encrypt <filename> <password>  - шифрование\n"
              << "./main decrypt <filename> <password>  - дешифрование\n";
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];
    std::string filename = argv[2];
    std::string password = argv[3];

    bool success = false;

    if (command == "encrypt") {
        success = Singleton::Instance().encryptFile(filename, password);
    } else if (command == "decrypt") {
        success = Singleton::Instance().decryptFile(filename, password);
    } else {
        printUsage();
        return 1;
    }

    if (!success) {
        std::cerr << "Операция не выполнена." << std::endl;
        return 1;
    }

    return 0;
}
