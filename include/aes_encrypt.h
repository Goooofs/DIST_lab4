#ifndef AES_ENCRYPT_H
#define AES_ENCRYPT_H

#include <string>

class AES {
    public:
        static bool aesEncryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& password);
        static bool aesDecryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& password);
};

#endif // AES_ENCRYPT_H
