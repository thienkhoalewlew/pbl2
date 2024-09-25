#include "../include/LoginForm.h"
#include "../include/Customer.h"
#include "../include/Admin.h"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>

int main() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::string role = LoginForm::login(username, password);

    if (role == "Admin") {
        adminFunctionality();
        return 0;
    } else if (role == "Normal User") {
        customerFunctionality();

    } else {
        std::cout << "Login failed. Please try again." << std::endl;
    }

    return 0;
}


