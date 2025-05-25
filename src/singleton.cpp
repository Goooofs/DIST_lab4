#include "../include/singleton.h"
#include "../include/aes_encrypt.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

Singleton& Singleton::Instance() {
    static Singleton instance;
    return instance;
}

bool Singleton::encryptFile(const std::string& filename, const std::string& password) {
    if (!fs::exists(filename)) {
        std::cerr << "Файл не найден: " << filename << std::endl;
        return false;
    }

    std::string outputFile = filename + ".enc";

    bool result = aesEncryptFile(filename, outputFile, password);
    if (result) {

        fs::remove(filename);
        std::cout << "Файл успешно зашифрован: " << outputFile << std::endl;

    } else {

        std::cerr << "Ошибка при шифровании файла." << std::endl;

    }
    return result;
}

bool Singleton::decryptFile(const std::string& filename, const std::string& password) {
    namespace fs = std::filesystem;

    if (!fs::exists(filename)) {
        std::cerr << "Файл не найден: " << filename << std::endl;
        return false;
    }

    std::string outputFileTmp = filename + ".tmp";
    std::string outputFileFinal = filename.substr(0, filename.size() - 4);

    bool result = aesDecryptFile(filename, outputFileTmp, password);
    if (result) {

        fs::remove(filename);
        fs::rename(outputFileTmp, outputFileFinal);
        std::cout << "Файл успешно дешифрован: " << outputFileFinal << std::endl;

    } else {

        std::cerr << "Ошибка при дешифровании файла. Неверный пароль или повреждённые данные." << std::endl;
        if (fs::exists(outputFileTmp)) {
            fs::remove(outputFileTmp);
        }

    }
    return result;
}

