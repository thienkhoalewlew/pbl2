#include "../include/Ticket.h"
#include "../include/FileManager.h"
#include <sstream>
#include <stdexcept>

Ticket::Ticket(const std::string& id, const std::string& showTimeId, const std::vector<std::string>& seatIds, double price)
    : id(id), showTimeId(showTimeId), seatIds(seatIds), price(price) {}

std::string Ticket::getId() const { return id; }
std::string Ticket::getShowTimeId() const { return showTimeId; }
std::vector<std::string> Ticket::getSeatIds() const { return seatIds; }
double Ticket::getPrice() const { return price; }

void Ticket::save(const Ticket& ticket) {
    FileManager::appendLine("../DB/tickets.dat", ticket.toString());
}

void Ticket::update(const Ticket& ticket) {
    auto lines = FileManager::readLines("../DB/tickets.dat");
    for (auto& line : lines) {
        Ticket t = Ticket::fromString(line);
        if (t.getId() == ticket.getId()) {
            line = ticket.toString();
            break;
        }
    }
    FileManager::writeLines("../DB/tickets.dat", lines);
}

void Ticket::remove(const std::string& id) {
    auto lines = FileManager::readLines("../DB/tickets.dat");
    auto newLines = std::vector<std::string>();
    for (const auto& line : lines) {
        Ticket t = Ticket::fromString(line);
        if (t.getId() != id) {
            newLines.push_back(line);
        }
    }
    FileManager::writeLines("../DB/tickets.dat", newLines);
}

Ticket Ticket::getById(const std::string& id) {
    auto lines = FileManager::readLines("../DB/tickets.dat");
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
    auto lines = FileManager::readLines("../DB/tickets.dat");
    for (const auto& line : lines) {
        tickets.push_back(Ticket::fromString(line));
    }
    return tickets;
}

std::string Ticket::toString() const {
    std::ostringstream oss;
    oss << id << "," << showTimeId << "," << price;
    for (const auto& seatId : seatIds) {
        oss << "," << seatId;
    }
    return oss.str();
}

Ticket Ticket::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }
    if (tokens.size() < 4) throw std::runtime_error("Invalid ticket string");
    
    double price = std::stod(tokens[2]);
    std::vector<std::string> seatIds(tokens.begin() + 3, tokens.end());
    return Ticket(tokens[0], tokens[1], seatIds, price);
}
