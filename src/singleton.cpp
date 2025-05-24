#include "../include/singleton.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

Singleton& Singleton::Instance() {
    static Singleton instance;
    return instance;
}

bool Singleton::encryptFile(const std::string& filename, const std::string& password) {
    // просто добавляю расширение .enc
    std::string newName = filename + ".enc";
    try {
        fs::rename(filename, newName);
        std::cout << "Файл зашифрован (переименован) в: " << newName << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при шифровании: " << e.what() << std::endl;
        return false;
    }
}

bool Singleton::decryptFile(const std::string& filename, const std::string& password) {
    // Проверяю расширение .enc и убираю его
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".enc") {
        std::cerr << "Файл не имеет расширения .enc" << std::endl;
        return false;
    }
    std::string newName = filename.substr(0, filename.size() - 4);
    try {
        fs::rename(filename, newName);
        std::cout << "Файл дешифрован (переименован) в: " << newName << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при дешифровании: " << e.what() << std::endl;
        return false;
    }
}
