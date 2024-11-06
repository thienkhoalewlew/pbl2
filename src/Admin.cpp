#include "../include/Admin.h"
#include "../include/Customer.h"
#include "../include/Movie.h"
#include "../include/ShowTime.h"
#include "../include/Room.h"
#include "../include/Ticket.h"
#include "../include/LoginForm.h"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <conio.h>  
#include <windows.h> 

static std::string getCurrentDate();

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

Admin::Admin(std::string id, std::string username, std::string password)
    : User(id, username, password, UserRole::Admin) {}

void Admin::displayMenu() {
    const int NUM_OPTIONS = 7;
    const std::string options[NUM_OPTIONS] = {
        "Manage Movies",
        "Manage Rooms",
        "Manage Showtimes",
        "Manage Tickets",
        "Manage Users",
        "Revenue",
        "Logout"
    };
    int selectedOption = 0;
    int key;

    while (true) {
        system("cls");
        std::cout << "\033[32mLogin successful! Admin Account, Welcome " << getUsername() << "!\033[0m\n";
        std::cout << "\033[33mAdmin Menu:\n\n\033[0m";
        for (int i = 0; i < NUM_OPTIONS; ++i) {
            if (i == selectedOption) {
                std::cout << "\033[44m> " << options[i] << "\033[0m\n";
            } else {
                std::cout << "  " << options[i] << "\n";
            }
        }

        key = _getch();
        switch (key) {
            case 72: // Up arrow
                selectedOption = (selectedOption - 1 + NUM_OPTIONS) % NUM_OPTIONS;
                break;
            case 80: // Down arrow
                selectedOption = (selectedOption + 1) % NUM_OPTIONS;
                break;
            case 13: // Enter
                executeOption(selectedOption);
                if (selectedOption == NUM_OPTIONS - 1) return; // Logout
                break;
        }
    }
}

void Admin::executeOption(int option) {
    switch (option) {
        case 0: manageMovies(); break;
        case 1: manageRooms(); break;
        case 2: manageShowtimes(); break;
        case 3: manageTickets(); break;
        case 4: manageUsers(); break;
        case 5: revenue(); break;
        case 6: return; // Logout
    }
}

void Admin::manageMovies() {
    std::vector<Movie> movies = Movie::getAll();
    std::cout << "\033[34m";
    std::cout << "All Movies:\n";
    std::cout << "ID | Name | Duration | Show Start Date | Show Stop Date\n";
    for (const auto& movie : movies) {
        std::cout << movie.getId() << " | " << movie.getName() << " | " << movie.getDuration() << " | " << movie.getShowStartDate() << " | " << movie.getShowStopDate() << "\n\n";
    }
    std::cout << "\033[0m";
    std::cout << "\033[33m";
    std::cout << "Choose an option:\n";
    std::cout << "1. Add New Movie\n";
    std::cout << "2. Edit Movie\n";
    std::cout << "3. Delete Movie\n";
    std::cout << "Enter your choice: ";
    std::cout << "\033[0m";
    int choice;
    std::cin >> choice;
    while (choice > 3 || choice < 1) {
        std::cout << "\033[31m";
        std::cout << "Invalid choice. Please try again!\n";
        std::cout << "\033[33m";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << "\033[0m";
    }
    switch (choice) {
        case 1: addNewMovie(); break;
        case 2: editMovie(); break;
        case 3: deleteMovie(); break;
    }
}

void Admin::manageRooms() {
    std::vector<Room> rooms = Room::getAll();
    std::cout << "\033[34m";
    std::cout << "All Rooms:\n";
    std::cout << "ID | Capacity \n";
    for (const auto& room : rooms) {
        std::cout << room.getId() <<  " | " << room.getCapacity() << "\n";
    }
    std::cout << "\033[0m";
    std::cout << "\033[33m";
    std::cout << "Choose an option:\n";
    std::cout << "1. Add New Room\n";
    std::cout << "2. Edit Room\n";
    std::cout << "3. Delete Room\n";
    std::cout << "Enter your choice: ";
    std::cout << "\033[0m";
    int choice;
    std::cin >> choice;
    while (choice > 3 || choice < 1) {
        std::cout << "\033[31m";
        std::cout << "Invalid choice. Please try again!\n";
        std::cout << "\033[33m";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << "\033[0m";
    }
    switch (choice) {
        case 1: addNewRoom(); break;
        case 2: editRoom(); break;
        case 3: deleteRoom(); break;
    }
    
}

