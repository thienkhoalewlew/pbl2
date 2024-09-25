#include "Admin.h"
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

void manageMovies();
void manageRooms();
void manageShowtimes();
void manageTickets();
void manageUsers();
void revenue();
void searchMovie();
void addNewMovie();
void editMovie();
void deleteMovie();
void addNewRoom();
void editRoom();
void deleteRoom();
void addNewShowtime();
void editShowtime();
void deleteShowtime();
void editTicket();
void deleteTicket();
void addUser();
void editUser();
void deleteUser();

// Function to set cursor position
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void adminFunctionality() {
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

        std::cout << "\033[33mAdmin Menu:\n\n\033[0m";

        for (int i = 0; i < NUM_OPTIONS; ++i) {
            if (i == selectedOption) {
                std::cout << "\033[44m> " << options[i] << "\033[0m\n";
            } else {
                std::cout << "  " << options[i] << "\n";
            }
        }

        key = _getch();  // Get user input without pressing Enter

        switch (key) {
            case 72:  // Up arrow
                selectedOption = (selectedOption - 1 + NUM_OPTIONS) % NUM_OPTIONS;
                break;
            case 80:  // Down arrow
                selectedOption = (selectedOption + 1) % NUM_OPTIONS;
                break;
            case 13:  // Enter key
                switch (selectedOption) {
                    case 0: manageMovies(); break;
                    case 1: manageRooms(); break;
                    case 2: manageShowtimes(); break;
                    case 3: manageTickets(); break;
                    case 4: manageUsers(); break;
                    case 5: revenue(); break;
                    case 6: return;  // Logout
                }
                break;
        }
    }
}

void manageMovies() {
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
    switch (choice) {
        case 1: addNewMovie(); break;
        case 2: editMovie(); break;
        case 3: deleteMovie(); break;
        std::cout << "\033[31m";
        default: std::cout << "Invalid choice. Please try again.\n";
        std::cout << "\033[0m";
    }

}

void manageRooms() {
    std::vector<Room> rooms = Room::getAll();
    std::cout << "\034[0m";
    std::cout << "All Rooms:\n";
    std::cout << "ID | Capacity \n";
    for (const auto& room : rooms) {
        std::cout << room.getId() <<  " | " << room.getCapacity() << "\n";
    }
    std::cout << "\033[0m";
    std::cout << "\033[31m";
    std::cout << "Choose an option:\n";
    std::cout << "1. Add New Room\n";
    std::cout << "2. Edit Room\n";
    std::cout << "3. Delete Room\n";
    std::cout << "Enter your choice: ";
    std::cout << "\033[0m";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1: addNewRoom(); break;
        case 2: editRoom(); break;
        case 3: deleteRoom(); break;
    }
    
}

void manageShowtimes() {
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
    switch (choice) {
        case 1: addNewShowtime(); break;
        case 2: editShowtime(); break;
        case 3: deleteShowtime(); break;
    }
}

void manageTickets() {
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
    switch (choice) {
        case 1: editTicket(); break;
        case 2: deleteTicket(); break;
        std::cout << "\033[31m";
        default: std::cout << "Invalid choice. Please try again.\n"; break;
        std::cout << "\033[0m";
    }
}

