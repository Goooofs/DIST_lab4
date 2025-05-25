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
            if (file.size() > 4 && file.substr(file.size() - 4) == ".enc") {
                processFile(file, false);
            } else {
                std::cout << "Пропускаем (не .enc файл): " << file << std::endl;
            }
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
        std::string outputFile = filePath.substr(0, filePath.size() - 4);
        success = AES::aesDecryptFile(filePath, tempFile, current_key);
    }

    if (success) {
        std::remove(filePath.c_str()) != 0;

        std::string newName = filePath;
        if (encryptMode) {
            newName += ".enc";
        } else {
            newName.resize(newName.size() - 4);
        }
        
        std::rename(tempFile.c_str(), newName.c_str()) != 0;
        
        std::cout << "Успешно: " << filePath << " -> " << newName << std::endl;
    } else {
        std::remove(tempFile.c_str());
        throw std::runtime_error("Ошибка обработки файла");
    }
}