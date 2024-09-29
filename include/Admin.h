#pragma once
#include "User.h"

class Admin : public User {
public:
    Admin(std::string id, std::string username, std::string password);

    void displayMenu() override;
    void executeOption(int option) override;

private:
    void manageMovies();
    void manageRooms();
    void manageShowtimes();
    void manageTickets();
    void manageUsers();
    void revenue();
    void addNewMovie();
    void editMovie();
    void deleteMovie();
    void addNewRoom();
    void editRoom();
    void deleteRoom();
    void addNewShowtime();
    void editShowtime();
    void deleteShowtime();
    void addNewTicket();
    void editTicket();
    void deleteTicket();
    void addUser();
    void editUser();
    void deleteUser();
};