void editTicket() {
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter the ID of the ticket you want to edit: ";
    std::cout << "\033[0m";
    std::cin >> id;

    try {
        Ticket ticketToEdit = Ticket::getById(id);

        std::string showTimeId;
        std::cout << "\033[33m";
        std::cout << "Current showtime ID: " << ticketToEdit.getShowTimeId() << std::endl;
        std::cout << "Enter new showtime ID (press Enter to keep current): ";
        std::cout << "\033[0m";
        std::cin.ignore();
        std::getline(std::cin, showTimeId);
        if (showTimeId.empty()) showTimeId = ticketToEdit.getShowTimeId();

        std::cout << "\033[33m";
        std::cout << "Current seat IDs: ";
        const auto& currentSeatIds = ticketToEdit.getSeatIds();
        for (size_t i = 0; i < currentSeatIds.size(); ++i) {
            std::cout << currentSeatIds[i];
            if (i < currentSeatIds.size() - 1) {
                std::cout << ", ";
            }
        std::cout << "\033[0m";
        }
        std::cout << std::endl;

        std::cout << "\033[33m";
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

        Ticket updatedTicket(id, showTimeId, seatIds, ticketToEdit.getPrice());
        Ticket::update(updatedTicket);
        std::cout << "\033[32m";
        std::cout << "Ticket updated successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error editing ticket: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

void deleteTicket() {
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter the ID of the ticket you want to delete: ";
    std::cout << "\033[0m";
    std::cin >> id;

    try {
        Ticket::remove(id);
        std::cout << "\033[32m";
        std::cout << "Ticket deleted successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error deleting ticket: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

void manageUsers() {
    std::vector<User> users = User::getAll();
    std::cout << "\033[34m";
    std::cout << "All Users:\n";
    std::cout << "ID | Username | Password | Role\n";
    for (const auto& user : users) {
        std::cout << user.getId() << " | " << user.getUsername() << " | " 
                  << std::string(user.getPassword().length(), '*') << " | ";
        
        if (user.getRole() == UserRole::Admin) {
            std::cout << "Admin";
        } else if (user.getRole() == UserRole::Normal) {
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
    switch (choice) {
        case 1: addUser(); break;
        case 2: editUser(); break;
        case 3: deleteUser(); break;
        std::cout << "\033[31m";
        default: std::cout << "Invalid choice. Please try again.\n"; break;
        std::cout << "\033[0m";
    }
}

void addUser() {
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

    UserRole userRole;
    if (role == "admin") {
        userRole = UserRole::Admin;
    } else if (role == "normal") {
        userRole = UserRole::Normal;
    } else {
        std::cerr << "Invalid role. Defaulting to Normal.\n";
        userRole = UserRole::Normal;
    }

    try {
        User newUser(id, username, password, userRole);
        newUser.save(newUser);
        std::cout << "\033[32m";
        std::cout << "User added successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error adding user: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

void editUser() {
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter the ID of the user you want to edit: ";
    std::cout << "\033[0m";
    std::cin >> id;

    try {
        User userToEdit = User::getById(id);

        std::string username, password, role;
        std::cout << "\033[33m";
        std::cout << "Current username: " << userToEdit.getUsername() << std::endl;
        std::cout << "Enter new username (press Enter to keep current): ";
        std::cout << "\033[0m";
        std::cin.ignore();
        std::getline(std::cin, username);
        if (username.empty()) username = userToEdit.getUsername();

        std::cout << "\033[33m";
        std::cout << "Enter new password (press Enter to keep current): ";
        std::cout << "\033[0m";
        std::getline(std::cin, password);
        if (password.empty()) password = userToEdit.getPassword();

        std::cout << "\033[33";
        std::cout << "Current role: " << (userToEdit.getRole() == UserRole::Admin ? "Admin" : "Normal User") << std::endl;
        std::cout << "Enter new role (Admin/Normal, press Enter to keep current): ";
        std::cout << "\033[0m";
        std::getline(std::cin, role);
        UserRole newRole = userToEdit.getRole();
        if (!role.empty()) {
            if (role == "Admin") newRole = UserRole::Admin;
            else if (role == "Normal") newRole = UserRole::Normal;
            else {
                std::cout << "\033[31m";
                std::cout << "Invalid role. Keeping current role.\n";
                std::cout << "\033[0m";
            }
        }

        User updatedUser(id, username, password, newRole);
        User::update(updatedUser);
        std::cout << "\033[32m";
        std::cout << "User updated successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error editing user: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

void deleteUser() {
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter the ID of the user you want to delete: ";
    std::cout << "\033[0m";
    std::cin >> id;

    try {
        User::remove(id);
        std::cout << "\033[32m";
        std::cout << "User deleted successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error deleting user: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

void revenue() {
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
}

void addNewMovie() {
    std::string name, duration, showStartDate, showStopDate;
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter movie id: ";
    std::cout << "\033[0m";
    std::cin >> id;
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
    std::cout << "\033[33m";
    std::cout << "Enter movie show stop date (YYYY-MM-DD): ";
    std::cout << "\033[0m";
    std::cin >> showStopDate;

    Movie newMovie(id, name, duration, showStartDate, showStopDate);
    try {
        Movie::save(newMovie);
        std::cout << "\033[32m";
        std::cout << "Movie added successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error adding movie: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

void editMovie() {
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter the ID of the movie you want to edit: ";
    std::cout << "\033[0m";
    std::cin >> id;

    try {
        Movie movieToEdit = Movie::getbyId(id);

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
        std::cout << "Enter new movie show stop date (YYYY-MM-DD) (press Enter to keep current): ";
        std::cout << "\033[0m";
        std::getline(std::cin, showStopDate);
        if (showStopDate.empty()) showStopDate = movieToEdit.getShowStopDate();

        Movie updatedMovie(id, name, duration, showStartDate, showStopDate);
        Movie::update(updatedMovie);
        std::cout << "\033[32m";
        std::cout << "Movie updated successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error editing movie: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

void deleteMovie() {
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter the ID of the movie you want to delete: ";
    std::cout << "\033[0m";
    std::cin >> id;

    try {
        Movie::remove(id);
        std::cout << "\033[32m";
        std::cout << "Movie deleted successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error deleting movie: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

void addNewRoom() {
    std::string id;
    int capacity;
    std::cout << "\033[33m";
    std::cout << "Enter room id: ";
    std::cout << "\033[0m";
    std::cin >> id;
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

void editRoom() {
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter the ID of the room you want to edit: ";
    std::cout << "\033[0m";
    std::cin >> id;

    try {
        Room roomToEdit = Room::getById(id);

        int capacity;
        std::cout << "\033[33m";
        std::cout << "Current room capacity: " << roomToEdit.getCapacity() << std::endl;
        std::cout << "Enter new room capacity (or 0 to keep current): ";
        std::cout << "\033[0m";
        std::cin >> capacity;
        
        if (capacity == 0) {
            capacity = roomToEdit.getCapacity();
        }

        Room updatedRoom(id, capacity);
        Room::update(updatedRoom);
        std::cout << "\033[32m";
        std::cout << "Room updated successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error editing room: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

void deleteRoom() {
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter the ID of the room you want to delete: ";
    std::cout << "\033[0m";
    std::cin >> id;

    try {
        Room::remove(id);
        std::cout << "\033[32m";
        std::cout << "Room deleted successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error deleting room: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

static std::string getCurrentDate() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

void addNewShowtime() {

    std::string currentDate = getCurrentDate();
    std::vector<Movie> movies = Movie::getAll();
    std::vector<Movie> availableMovies;

    std::string id, movieId, roomId, showTime, showDate;
    std::cout << "\033[33m";
    std::cout << "Enter showtime ID: ";
    std::cout << "\033[0m";
    std::cin >> id;
    
    std::cout << "\033[34m";
    std::cout << "Movies available for creating showtimes:\n";
    for (const auto& movie : movies) {
        if (currentDate >= movie.getShowStartDate() && currentDate <= movie.getShowStopDate()) {
            availableMovies.push_back(movie);
            std::cout << "- Movie ID: " << movie.getId() << ", Name: " << movie.getName() << "\n";
        }
    }
    std::cout << "\033[0m";

    if (availableMovies.empty()) {
        std::cout << "\033[31m";
        std::cout << "No movies available for creating showtimes.\n";
        std::cout << "\033[0m";
        return;
    }

    std::cout << "\033[33m";
    std::cout << "Enter movie ID from the list above: ";
    std::cout << "\033[0m";
    std::cin >> movieId;
    std::cout << "\033[33m";
    std::cout << "Enter room ID: ";
    std::cout << "\033[0m";
    std::cin >> roomId;
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
        
        if (showDate < currentDate) {
            std::cout << "\033[31m";
            std::cout << "Error: The entered date is in the past. Please enter a future date.\n";
            std::cout << "\033[0m";
        } else {
            validDate = true;
        }
    }

    ShowTime newShowtime(id, movieId, roomId, showTime, showDate);
    ShowTime::save(newShowtime);
    std::cout << "\033[32m";
    std::cout << "Showtime added successfully!\n";
    std::cout << "\033[0m";
}

void editShowtime() {
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter the ID of the showtime you want to edit: ";
    std::cout << "\033[0m";
    std::cin >> id;

    try {
        ShowTime showtimeToEdit = ShowTime::getById(id);

        std::string movieId, roomId, showTime, showDate;
        std::cout << "\033[33m";
        std::cout << "Current movie ID: " << showtimeToEdit.getMovieId() << std::endl;
        std::cout << "Enter new movie ID (press Enter to keep current): ";
        std::cout << "\033[0m";
        std::cin.ignore();
        std::getline(std::cin, movieId);
        if (movieId.empty()) movieId = showtimeToEdit.getMovieId();

        std::cout << "\033[33m";
        std::cout << "Current room ID: " << showtimeToEdit.getRoomId() << std::endl;
        std::cout << "Enter new room ID (press Enter to keep current): ";
        std::cout << "\033[0m";
        std::getline(std::cin, roomId);
        if (roomId.empty()) roomId = showtimeToEdit.getRoomId();

        std::cout << "\033[33m";
        std::cout << "Current show time: " << showtimeToEdit.getShowTime() << std::endl;
        std::cout << "Enter new show time (HH:MM) (press Enter to keep current): ";
        std::cout << "\033[0m";
        std::getline(std::cin, showTime);
        if (showTime.empty()) showTime = showtimeToEdit.getShowTime();

        std::cout << "\033[33m";
        std::cout << "Current show date: " << showtimeToEdit.getShowDate() << std::endl;
        std::cout << "Enter new show date (YYYY-MM-DD) (press Enter to keep current): ";
        std::cout << "\033[0m";
        std::getline(std::cin, showDate);
        if (showDate.empty()) showDate = showtimeToEdit.getShowDate();

        ShowTime updatedShowtime(id, movieId, roomId, showTime, showDate);
        ShowTime::update(updatedShowtime);
        std::cout << "\033[32m";
        std::cout << "Showtime updated successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error editing showtime: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

void deleteShowtime() {
    std::string id;
    std::cout << "\033[33m";
    std::cout << "Enter the ID of the showtime you want to delete: ";
    std::cout << "\033[0m";
    std::cin >> id;

    try {
        ShowTime::remove(id);
        std::cout << "\033[32m";
        std::cout << "Showtime deleted successfully!\n";
        std::cout << "\033[0m";
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error deleting showtime: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}