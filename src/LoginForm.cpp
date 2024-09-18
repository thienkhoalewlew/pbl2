#include "../include/LoginForm.h"
#include "../include/User.h"
#include <iostream>

std::string LoginForm::login(const std::string& username, const std::string& password) {
    try {
        User user = User::getByUsername(username);
        if (user.getPassword() == password) {
            std::string role = (user.getRole() == UserRole::Admin) ? "Admin" : "Normal User";
            std::cout << "\033[32m";
            std::cout << "Login successful! Welcome, " << user.getUsername() << ". Your role: " << role << "." << std::endl;
            std::cout << "\033[0m";
            return role;
        } else {
            std::cout << "\033[31m";
            std::cout << "Invalid username or password." << std::endl;
            std::cout << "\033[0m";
            return 0;
        }
    } catch (const std::runtime_error& e) {
        std::cout << "\033[31m";
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "\033[0m";
        return 0;
    }
}