void Admin::manageShowtimes() {
    std::vector<ShowTime> showtimes = ShowTime::getAll();
    std::cout << "\033[34m";
    std::cout << "All Showtimes:\n";
    std::cout << "ID | Movie ID | Room ID | Show Date | Show Time\n";
    for (const auto& showtime : showtimes) {
        std::cout << showtime.getId() << " | " << showtime.getMovieId() << " | " << showtime.getRoomId() << " | " << showtime.getShowDate() << " | " << showtime.getShowTime() << "\n\n";
    }
    std::cout << "\033[0m";
    std::cout << "\033[33m";
    std::cout << "Choose an option:\n";
    std::cout << "1. Add New Showtime\n";
    std::cout << "2. Edit Showtime\n";
    std::cout << "3. Delete Showtime\n";
    std::cout << "Enter your choice: ";
    std::cout << "\033[0m";
    int choice;
    std::cin >> choice;
    while (choice > 3 || choice < 1) {
        std::cout << "\033[31m";
        std::cout << "Invalid choice. Please try again!\n";
        std::cout << "\033[33m";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << "\033[0m";
    }
    switch (choice) {
        case 1: addNewShowtime(); break;
        case 2: editShowtime(); break;
        case 3: deleteShowtime(); break;
    }
}

void Admin::manageTickets() {
    std::vector<Ticket> tickets = Ticket::getAll();
    std::cout << "\033[34m";
    std::cout << "All Tickets:\n";
    std::cout << "ID | Showtime ID | Seat Numbers \n";
    for (const auto& ticket : tickets) {
        std::cout << ticket.getId() << " | " << ticket.getShowTimeId() << " | ";
        const auto& seatIds = ticket.getSeatIds();
        for (size_t i = 0; i < seatIds.size(); ++i) {
            std::cout << seatIds[i];
            if (i < seatIds.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n\n";
    }
    std::cout << "\033[0m";
    std::cout << "\033[33m";
    std::cout << "Choose an option:\n";
    std::cout << "1. Edit Ticket\n";
    std::cout << "2. Delete Ticket\n";
    std::cout << "Enter your choice: ";
    std::cout << "\033[0m";
    int choice;
    std::cin >> choice;
    while (choice > 2 || choice < 1) {
        std::cout << "\033[31m";
        std::cout << "Invalid choice. Please try again!\n";
        std::cout << "\033[33m";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << "\033[0m";
    }
    switch (choice) {
        case 1: editTicket(); break;
        case 2: deleteTicket(); break;
    }
}

void Admin::editTicket() {
    std::cout << "\033[33m";
    std::cout << "Enter ticket ID to edit: ";
    std::cout << "\033[0m";
    std::string id;
    std::cin >> id;
    Ticket ticketToEdit = Ticket::getById(id);

    std::cout << "\033[33m";
    std::cout << "Current showtime ID: " << ticketToEdit.getShowTimeId() << "\n";
    std::cout << "Enter new showtime ID (or press Enter to keep current): ";
    std::cout << "\033[0m";
    std::string showtimeId;
    std::cin.ignore();
    std::getline(std::cin, showtimeId);
    if (showtimeId.empty()) {
        showtimeId = ticketToEdit.getShowTimeId();
    }

    std::cout << "\033[33m";
    std::cout << "Current seat IDs: ";
    const auto& currentSeatIds = ticketToEdit.getSeatIds();
    for (size_t i = 0; i < currentSeatIds.size(); ++i) {
        std::cout << currentSeatIds[i];
        if (i < currentSeatIds.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
    std::cout << "Enter new seat IDs (comma-separated, or press Enter to keep current): ";
    std::cout << "\033[0m";
    std::string seatIdsInput;
    std::getline(std::cin, seatIdsInput);
    std::vector<std::string> seatIds;
    if (!seatIdsInput.empty()) {
        std::istringstream iss(seatIdsInput);
        std::string seatId;
        while (std::getline(iss, seatId, ',')) {
            seatIds.push_back(seatId);
        }
    } else {
        seatIds = currentSeatIds;
    }

    Ticket updatedTicket(id, showtimeId, seatIds, ticketToEdit.getPrice());
    Ticket::update(updatedTicket);
    std::cout << "\033[32m";
    std::cout << "Ticket updated successfully!\n";
    std::cout << "\033[0m";
    std::cin.ignore();
}

void Admin::deleteTicket() {
    std::vector<Ticket> tickets = Ticket::getAll();
    std::vector<std::string> availableTickets;
    system("cls");
    std::string id;

    for (const auto& ticket : tickets) {
        availableTickets.push_back(ticket.getId());
    }

    if (availableTickets.empty()) {
        std::cout << "\033[31m";
        std::cout << "No tickets available for deleting.\n";
        std::cout << "\033[0m";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    int selectedOption = 0;
    int key;
    while (true) {
        system("cls"); 

        std::cout << "\033[33mTickets are available:\n\n\033[0m";

        for (int i = 0; i < availableTickets.size(); ++i) {
            if (i == selectedOption) {
                std::cout << "\033[44m> " << availableTickets[i] << "\033[0m\n";
            } else {
                std::cout << "  " << availableTickets[i] << "\n";
            }
        }
    
        key = _getch();
        int check = 0;

        switch (key) {
            case 72:  
                selectedOption = (selectedOption - 1 + availableTickets.size()) % availableTickets.size();
                break;
            case 80: 
                selectedOption = (selectedOption + 1) % availableTickets.size();
                break;
            case 13: 
                id = availableTickets[selectedOption];
                check = 1;
                break;
        }
        if (check) break;
    }
    std::cout << "\033[0m";


    Ticket::remove(id);
    std::cout << "\033[32m";
    std::cout << "Ticket deleted successfully!\n";
    std::cout << "\033[0m";
    std::cin.ignore();
    std::cin.get();

}

void Admin::manageUsers() {
    std::vector<User*> users = User::getAll();
    std::cout << "\033[34m";
    std::cout << "All Users:\n";
    std::cout << "ID | Username | Password | Role\n";
    for (const auto& user : users) {
        std::cout << user->getId() << " | " << user->getUsername() << " | " 
                  << std::string(user->getPassword().length(), '*') << " | ";
        
        if (user->getRole() == UserRole::Admin) {
            std::cout << "Admin";
        } else if (user->getRole() == UserRole::Normal) {
            std::cout << "Normal User";
        }
        
        std::cout << "\n\n";
    }
    std::cout << "\033[0m";
    std::cout << "\033[33m";
    std::cout << "Choose an option:\n";
    std::cout << "1. Add User\n";
    std::cout << "2. Edit User\n";
    std::cout << "3. Delete User\n";
    std::cout << "Enter your choice: ";
    std::cout << "\033[0m";
    int choice;
    std::cin >> choice;
    while (choice > 3 || choice < 1) {
        std::cout << "\033[31m";
        std::cout << "Invalid choice. Please try again!\n";
        std::cout << "\033[33m";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << "\033[0m";
    }
    switch (choice) {
        case 1: addUser(); break;
        case 2: editUser(); break;
        case 3: deleteUser(); break;
    }

    // Clean up allocated memory
    for (auto user : users) {
        delete user;
    }
}

void Admin::addUser() {
    std::string id, username, password, role;
    std::cout << "\033[33m";
    std::cout << "Enter new ID: ";
    std::cout << "\033[0m";
    std::cin >> id;
    std::cout << "\033[33m";
    std::cout << "Enter new username: ";
    std::cout << "\033[0m";
    std::cin >> username;
    std::cout << "\033[33m";
    std::cout << "Enter new password: ";
    std::cout << "\033[0m";
    std::cin >> password;
    std::cout << "\033[33m";
    std::cout << "Enter role (admin/normal): ";
    std::cout << "\033[0m";
    std::cin >> role;

    User* newUser = nullptr;
    try {
        if (role == "admin") {
            newUser = new Admin(id, username, password);
        } else if (role == "normal") {
            newUser = new Customer(id, username, password);
        } else {
            std::cout << "\033[31m";
            std::cerr << "Invalid role. Defaulting to Normal.\n";
            std::cout << "\033[0m";
            newUser = new Customer(id, username, password);
        }

        User::save(*newUser);
        std::cout << "\033[32m";
        std::cout << "User added successfully!\n";
        std::cout << "\033[0m";
        std::cin.ignore();
        std::cin.get();
        
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error adding user: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }

    if (newUser != nullptr) {
        delete newUser;
    }
}

void Admin::editUser() {
    std::cout << "\033[33m";
    std::cout << "Enter user ID to edit: ";
    std::cout << "\033[0m";
    std::string id;
    std::cin >> id;
    User* userToEdit = User::getById(id);

    std::string username, password, role;
    std::cout << "\033[33m";
    std::cout << "Current username: " << userToEdit->getUsername() << std::endl;
    std::cout << "Enter new username (press Enter to keep current): ";
    std::cout << "\033[0m";
    std::cin.ignore();
    std::getline(std::cin, username);
    if (username.empty()) username = userToEdit->getUsername();

    std::cout << "\033[33m";
    std::cout << "Enter new password (press Enter to keep current): ";
    std::cout << "\033[0m";
    std::getline(std::cin, password);
    if (password.empty()) password = userToEdit->getPassword();

    std::cout << "\033[33m";
    std::cout << "Current role: " << (userToEdit->getRole() == UserRole::Admin ? "Admin" : "Normal User") << std::endl;
    std::cout << "Enter new role (Admin/Normal, press Enter to keep current): ";
    std::cout << "\033[0m";
    std::getline(std::cin, role);
    UserRole newRole = userToEdit->getRole();
    if (!role.empty()) {
        if (role == "Admin") newRole = UserRole::Admin;
        else if (role == "Normal") newRole = UserRole::Normal;
        else {
            std::cout << "\033[31m";
            std::cout << "Invalid role. Keeping current role.\n";
            std::cout << "\033[0m";
        }
    }

    User* updatedUser;
    if (newRole == UserRole::Admin) {
        updatedUser = new Admin(id, username, password);
    } else {
        updatedUser = new Customer(id, username, password);
    }

    User::update(*updatedUser);
    std::cout << "\033[32m";
    std::cout << "User updated successfully!\n";
    std::cout << "\033[0m";

    // Clean up
    delete userToEdit;
    delete updatedUser;

    std::cin.ignore();
    std::cin.get();
}

void Admin::deleteUser() {
    std::vector<User*> users = User::getAll();
    std::vector<std::string> availableUsers;
    system("cls");
    std::string id;

    for (const auto& user : users) {
        availableUsers.push_back(user->getId());
    }

    if (availableUsers.empty()) {
        std::cout << "\033[31m";
        std::cout << "No users available for deleting.\n";
        std::cout << "\033[0m";
        std::cin.ignore();
        std::cin.get();
        // Clean up
        for (auto user : users) {
            delete user;
        }
        return;
    }

    int selectedOption = 0;
    int key;
    while (true) {
        system("cls"); 

        std::cout << "\033[33mUsers are available:\n\n\033[0m";

        for (int i = 0; i < availableUsers.size(); ++i) {
            if (i == selectedOption) {
                std::cout << "\033[44m> " << availableUsers[i] << "\033[0m\n";
            } else {
                std::cout << "  " << availableUsers[i] << "\n";
            }
        }
    
        key = _getch();
        int check = 0;

        switch (key) {
            case 72:  
                selectedOption = (selectedOption - 1 + availableUsers.size()) % availableUsers.size();
                break;
            case 80: 
                selectedOption = (selectedOption + 1) % availableUsers.size();
                break;
            case 13: 
                id = availableUsers[selectedOption];
                check = 1;
                break;
        }
        if (check) break;
    }
    std::cout << "\033[0m";

    User::remove(id);
    std::cout << "\033[32m";
    std::cout << "User deleted successfully!\n";
    std::cout << "\033[0m";

    // Clean up
    for (auto user : users) {
        delete user;
    }

    std::cin.ignore();
    std::cin.get();
}

void Admin::revenue() {
    std::vector<Movie> movies = Movie::getAll();
    std::cout << "\033[34m";
    std::cout << "Revenue by Movie:\n";
    std::cout << "ID | Name | Total Revenue\n";
    
    for (const auto& movie : movies) {
        double totalRevenue = 0.0;
        std::vector<ShowTime> showTimes = ShowTime::getByMovieId(movie.getId());
        
        for (const auto& showTime : showTimes) {
            std::vector<Ticket> tickets = Ticket::getByShowTimeId(showTime.getId());
            
            for (const auto& ticket : tickets) {
                totalRevenue += ticket.getPrice();
            }
        }
        
        std::cout << movie.getId() << " | " << movie.getName() << " | " << std::fixed << std::setprecision(0) << "\033[31m"<< totalRevenue << "\033[34m"<< " VND\n";
    }
    std::cout << "\033[0m";
    std::cin.ignore();
    std::cin.get();
    
}

void Admin::addNewMovie() {
    std::string currentDate = getCurrentDate();
    std::vector<Movie> movies = Movie::getAll();
    std::string name, duration, showStartDate, showStopDate;
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter movie id: ";
    std::cout << "\033[0m";
    std::cin >> id;

    for (const auto& movie : movies) {
        if (id == movie.getId()) {
            std::cout << "\033[31m";
            std::cout << "Movie already exists!";
            std::cin.ignore();
            std::cin.get();
            std::cout << "\033[0m";
            return;
        }
    }
    std::cout << "\033[33m";
    std::cout << "Enter movie name: ";
    std::cout << "\033[0m";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "\033[33m";
    std::cout << "Enter movie duration (in minutes): ";
    std::cout << "\033[0m";
    std::cin >> duration;

    std::cout << "\033[33m";
    std::cout << "Enter movie show start date (YYYY-MM-DD): ";
    std::cout << "\033[0m";
    std::cin >> showStartDate;

    bool validDate = false;
    while (!validDate) {
        std::cout << "\033[33m";
        std::cout << "Enter movie show stop day (YYYY-MM-DD): ";
        std::cout << "\033[0m";
        std::cin >> showStopDate;
        if (showStopDate < currentDate) {
            std::cout << "\033[31m";
            std::cout << "Error: The entered date is not valid. Please enter again!.\n";
            std::cout << "\033[0m";
        } else {
            validDate = true;
        }
    }

    Movie newMovie(id, name, duration, showStartDate, showStopDate);
    Movie::save(newMovie);
    std::cout << "\033[32m";
    std::cout << "Movie added successfully!\n";
    std::cout << "\033[0m";
    std::cin.ignore();
    std::cin.get();
}

void Admin::editMovie() {
    std::string currentDate = getCurrentDate();
    std::vector<Movie> movies = Movie::getAll();
    std::vector<std::string> availableMovies;
    std::cout << "\033[33m";
    std::cout << "Enter movie ID to edit: ";
    std::cout << "\033[0m";
    std::string movieId;
    std::cin >> movieId;
    Movie movieToEdit = Movie::getbyId(movieId);

    std::string name, duration, showStartDate, showStopDate;
    std::cout << "\033[33m";
    std::cout << "Current movie name: " << movieToEdit.getName() << std::endl;
    std::cout << "Enter new movie name (press Enter to keep current): ";
    std::cout << "\033[0m";
    std::cin.ignore();
    std::getline(std::cin, name);
    if (name.empty()) name = movieToEdit.getName();

    std::cout << "\033[33m";
    std::cout << "Current movie duration: " << movieToEdit.getDuration() << " minutes" << std::endl;
    std::cout << "Enter new movie duration in minutes (press Enter to keep current): ";
    std::cout << "\033[0m";
    std::string durationInput;
    std::getline(std::cin, durationInput);
    duration = durationInput.empty() ? movieToEdit.getDuration() : durationInput;

    std::cout << "\033[33m";
    std::cout << "Current movie show start date: " << movieToEdit.getShowStartDate() << std::endl;
    std::cout << "Enter new movie show start date (YYYY-MM-DD) (press Enter to keep current): ";
    std::cout << "\033[0m";
    std::getline(std::cin, showStartDate);
    if (showStartDate.empty()) showStartDate = movieToEdit.getShowStartDate();

    std::cout << "\033[33m";
    std::cout << "Current movie show stop date: " << movieToEdit.getShowStopDate() << std::endl;

    bool validDate = false;
    while (!validDate) {
        std::cout << "Enter new movie show stop date (YYYY-MM-DD) (press Enter to keep current): ";
        std::cout << "\033[0m";
        std::getline(std::cin, showStartDate);
        if (showStopDate < currentDate && !showStopDate.empty()) {
            std::cout << "\033[31m";
            std::cout << "Error: The entered date is not valid. Please enter again!.\n";
            std::cout << "\033[0m";
        } else {
            validDate = true;
        }
    }
    if (showStopDate.empty()) showStopDate = movieToEdit.getShowStopDate();

    Movie updatedMovie(movieId, name, duration, showStartDate, showStopDate);
    Movie::update(updatedMovie);
    std::cout << "\033[32m";
    std::cout << "Movie updated successfully!\n";
    std::cout << "\033[0m";
    std::cin.ignore();
    std::cin.get();
}

void Admin::deleteMovie() {
    std::vector<Movie> movies = Movie::getAll();
    std::vector<std::string> availableMovies;
    system("cls");
    std::string movieId;

    for (const auto& movie : movies) {
        availableMovies.push_back(movie.getName());
    }
    if (availableMovies.empty()) {
        std::cout << "\033[31m";
        std::cout << "No movies available for deleting.\n";
        std::cout << "\033[0m";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    int selectedOption = 0;
    int key;
    while (true) {
        system("cls"); 

        std::cout << "\033[33mMovies are available:\n\n\033[0m";

        for (int i = 0; i < availableMovies.size(); ++i) {
            if (i == selectedOption) {
                std::cout << "\033[44m> " << availableMovies[i] << "\033[0m\n";
            } else {
                std::cout << "  " << availableMovies[i] << "\n";
            }
        }
    
        key = _getch();
        int check = 0;

        switch (key) {
            case 72:  
                selectedOption = (selectedOption - 1 + availableMovies.size()) % availableMovies.size();
                break;
            case 80: 
                selectedOption = (selectedOption + 1) % availableMovies.size();
                break;
            case 13: 
                for (const auto& movie : movies) {
                    if (movie.getName() == availableMovies[selectedOption]) {
                        movieId = movie.getId();
                        check = 1;
                        break;
                    }
                } 
                break;
        }
        if (check) break;
    }
    std::cout << "\033[0m";

    Movie::remove(movieId);
    system("cls");
    std::cout << "\033[32m";
    std::cout << "Movie deleted successfully!\n";
    std::cout << "\033[0m";
    std::cin.ignore();
    std::cin.get();
}

void Admin::addNewRoom() {
    std::vector<Room> rooms = Room::getAll();
    std::string id;
    int capacity;
    std::cout << "\033[33m";
    std::cout << "Enter room id: ";
    std::cout << "\033[0m";
    std::cin >> id;
    
    for (const auto& room : rooms) {
        if (id == room.getId()) {
            std::cout << "\033[31m";
            std::cout << "Room already exists!";
            std::cin.ignore();
            std::cin.get();
            std::cout << "\033[0m";
            return;
        }
    }
    
    std::cout << "\033[33m";
    std::cout << "Enter room capacity: ";
    std::cout << "\033[0m";
    std::cin >> capacity;

    Room newRoom(id, capacity);
    Room::save(newRoom);    
    std::cout << "\033[32m";
    std::cout << "Room added successfully!\n";
    std::cout << "\033[0m";
    std::cin.ignore();
    std::cin.get();
}

void Admin::editRoom() {
    std::cout << "\033[33m";
    std::cout << "Enter room ID to edit: ";
    std::cout << "\033[0m";
    std::string roomId;
    std::cin >> roomId;
    Room roomToEdit = Room::getById(roomId);

    int capacity;
    std::cout << "\033[33m";
    std::cout << "Current room capacity: " << roomToEdit.getCapacity() << std::endl;
    std::cout << "Enter new room capacity (or 0 to keep current): ";
    std::cout << "\033[0m";
    std::cin >> capacity;
    
    if (capacity == 0) {
        capacity = roomToEdit.getCapacity();
    }

    Room updatedRoom(roomId, capacity);
    Room::update(updatedRoom);
    std::cout << "\033[32m";
    std::cout << "Room updated successfully!\n";
    std::cout << "\033[0m";
    std::cin.ignore();
    std::cin.get();
}

void Admin::deleteRoom() {
    std::vector<Room> rooms = Room::getAll();
    std::vector<std::string> availableRooms;
    system("cls");
    std::string roomId;

    for (const auto& room : rooms) {
        availableRooms.push_back(room.getId());
    }
    if (availableRooms.empty()) {
        std::cout << "\033[31m";
        std::cout << "No movies available for editing.\n";
        std::cin.ignore();
        std::cin.get();
        std::cout << "\033[0m";
        return;
    }
    int selectedOption = 0;
    int key;
    while (true) {
        system("cls"); 

        std::cout << "\033[33mRooms are available:\n\n\033[0m";

        for (int i = 0; i < availableRooms.size(); ++i) {
            if (i == selectedOption) {
                std::cout << "\033[44m> " << availableRooms[i] << "\033[0m\n";
            } else {
                std::cout << "  " << availableRooms[i] << "\n";
            }
        }
    
        key = _getch();
        int check = 0;

        switch (key) {
            case 72:  
                selectedOption = (selectedOption - 1 + availableRooms.size()) % availableRooms.size();
                break;
            case 80: 
                selectedOption = (selectedOption + 1) % availableRooms.size();
                break;
            case 13: 
                roomId = availableRooms[selectedOption];
                check = 1;
                break;
                break;
        }
        if (check) break; 
    }
    std::cout << "\033[0m";

    Room::remove(roomId);
    std::cout << "\033[32m";
    std::cout << "Room deleted successfully!\n";
    std::cout << "\033[0m";
    std::cin.ignore();
    std::cin.get();
}

static std::string getCurrentDate() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

void Admin::addNewShowtime() {
    std::string currentDate = getCurrentDate();
    std::vector<Movie> movies = Movie::getAll();
    std::vector<ShowTime> showtimes = ShowTime::getAll();
    std::vector<Room> rooms = Room::getAll();
    std::vector<std::string> availableMovies;
    std::vector<std::string> availableRooms;

    std::string id, movieId, roomId, showTime, showDate;
    std::cout << "\033[33m";
    std::cout << "Enter showtime ID: ";
    std::cout << "\033[0m";
    std::cin >> id;
    for (const auto& showtime : showtimes) {
        if (id == showtime.getId()) {
            std::cout << "\033[31m";
            std::cout << "Showtime already exists!";
            std::cin.ignore();
            std::cin.get();
            std::cout << "\033[0m";
            return;
        }
    }
    
    for (const auto& movie : movies) {
        if (currentDate >= movie.getShowStartDate() && currentDate <= movie.getShowStopDate()) {
            availableMovies.push_back(movie.getName());
        }
    }
    if (availableMovies.empty()) {
        std::cout << "\033[31m";
        std::cout << "No movies available for creating showtimes.\n";
        std::cin.ignore();
        std::cin.get();
        std::cout << "\033[0m";
        return;
    }
    int selectedOption = 0;
    int key;
    while (true) {
        system("cls"); 

        std::cout << "\033[33mMovies are available:\n\n\033[0m";

        for (int i = 0; i < availableMovies.size(); ++i) {
            if (i == selectedOption) {
                std::cout << "\033[44m> " << availableMovies[i] << "\033[0m\n";
            } else {
                std::cout << "  " << availableMovies[i] << "\n";
            }
        }
    
        key = _getch();
        int check = 0;

        switch (key) {
            case 72:  
                selectedOption = (selectedOption - 1 + availableMovies.size()) % availableMovies.size();
                break;
            case 80: 
                selectedOption = (selectedOption + 1) % availableMovies.size();
                break;
            case 13: 
                for (const auto& movie : movies) {
                    if (movie.getName() == availableMovies[selectedOption]) {
                        movieId = movie.getId();
                        check = 1;
                        break;
                    }
                } 
                break;
        }
        if (check) break;
    }
    std::cout << "\033[0m";

    for (const auto& room : rooms) {
            availableRooms.push_back(room.getId());
    }
    if (availableRooms.empty()) {
        std::cout << "\033[31m";
        std::cout << "No rooms available for creating showtimes.\n";
        std::cin.ignore();
        std::cin.get();
        std::cout << "\033[0m";
        return;
    }
    int selectedOption2 = 0;
    int key2;
    while (true) {
        system("cls"); 

        std::cout << "\033[33mRooms are available:\n\n\033[0m";

        for (int i = 0; i < availableRooms.size(); ++i) {
            if (i == selectedOption2) {
                std::cout << "\033[44m> " << availableRooms[i] << "\033[0m\n";
            } else {
                std::cout << "  " << availableRooms[i] << "\n";
            }
        }

        key2 = _getch();
        int check2 = 0;

        switch (key2) {
            case 72:  
                selectedOption2 = (selectedOption2 - 1 + availableRooms.size()) % availableRooms.size();
                break;
            case 80: 
                selectedOption2 = (selectedOption2 + 1) % availableRooms.size();
                break;
            case 13: 
                roomId = availableRooms[selectedOption2];
                check2 = 1;
                break;
        }
    if (check2) break;
    }
    std::cout << "\033[0m";
    system("cls");
        
    std::cout << "\033[33m";
    std::cout << "Enter show time (HH:MM): ";
    std::cout << "\033[0m";
    std::cin >> showTime;
    bool validDate = false;
    while (!validDate) {
        std::cout << "\033[33m";
        std::cout << "Enter show date (YYYY-MM-DD): ";
        std::cout << "\033[0m";
        std::cin >> showDate;
        Movie m = Movie::getbyId(movieId);
        if (showDate < currentDate || showDate > m.getShowStopDate()) {
            std::cout << "\033[31m";
            std::cout << "Error: The entered date is not valid. Please enter again!.\n";
            std::cout << "\033[0m";
        } else {
            validDate = true;
        }
    }

    ShowTime newShowtime(id, movieId, roomId, showTime, showDate);
    ShowTime::save(newShowtime);
    std::cout << "\033[32m";
    std::cout << "Showtime added successfully!\n";
    std::cin.ignore();
    std::cin.get();
    std::cout << "\033[0m";
}

void Admin::editShowtime() {
    std::string currentDate = getCurrentDate();
    std::vector<Movie> movies = Movie::getAll();
    std::vector<ShowTime> showtimes = ShowTime::getAll();
    std::vector<Room> rooms = Room::getAll();
    std::string id, movieId, roomId, showTime, showDate;

    std::cout << "\033[33mEnter showtime ID to edit: ";
    std::cout << "\033[0m";
    std::cin >> id;
    ShowTime showtimeToEdit = ShowTime::getById(id);
    std::cout << "\033[33mCurrent movie ID: " << showtimeToEdit.getMovieId() << std::endl;
    std::cout << "\033[33mEnter new movie ID (or press Enter to keep current): ";
    std::cout << "\033[0m";
    std::cin.ignore();
    std::getline(std::cin, movieId);
    if (movieId.empty()) movieId = showtimeToEdit.getMovieId();

    std::cout << "\033[33mCurrent room ID: " << showtimeToEdit.getRoomId() << std::endl;
    std::cout << "\033[33mEnter new room ID (or press Enter to keep current): ";
    std::cout << "\033[0m";
    std::getline(std::cin, roomId);
    if (roomId.empty()) roomId = showtimeToEdit.getRoomId();

    std::cout << "\033[33mCurrent show time: " << showtimeToEdit.getShowTime() << std::endl;
    std::cout << "Enter new show time (HH:MM) (press Enter to keep current): ";
    std::cout << "\033[0m";
    std::getline(std::cin, showTime);
    if (showTime.empty()) showTime = showtimeToEdit.getShowTime();

    bool validDate = false;
    while (!validDate) {
        std::cout << "\033[33m";
        std::cout << "Current show date: " << showtimeToEdit.getShowDate() << std::endl;
        std::cout << "Enter new show date (YYYY-MM-DD) (press Enter to keep current): ";
        std::cout << "\033[0m";
        std::getline(std::cin, showDate);
        Movie m = Movie::getbyId(movieId);
        if ((showDate < currentDate || showDate > m.getShowStopDate()) && (!showDate.empty())) {
            std::cout << "\033[31m";
            std::cout << "Error: The entered date is not valid. Please enter again!.\n";
            std::cout << "\033[0m";
        } else {
            validDate = true;
        }
    }
    if (showDate.empty()) showDate = showtimeToEdit.getShowDate();

    ShowTime updatedShowtime(id, movieId, roomId, showTime, showDate);
    ShowTime::update(updatedShowtime);
    std::cout << "\033[32m";
    std::cout << "Showtime updated successfully!\n";
    std::cin.ignore();
    std::cin.get();
    std::cout << "\033[0m";
}

void Admin::deleteShowtime() {
    std::vector<ShowTime> showtimes = ShowTime::getAll();
    std::string id;

    if (showtimes.empty()) {
        std::cout << "\033[31m";
        std::cout << "No showtimes available for deleting.\n";
        std::cout << "\033[0m";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::cout << "\033[33mAll Showtimes:\n\033[0m";
    for (const auto& showtime : showtimes) {
        std::cout << showtime.getId() << "\n";
    }

    std::cout << "\033[33mEnter the ID of the showtime to delete: \033[0m";
    std::cin >> id;

    std::cout << "\033[33mAre you sure you want to delete showtime " << id << "? (y/n): \033[0m";
    char confirmation;
    std::cin >> confirmation;

    if (confirmation == 'y' || confirmation == 'Y') {
        ShowTime::remove(id);
        std::cout << "\033[32mShowtime deleted successfully!\n\033[0m";
    } else {
        std::cout << "\033[31mDeletion cancelled.\n\033[0m";
    }

    std::cin.ignore();
    std::cin.get();
}