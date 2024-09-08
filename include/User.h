#pragma once
#include <string>
#include <vector>

enum class UserRole { Admin, Normal };

class User {
private:
    std::string id; 
    std::string username;
    std::string password;
    UserRole role;

public:
    User(std::string id, std::string username, std::string password, UserRole role);  

    std::string getId() const;  
    std::string getUsername() const;
    std::string getPassword() const;
    UserRole getRole() const;

    static void save(const User& user);
    static void update(const User& user);
    static void remove(const std::string& id);
    static User getById(const std::string& id);  
    static User getByUsername(const std::string& username);
    static std::vector<User> getAll();

    std::string toString() const;
    static User fromString(const std::string& str);
};