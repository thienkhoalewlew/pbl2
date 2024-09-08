#include "Admin.h"
#include "../include/Movie.h"
#include "../include/ShowTime.h"
#include "../include/Room.h"
#include "../include/Ticket.h"
#include "../include/LoginForm.h"
#include <iostream>
#include <string>
#include <vector>

void addMovie();
void editMovie();
void deleteMovie();
void addRoom();
void editRoom();
void deleteRoom();
void addShowTime();
void editShowTime();
void deleteShowTime();
void addTicket();
void editTicket();
void deleteTicket();

void adminFunctionality() {
    int choice;
    do {
        std::cout << "Admin Menu:\n";
        std::cout << "1. Manage Movies\n";
        std::cout << "2. Manage Rooms\n";
        std::cout << "3. Manage Showtimes\n";
        std::cout << "4. Manage Tickets\n";
        std::cout << "5. Manage Users\n";
        std::cout << "0. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 0: {
                 break;
                }
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void addMovie() {
    std::string id, name, duration, showStartDate, showStopDate;

    std::cout << "Enter Movie ID: ";
    std::cin >> id;
    std::cin.ignore(); // Ignore leftover newline character

    std::cout << "Enter Movie Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Duration (in minutes): ";
    std::getline(std::cin, duration);

    std::cout << "Enter Show Start Date (YYYY-MM-DD): ";
    std::getline(std::cin, showStartDate);

    std::cout << "Enter Show Stop Date (YYYY-MM-DD): ";
    std::getline(std::cin, showStopDate);

    // Create a Movie object
    Movie newMovie(id, name, duration, showStartDate, showStopDate);

    // Save the movie to the database (e.g., a file)
    try {
        newMovie.save(newMovie);
        std::cout << "Movie added successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void editMovie() {
    std::string id;
    std::cout << "Enter Movie ID to edit: ";
    std::cin >> id;
    std::cin.ignore(); // Ignore leftover newline character

    try {
        Movie movie = Movie::getbyId(id);

        std::string name, duration, showStartDate, showStopDate;

        std::cout << "Enter new Movie Name (current: " << movie.getName() << "): ";
        std::getline(std::cin, name);

        std::cout << "Enter new Duration (in minutes) (current: " << movie.getDuration() << "): ";
        std::getline(std::cin, duration);

        std::cout << "Enter new Show Start Date (YYYY-MM-DD) (current: " << movie.getShowStartDate() << "): ";
        std::getline(std::cin, showStartDate);

        std::cout << "Enter new Show Stop Date (YYYY-MM-DD) (current: " << movie.getShowStopDate() << "): ";
        std::getline(std::cin, showStopDate);

        // Update the movie object
        Movie updatedMovie(id, name, duration, showStartDate, showStopDate);

        // Save the updated movie to the database
        updatedMovie.update(updatedMovie);
        std::cout << "Movie updated successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void deleteMovie() {
    // Implementation for deleting a movie
}

void addRoom() {
    // Implementation for adding a room
}

void editRoom() {
    // Implementation for editing a room
}

void deleteRoom() {
    // Implementation for deleting a room
}

void addShowTime() {
    // Implementation for adding a showtime
}

void editShowTime() {
    // Implementation for editing a showtime
}

void deleteShowTime() {
    // Implementation for deleting a showtime
}

void addTicket() {
    // Implementation for adding a ticket
}

void editTicket() {
    // Implementation for editing a ticket
}

void deleteTicket() {
    // Implementation for deleting a ticket
}