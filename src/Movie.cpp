#include "../include/Movie.h"
#include "../include/FileManager.h"
#include <sstream>
#include <stdexcept>

Movie::Movie(int id, std::string name, std::string duration, std::string showStartDate, std::string showStopDate) 
    : id(id), name(name), duration(duration), showStartDate(showStartDate), showStopDate(showStopDate) {}

int Movie::getId() const { return id; }
std::string Movie::getName() const { return name; }  // Thêm getter cho name
std::string Movie::getDuration() const { return duration; }
std::string Movie::getShowStartDate() const { return showStartDate; }
std::string Movie::getShowStopDate() const { return showStopDate; }

void Movie::save(const Movie& Movie) {
    FileManager::appendLine("../DB/movies.txt", Movie.toString());
} 

void Movie::update(const Movie& movie) {
    auto lines = FileManager::readLines("../DB/movies.txt");
    for (auto& line : lines) {
        Movie m = Movie::fromString(line);
        if(m.getId() == movie.getId()) {
            line = movie.toString();
            break;
        }
    }
    FileManager::writeLines("../DB/movies.txt", lines);
}

Movie Movie::getbyId(int id) {
    auto lines = FileManager::readLines("../DB/movies.txt");
    for(const auto& line : lines) {
        Movie m = Movie::fromString(line);
        if(m.getId() == id) {
            return m;
        }
    }
    throw std::runtime_error("Movie not found");
}

std::vector<Movie> Movie::getAll() {
    std::vector<Movie> movies;
    auto lines = FileManager::readLines("../DB/movies.txt");
    for(const auto& line : lines) {
        movies.push_back(Movie::fromString(line));
    }
    return movies;
}

std::string Movie::toString() const {
    return std::to_string(id) + "," + name + "," + duration + "," + showStartDate + "," + showStopDate;
}

Movie Movie::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;
    while(std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }
    if(tokens.size() != 5) throw std::runtime_error("Invalid movie string");
    return Movie(std::stoi(tokens[0]), tokens[1], tokens[2], tokens[3], tokens[4]);
}