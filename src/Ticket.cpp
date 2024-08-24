#include "../include/Ticket.h"
#include "../include/FileManager.h"
#include <sstream>
#include <stdexcept>

Ticket::Ticket(int id, int showtimeId, int seatId)
    : id(id), showTimeId(showtimeId), seatId(seatId) {}

int Ticket::getId() const { return id; }
int Ticket::getShowTimeId() const { return showTimeId; }
int Ticket::getSeatId() const { return seatId; }

void Ticket::save(const Ticket& ticket) {
    FileManager::appendLine("../DB/tickets.txt", ticket.toString());
}

void Ticket::update(const Ticket& ticket) {
    auto lines = FileManager::readLines("../DB/tickets.txt");
    for (auto& line : lines) {
        Ticket t = Ticket::fromString(line);
        if (t.getId() == ticket.getId()) {
            line = ticket.toString();
            break;
        }
    }
    FileManager::writeLines("../Db/tickets.txt", lines);
}

Ticket Ticket::getById(int id) {
    auto lines = FileManager::readLines("../DB/tickets.txt");
    for (const auto& line : lines) {
        Ticket t = Ticket::fromString(line);
        if (t.getId() == id) {
            return t;
        }
    }
    throw std::runtime_error("Ticket not found");
}

std::vector<Ticket> Ticket::getAll() {
    std::vector<Ticket> tickets;
    auto lines = FileManager::readLines("../DB/tickets.txt");
    for (const auto& line : lines) {
        tickets.push_back(Ticket::fromString(line));
    }
    return tickets;
}

std::string Ticket::toString() const {
    return std::to_string(id) + "," + std::to_string(showTimeId) + "," + std::to_string(seatId);
}

Ticket Ticket::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }
    if (tokens.size() != 3) throw std::runtime_error("Invalid ticket string");
    return Ticket(std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]));
}