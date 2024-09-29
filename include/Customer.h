#pragma once
#include "User.h"

class Customer : public User {
public:
    Customer(std::string id, std::string username, std::string password);

    void displayMenu() override;
    void executeOption(int option) override;

private:
    void booking();
    void viewTicketInformation();
};