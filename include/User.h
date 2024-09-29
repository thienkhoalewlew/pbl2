#pragma once
#include <string>
#include <vector>

enum class UserRole {
    Admin,
    Normal
};

class User {
protected:
    std::string id;
    std::string username;
    std::string password;
    UserRole role;

public:
    User(std::string id, std::string username, std::string password, UserRole role);
    virtual ~User() = default;

    std::string getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    UserRole getRole() const;

    virtual void displayMenu() = 0;
    virtual void executeOption(int option) = 0;

    static void save(const User& user);
    static void update(const User& user);
    static void remove(const std::string& id);
    static User* getById(const std::string& id);
    static User* getByUsername(const std::string& username);
    static std::vector<User*> getAll();

protected:
    virtual std::string toString() const;
    static User* fromString(const std::string& str);
};