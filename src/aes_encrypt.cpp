#include "../include/aes_encrypt.h"
#include <openssl/aes.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>

bool AES::aesEncryptFile(const std::string& inFile, const std::string& outFile, const std::string& keyStr) {
    std::ifstream in(inFile, std::ios::binary);

    if (!in) {
        std::cerr << "Не удалось открыть файл для чтения: " << inFile << std::endl;
        return false;
    }

    std::vector<unsigned char> data((std::istreambuf_iterator<char>(in)), {});
    int pad = AES_BLOCK_SIZE - (data.size() % AES_BLOCK_SIZE);
    data.insert(data.end(), pad, static_cast<unsigned char>(pad));

    unsigned char key[32] = {0};
    std::memcpy(key, keyStr.data(), std::min(keyStr.size(), sizeof(key)));

    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, 256, &aesKey) < 0) {
        std::cerr << "Ошибка установки ключа шифрования" << std::endl;
        return false;
    }

    unsigned char iv[AES_BLOCK_SIZE] = {0};

    std::vector<unsigned char> out(data.size());
    AES_cbc_encrypt(data.data(), out.data(), data.size(), &aesKey, iv, AES_ENCRYPT);

    std::ofstream ofs(outFile, std::ios::binary);

    if (!ofs) {
        std::cerr << "Не удалось открыть файл для записи: " << outFile << std::endl;
        return false;
    }

    ofs.write(reinterpret_cast<char*>(out.data()), out.size());

    return true;
}

bool AES::aesDecryptFile(const std::string& inFile, const std::string& outFile, const std::string& keyStr) {
    std::ifstream in(inFile, std::ios::binary);

    if (!in) {
        std::cerr << "Не удалось открыть файл для чтения: " << inFile << std::endl;
        return false;
    }

    std::vector<unsigned char> enc((std::istreambuf_iterator<char>(in)), {});
    if (enc.size() % AES_BLOCK_SIZE != 0) {
        std::cerr << "Некорректный размер файла" << std::endl;
        return false;
    }

    unsigned char key[32] = {0};
    std::memcpy(key, keyStr.data(), std::min(keyStr.size(), sizeof(key)));

    AES_KEY aesKey;
    if (AES_set_decrypt_key(key, 256, &aesKey) < 0) {
        std::cerr << "Ошибка установки ключа дешифрования" << std::endl;
        return false;
    }

    unsigned char iv[AES_BLOCK_SIZE] = {0};

    std::vector<unsigned char> out(enc.size());
    AES_cbc_encrypt(enc.data(), out.data(), enc.size(), &aesKey, iv, AES_DECRYPT);

    if (out.empty()) {
        std::cerr << "Пустой результат дешифрования" << std::endl;
        return false;
    }

    int pad = out.back();

    if (pad <= 0 || pad > AES_BLOCK_SIZE) {
        std::cerr << "Некорректный паддинг" << std::endl;
        return false;
    }

    out.resize(out.size() - pad);

    std::ofstream ofs(outFile, std::ios::binary);
    
    if (!ofs) {
        std::cerr << "Не удалось открыть файл для записи: " << outFile << std::endl;
        return false;
    }

    ofs.write(reinterpret_cast<char*>(out.data()), out.size());

    return true;
}
