#include "../include/Showtime.h"
#include "../include/FileManager.h"
#include <sstream>
#include <stdexcept>

ShowTime::ShowTime(int id, int movieId, int roomId, std::string showTime, std::string showDate)
    : id(id), movieId(movieId), roomId(roomId), showTime(showTime), showDate(showDate) {}

int ShowTime::getId() const { return id; }
int ShowTime::getMovieId() const { return movieId; }
int ShowTime::getRoomId() const { return roomId; }
std::string ShowTime::getShowTime() const { return showTime; }
std::string ShowTime::getShowDate() const { return showDate; }

void ShowTime::save(const ShowTime& showtime) {
    FileManager::appendLine("showtimes.txt", showtime.toString());
}

void ShowTime::update(const ShowTime& showtime) {
    auto lines = FileManager::readLines("showtimes.txt");
    for (auto& line : lines) {
        ShowTime s = ShowTime::fromString(line);
        if (s.getId() == showtime.getId()) {
            line = showtime.toString();
            break;
        }
    }
    FileManager::writeLines("../DB/showtimes.txt", lines);
}

ShowTime ShowTime::getById(int id) {
    auto lines = FileManager::readLines("../DB/showtimes.txt");
    for (const auto& line : lines) {
        ShowTime s = ShowTime::fromString(line);
        if (s.getId() == id) {
            return s;
        }
    }
    throw std::runtime_error("Showtime not found");
}

std::vector<ShowTime> ShowTime::getAll() {
    std::vector<ShowTime> showtimes;
    auto lines = FileManager::readLines("../DB/showtimes.txt");
    for (const auto& line : lines) {
        showtimes.push_back(ShowTime::fromString(line));
    }
    return showtimes;
}

std::string ShowTime::toString() const {
    return std::to_string(id) + "," + std::to_string(movieId) + "," + std::to_string(roomId) + "," + showTime + "," + showDate;
}

ShowTime ShowTime::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }
    if (tokens.size() != 5) throw std::runtime_error("Invalid showtime string");
    return ShowTime(std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]), tokens[3], tokens[4]);
}