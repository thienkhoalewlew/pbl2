#include "../include/FileManager.h"
#include <fstream>
#include <iostream>

std::vector<std::string> FileManager::readLines(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    
    if (file.is_open()) {
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    
    return lines;
}

void FileManager::writeLines(const std::string& filename, const std::vector<std::string>& lines) {
    std::ofstream file(filename);
    
    if (file.is_open()) {
        for (const auto& line : lines) {
            file << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void FileManager::appendLine(const std::string& filename, const std::string& line) {
    std::ofstream file(filename, std::ios::app);
    
    if (file.is_open()) {
        file << line << std::endl;
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}