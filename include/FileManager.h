#pragma once
#include<string>
#include<vector>
#include<fstream>

class FileManager{
    public:
        static std::vector<std::string> readLines(const std::string& filename);
        static void writeLines(const std::string& filename, const std::vector<std::string>& lines);
        static void appendLine(const std::string& filename, const std::string& line);
};