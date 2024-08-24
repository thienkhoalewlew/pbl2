#pragma once
#include <string>
#include <vector>

enum class UserRole { Admin, Normal };

class User {
private:
    int id;
    std::string username;
    std::string password;
    UserRole role;

public:
    User(int id, std::string username, std::string password, UserRole role);

    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    UserRole getRole() const;

    static void save(const User& user);
    static void update(const User& user);
    static User getById(int id);
    static User getByUsername(const std::string& username);
    static std::vector<User> getAll();

    std::string toString() const;
    static User fromString(const std::string& str);
};