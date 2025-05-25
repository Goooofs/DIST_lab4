#include <iostream>
#include <string>
#include "../include/singleton.h"

void printUsage() {
    std::cout << "Использование:" << std::endl; 
    std::cout << "./main encrypt <path> <password> - шифрование" << std::endl;
    std::cout << "./main decrypt <path> <password> - дешифрование" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printUsage();
        return 1;
    }

    std::string mode = argv[1];
    std::string path = argv[2];
    std::string password = argv[3];

    try {
        Singleton& singleton = Singleton::getInstance();
        singleton.setKey(password);

        if (mode == "encrypt") {
            singleton.encrypt(path);
            std::cout << "Шифрование завершено" << std::endl;
        } else if (mode == "decrypt") {
            singleton.decrypt(path);
            std::cout << "Дешифрование завершено" << std::endl;
        } else {
            printUsage();
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
