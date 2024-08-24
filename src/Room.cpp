#include "../include/Room.h"
#include "../include/FileManager.h"
#include <sstream>
#include <stdexcept>

Room::Room(int id, int capacity) : id(id), capacity(capacity){}

int Room::getId() const { return id;}
int Room::getCapacity() const { return capacity;}

void Room::save(const Room& room){
    FileManager::appendLine("../DB/rooms.txt", room.toString());
}

void Room::update(const Room& room){
    auto lines = FileManager::readLines("../DB/rooms.txt");
    for(auto& line : lines){
        Room r = Room::fromString(line);
        if(r.getId() == room.getId()){
            line = room.toString();
            break;
        }   
    }
    FileManager::writeLines("../DB/rooms.txt", lines);
}

Room Room::getById(int id){
    auto lines = FileManager::readLines("../DB/rooms.txt");
    for(const auto& line : lines){
        Room r = Room::fromString(line);
        if(r.getId() ==id){
            return r;
        }
    }
    throw std::runtime_error("Room not found");
}

std::vector<Room> Room::getAll() {
    std::vector<Room> rooms;
    auto lines = FileManager::readLines("../DB/rooms.txt");
    for(const auto& line : lines){
        rooms.push_back(Room::fromString(line));
    }
    return rooms;
}

std::string Room::toString() const {
    return std::to_string(id) + "," + std::to_string(capacity);
}

Room Room::fromString(const std::string& str){
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;
    while(std::getline(iss, token, ',')){
        tokens.push_back(token);
    }
    if(tokens.size() != 2) throw std::runtime_error("Invalid room string");
    return Room(std::stoi(tokens[0]), std::stoi(tokens[1]));
}