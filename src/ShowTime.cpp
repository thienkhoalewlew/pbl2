#include "../include/ShowTime.h"
#include "../include/FileManager.h"
#include <sstream>
#include <stdexcept>

ShowTime::ShowTime(std::string id, std::string movieId, std::string roomId, std::string showTime, std::string showDate)
    : id(id), movieId(movieId), roomId(roomId), showTime(showTime), showDate(showDate) {}

std::string ShowTime::getId() const { return id; }
std::string ShowTime::getMovieId() const { return movieId; }
std::string ShowTime::getRoomId() const { return roomId; }
std::string ShowTime::getShowTime() const { return showTime; }
std::string ShowTime::getShowDate() const { return showDate; }

void ShowTime::save(const ShowTime& showtime) {
    FileManager::appendLine("../DB/showtimes.dat", showtime.toString());
}

void ShowTime::update(const ShowTime& showtime) {
    auto lines = FileManager::readLines("../DB/showtimes.dat");
    for (auto& line : lines) {
        ShowTime s = ShowTime::fromString(line);
        if (s.getId() == showtime.getId()) {
            line = showtime.toString();
            break;
        }
    }
    FileManager::writeLines("../DB/showtimes.dat", lines);
}

void ShowTime::remove(const std::string& id) {
    auto lines = FileManager::readLines("../DB/showtimes.dat");
    auto newLines = std::vector<std::string>();
    for (const auto& line : lines) {
        ShowTime s = ShowTime::fromString(line);
        if (s.getId() != id) {
            newLines.push_back(line);
        }
    }
    FileManager::writeLines("../DB/showtimes.dat", newLines);
}

ShowTime ShowTime::getById(const std::string& id) {
    auto lines = FileManager::readLines("../DB/showtimes.dat");
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
    auto lines = FileManager::readLines("../DB/showtimes.dat");
    for (const auto& line : lines) {
        showtimes.push_back(ShowTime::fromString(line));
    }
    return showtimes;
}

std::string ShowTime::toString() const {
    return id + "," + movieId + "," + roomId + "," + showTime + "," + showDate;
}

ShowTime ShowTime::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }
    if (tokens.size() != 5) throw std::runtime_error("Invalid showtime string");
    return ShowTime(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
}