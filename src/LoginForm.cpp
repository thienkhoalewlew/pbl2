#include "../include/LoginForm.h"
#include "../include/User.h"
#include <iostream>

std::string LoginForm::login(const std::string& username, const std::string& password) {
    try {
        User user = User::getByUsername(username);
        if (user.getPassword() == password) {
            std::string role = (user.getRole() == UserRole::Admin) ? "Admin" : "Normal User";
            std::cout << "Login successful! Welcome, " << user.getUsername() << ". Your role: " << role << "." << std::endl;
            return role;
        } else {
            std::cout << "Invalid username or password." << std::endl;
            return 0;
        }
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 0;
    }
}
