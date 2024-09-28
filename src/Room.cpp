#include "../include/Room.h"
#include "../include/ShowTime.h"
#include "../include/FileManager.h"
#include <sstream>
#include <stdexcept>

Room::Room(std::string id, int capacity) : id(id), capacity(capacity) {}

std::string Room::getId() const { return id; }
int Room::getCapacity() const { return capacity; }

void Room::save(const Room& room) {
    FileManager::appendLine("../DB/rooms.dat", room.toString());
}

void Room::update(const Room& room) {
    auto lines = FileManager::readLines("../DB/rooms.dat");
    for(auto& line : lines) {
        Room r = Room::fromString(line);
        if(r.getId() == room.getId()) {
            line = room.toString();
            break;
        }   
    }
    FileManager::writeLines("../DB/rooms.dat", lines);
}

void Room::remove(const std::string& id) {
    auto lines = FileManager::readLines("../DB/rooms.dat");
    auto newLines = std::vector<std::string>();
    for (const auto& line : lines) {
        Room r = Room::fromString(line);
        if (r.getId() != id) {
            newLines.push_back(line);
        }
    }
    FileManager::writeLines("../DB/rooms.dat", newLines);

    auto linesS= FileManager::readLines("../DB/showtimes.dat");
    for (const auto& line : linesS) {
        ShowTime s = ShowTime::fromString(line);
        if (s.getRoomId() == id) {
            ShowTime::remove(s.getId());
        }
    }
}

Room Room::getById(const std::string& id) {
    auto lines = FileManager::readLines("../DB/rooms.dat");
    for(const auto& line : lines) {
        Room r = Room::fromString(line);
        if(r.getId() == id) {
            return r;
        }
    }
    throw std::runtime_error("Room not found");
}

std::vector<Room> Room::getAll() {
    std::vector<Room> rooms;
    auto lines = FileManager::readLines("../DB/rooms.dat");
    for(const auto& line : lines) {
        rooms.push_back(Room::fromString(line));
    }
    return rooms;
}

std::string Room::toString() const {
    return id + "," + std::to_string(capacity);
}

Room Room::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;
    while(std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }
    if(tokens.size() != 2) throw std::runtime_error("Invalid room string");
    return Room(tokens[0], std::stoi(tokens[1]));
}