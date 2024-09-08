#include "../include/User.h"
#include "../include/FileManager.h"
#include <sstream>
#include <stdexcept>

User::User(std::string id, std::string username, std::string password, UserRole role)
    : id(id), username(username), password(password), role(role) {}

std::string User::getId() const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
UserRole User::getRole() const { return role; }

void User::save(const User& user) {
    FileManager::appendLine("../DB/users.dat", user.toString());
}

void User::update(const User& user) {
    auto lines = FileManager::readLines("../DB/users.dat");
    for (auto& line : lines) {
        User u = User::fromString(line);
        if (u.getId() == user.getId()) {
            line = user.toString();
            break;
        }
    }
    FileManager::writeLines("../DB/users.dat", lines);
}

void User::remove(const std::string& id) {
    auto lines = FileManager::readLines("../DB/users.dat");
    auto newLines = std::vector<std::string>();
    for (const auto& line : lines) {
        User u = User::fromString(line);
        if (u.getId() != id) {
            newLines.push_back(line);
        }
    }
    FileManager::writeLines("../DB/users.dat", newLines);
}

User User::getById(const std::string& id) {
    auto lines = FileManager::readLines("../DB/users.dat");
    for (const auto& line : lines) {
        User u = User::fromString(line);
        if (u.getId() == id) {
            return u;
        }
    }
    throw std::runtime_error("User not found");
}

User User::getByUsername(const std::string& username) {
    auto lines = FileManager::readLines("../DB/users.dat");
    for (const auto& line : lines) {
        User u = User::fromString(line);
        if (u.getUsername() == username) {
            return u;
        }
    }
    throw std::runtime_error("User not found");
}

std::vector<User> User::getAll() {
    std::vector<User> users;
    auto lines = FileManager::readLines("../DB/users.dat");
    for (const auto& line : lines) {
        users.push_back(User::fromString(line));
    }
    return users;
}

std::string User::toString() const {
    return id + "," + username + "," + password + "," + (role == UserRole::Admin ? "admin" : "normal");
}

User User::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }
    if (tokens.size() != 4) throw std::runtime_error("Invalid user string");
    UserRole role = tokens[3] == "admin" ? UserRole::Admin : UserRole::Normal;
    return User(tokens[0], tokens[1], tokens[2], role);
}