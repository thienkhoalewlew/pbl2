#include "../include/LoginForm.h"
#include "../include/User.h"
#include <iostream>

std::string LoginForm::login(const std::string& username, const std::string& password) {
    try {
        User* user = User::getByUsername(username);
        if (user && user->getPassword() == password) {
            return user->getRole() == UserRole::Admin ? "admin" : "normal";
        }
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "\033[0m";
        return 0;
    }
    return "invalid";
}
