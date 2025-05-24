#ifndef SINGLETON_H
#define SINGLETON_H

#include <string>

class Singleton {
public:
    static Singleton& Instance();

    // Заглушки для шифрования и дешифрования
    bool encryptFile(const std::string& filename, const std::string& password);
    bool decryptFile(const std::string& filename, const std::string& password);

private:
    Singleton() = default;
    ~Singleton() = default;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

};

#endif // SINGLETON_H
