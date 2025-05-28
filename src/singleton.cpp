#include "../include/singleton.h"
#include "../include/aes_encrypt.h"
#include "../include/dirsearch.h"
#include <iostream>
#include <cstdio>

Singleton& Singleton::getInstance() {
    static Singleton instance;
    return instance;
}

void Singleton::setKey(const std::string& key) {
    current_key = key;
}

void Singleton::encrypt(const std::string& path) {
    auto files = DirSearch::getAllFilesRecursively(path);
    for (const auto& file : files) {
        processFile(file, true);
    }
}

void Singleton::decrypt(const std::string& path) {
    auto files = DirSearch::getAllFilesRecursively(path);
    for (const auto& file : files) {
        try {
                processFile(file, false);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка дешифрования " << file << ": " << e.what() << std::endl;
        }
    }
}

void Singleton::processFile(const std::string& filePath, bool encryptMode) {
    std::string tempFile = filePath + ".tmp";
    bool success = false;
    
    if (encryptMode) {
        success = AES::aesEncryptFile(filePath, tempFile, current_key);
    } else {
        success = AES::aesDecryptFile(filePath, tempFile, current_key);
    }

    if (success) {
        std::remove(filePath.c_str()) != 0;
        
        std::rename(tempFile.c_str(), filePath.c_str()) != 0;
        
        std::cout << "Успешно: " << filePath << std::endl;
    } else {
        std::remove(tempFile.c_str());
        throw std::runtime_error("Ошибка обработки файла");
    }
}