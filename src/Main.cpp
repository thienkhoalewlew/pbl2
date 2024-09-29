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

    if (role == "admin") {
        Admin* admin = dynamic_cast<Admin*>(User::getByUsername(username));
        if (admin) {
            admin->displayMenu();
        }
    } else if (role == "normal") {
        Customer* customer = dynamic_cast<Customer*>(User::getByUsername(username));
        if (customer) {
            customer->displayMenu();
        }
    } else {
        std::cout << "Invalid login credentials." << std::endl;
    }

    return 0;
}


