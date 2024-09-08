#include "../include/Movie.h"
#include "../include/FileManager.h"
#include <sstream>
#include <stdexcept>

Movie::Movie(std::string id, std::string name, std::string duration, std::string showStartDate, std::string showStopDate) 
    : id(id), name(name), duration(duration), showStartDate(showStartDate), showStopDate(showStopDate) {}

std::string Movie::getId() const { return id; }
std::string Movie::getName() const { return name; }
std::string Movie::getDuration() const { return duration; }
std::string Movie::getShowStartDate() const { return showStartDate; }
std::string Movie::getShowStopDate() const { return showStopDate; }

void Movie::save(const Movie& Movie) {
    FileManager::appendLine("../DB/movies.dat", Movie.toString());
} 

void Movie::update(const Movie& movie) {
    auto lines = FileManager::readLines("../DB/movies.dat");
    for (auto& line : lines) {
        Movie m = Movie::fromString(line);
        if(m.getId() == movie.getId()) {
            line = movie.toString();
            break;
        }
    }
    FileManager::writeLines("../DB/movies.dat", lines);
}

void Movie::remove(const std::string& id) {
    auto lines = FileManager::readLines("../DB/movies.dat");
    auto newLines = std::vector<std::string>();
    for (const auto& line : lines) {
        Movie m = Movie::fromString(line);
        if (m.getId() != id) {
            newLines.push_back(line);
        }
    }
    FileManager::writeLines("../DB/movies.dat", newLines);
}

Movie Movie::getbyId(const std::string& id) {
    auto lines = FileManager::readLines("../DB/movies.dat");
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
    auto lines = FileManager::readLines("../DB/movies.dat");
    for(const auto& line : lines) {
        movies.push_back(Movie::fromString(line));
    }
    return movies;
}

std::string Movie::toString() const {
    return id + "," + name + "," + duration + "," + showStartDate + "," + showStopDate;
}

Movie Movie::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;
    while(std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }
    if(tokens.size() != 5) throw std::runtime_error("Invalid movie string");
    return Movie(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
}