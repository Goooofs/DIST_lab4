#include "../include/dirsearch.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>

void DirSearch::recursiveSearch(const std::string& folderPath, std::vector<std::string>& files) {
    DIR* dir = opendir(folderPath.c_str());
    if (!dir) {
        perror(("Не удалось открыть директорию: " + folderPath).c_str());
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") continue;

        std::string fullPath = folderPath + "/" + name;
        struct stat st;
        if (stat(fullPath.c_str(), &st) != 0) {
            perror(("Не удалось получить информацию о файле: " + fullPath).c_str());
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            recursiveSearch(fullPath, files);
        } else if (S_ISREG(st.st_mode)) {
            files.push_back(fullPath);
        }
    }

    closedir(dir);
}

std::vector<std::string> DirSearch::getAllFilesRecursively(const std::string& folderPath) {
    std::vector<std::string> files;
    recursiveSearch(folderPath, files);
    return files;
}
