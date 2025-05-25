#ifndef DIRSEARCH_H
#define DIRSEARCH_H

#include <string>
#include <vector>

class DirSearch {
public:
    static std::vector<std::string> getAllFilesRecursively(const std::string& folderPath);

private:
    static void recursiveSearch(const std::string& folderPath, std::vector<std::string>& files);
};

#endif // DIRSEARCH_H
