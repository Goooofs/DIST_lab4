#ifndef SINGLETON_H
#define SINGLETON_H

#include <string>

class Singleton {
public:
    static Singleton& getInstance();
    
    void setKey(const std::string& key);
    void encrypt(const std::string& path);
    void decrypt(const std::string& path);

private:
    Singleton() = default;
    ~Singleton() = default;
    
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    void processFile(const std::string& filePath, bool encryptMode);
    
    std::string current_key;
};

#endif // SINGLETON_H