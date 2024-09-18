#include "../include/Customer.h"
#include "../include/Movie.h"
#include "../include/ShowTime.h"
#include "../include/Room.h"
#include "../include/Ticket.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>

bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& stopDate);
void loadMovieAvailable(const std::string& currentDate);
void loadShowtimesForMovie(const std::string& movieId, const std::string& currentDate);
void loadSeatForShowtime(const std::string& showtimeId);
void printTicket(const std::string& movieId, const std::string& showtimeId, const std::vector<std::string>& seatIds);

void customerFunctionality(const std::string& currentDate) {
    std::cout << "\033[32m";
    std::cout << "Welcome to the movie booking system!\n";
    std::cout << "\033[0m";
    loadMovieAvailable(currentDate);

    std::string movieId;
    while (true) {
        std::cout << "\033[33m";
        std::cout << "Enter Movie ID to continue: ";
        std::cout << "\033[0m";
        std::cin >> movieId;
        try {
            Movie movie = Movie::getbyId(movieId);
            if (movie.getId() == movieId) {
                loadShowtimesForMovie(movieId, currentDate);
                break; // Exit the loop if movie ID is found
            }
        } catch (const std::exception& e) {
            std::cout << "\033[31m";
            std::cerr << "Movie ID not found. Please try again.\n";
            std::cout << "\033[0m";
        }
    }

    std::string showtimeId;
    std::cout << "\033[33m";
    std::cout << "Enter Showtime ID to continue: ";
    std::cout << "\033[0m";
    std::cin >> showtimeId;
    while (true) {
        try {
            ShowTime showtime = ShowTime::getById(showtimeId);
            if (showtime.getId() == showtimeId) {
                loadSeatForShowtime(showtimeId);
                break; // Exit the loop if showtime ID is found
            }
        } catch (const std::exception& e) {
            std::cout << "\033[31m";
            std::cerr << "Showtime ID not found. Please try again.\n";
            std::cout << "\033[0m";
            std::cout << "Enter Showtime ID to continue: ";
            std::cin >> showtimeId;
        }
    }

    std::string seatInput;
    std::cout << "\033[33m";
    std::cout << "Enter Seat IDs to book (separated by commas): ";
    std::cout << "\033[0m";
    std::cin.ignore();  // Ignore leftover newline character
    std::getline(std::cin, seatInput);

    // Split seatInput by commas
    std::vector<std::string> seatIds;
    std::istringstream iss(seatInput);
    std::string seatId;
    while (std::getline(iss, seatId, ',')) {
        seatIds.push_back(seatId);
    }

    printTicket(movieId, showtimeId, seatIds);
}

void loadMovieAvailable(const std::string& currentDate) {
    std::vector<ShowTime> showtimes = ShowTime::getAll();
    std::vector<std::string> availableMovieIds;
    bool found = false;
    std::cout << "\033[32m";
    std::cout << "Available movies for " << currentDate << ":\n";
    std::cout << "\033[0m";
    
    for (const auto& showtime : showtimes) {
        if (showtime.getShowDate() == currentDate) {
            std::string movieId = showtime.getMovieId();
            if (std::find(availableMovieIds.begin(), availableMovieIds.end(), movieId) == availableMovieIds.end()) {
                availableMovieIds.push_back(movieId);
                try {
                    Movie movie = Movie::getbyId(movieId);
                    std::cout << "\033[34m";
                    std::cout << "- Movie ID: " << movie.getId() << "\n";
                    std::cout << "  Name: " << movie.getName() << "\n";
                    std::cout << "  Duration: " << movie.getDuration() << " minutes\n";
                    std::cout << "  Show date: " << currentDate << "\n\n";
                    std::cout << "\033[0m";
                    found = true;
                } catch (const std::exception& e) {
                    std::cout << "\033[31m";
                    std::cerr << "Error: " << e.what() << "\n";
                    std::cout << "\033[0m";
                }
            }
        }
    }
    
    if (!found) {
        std::cout << "\033[31m";
        std::cout << "No movies available for today.\n";
        std::cout << "\033[0m"; 
    }
}

bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& stopDate) {
    return date >= startDate && date <= stopDate;
}

void loadShowtimesForMovie(const std::string& movieId, const std::string& currentDate) {
    try {
        Movie movie = Movie::getbyId(movieId);
        std::string movieName = movie.getName();

        std::vector<ShowTime> showtimes = ShowTime::getAll();
        std::vector<ShowTime> filteredShowtimes;
        bool found = false;

        for (const auto& showtime : showtimes) {
            if (showtime.getMovieId() == movieId && showtime.getShowDate() == currentDate) {
                filteredShowtimes.push_back(showtime);
            }
        }
        std::cout << "\033[33m"; 
        std::cout << "Showtimes today for \"" << movieName << "\":\n";
        std::cout << "\033[0m"; 

        std::cout << "\033[34m"; 
        for (const auto& showtime : filteredShowtimes) {

            std::cout << "- Showtime ID: " << showtime.getId() << "\n";
            std::cout << "  Show Time: " << showtime.getShowTime() << "\n";
            std::cout << "  Show Date: " << showtime.getShowDate() << "\n";
            std::cout << "  Room ID: " << showtime.getRoomId() << "\n\n";
            found = true;
        }
        std::cout << "\033[0m"; 
        if (!found) {
            std::cout << "\033[31m";
            std::cout << "No showtimes available for this movie.\n";
            std::cout << "\033[0m";
        }
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error: " << e.what() << "\n";
        std::cout << "Movie ID not found. Please enter a valid movie ID.\n";
        std::cout << "\033[0m";
    }
}

void loadSeatForShowtime(const std::string& showtimeId) {
    try {
        // Get the showtime to find the associated room
        ShowTime showtime = ShowTime::getById(showtimeId);
        std::string roomId = showtime.getRoomId();

        // Get the room and its capacity
        Room room = Room::getById(roomId);
        int capacity = room.getCapacity();

        // Create a list of all possible seats
        std::vector<std::string> allSeats;
        for (int i = 1; i <= capacity; ++i) {
            std::ostringstream seatId;
            seatId << roomId << std::setw(2) << std::setfill('0') << i; 
            allSeats.push_back(seatId.str());
        }

        // Get all tickets to filter out booked seats
        std::vector<Ticket> tickets = Ticket::getAll();
        std::vector<std::string> bookedSeats;
        for (const auto& ticket : tickets) {
            if (ticket.getShowTimeId() == showtimeId) {
                std::vector<std::string> ticketSeats = ticket.getSeatIds();
                bookedSeats.insert(bookedSeats.end(), ticketSeats.begin(), ticketSeats.end());
            }
        }

        // Display available seats
        std::cout << "\033[33m"; 
        std::cout << "Available seats for showtime " << showtimeId << " in room " << roomId << ":\n";
        std::cout << "\033[0m"; 
        bool found = false;
        std::cout << "\033[34m";
        for (const auto& seat : allSeats) {
            if (std::find(bookedSeats.begin(), bookedSeats.end(), seat) == bookedSeats.end()) {
                std::cout << seat << " ";
                found = true;
            }
        }
        std::cout << "\033[0m"; 
        if (!found) {
            std::cout << "\033[31m";
            std::cout << "No available seats.\n";
            std::cout << "\033[0m";
        } else {
            std::cout << "\n";
        }
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error: " << e.what() << "\n";
        std::cout << "\033[0m";
    }
}

void printTicket(const std::string& movieId, const std::string& showtimeId, const std::vector<std::string>& seatIds) {
    try {
        // Retrieve movie details
        Movie movie = Movie::getbyId(movieId);
        std::string movieName = movie.getName();

        // Retrieve showtime details
        ShowTime showtime = ShowTime::getById(showtimeId);
        std::string roomId = showtime.getRoomId();
        std::string showDate = showtime.getShowDate();
        std::string showTime = showtime.getShowTime();

        // Calculate ticket price based on seat type
        double price = 0.0;
        for (const auto& seat : seatIds) {
            if (seat.find("VIP") == 0) {
                price += 60000;
            } else {
                price += 45000;
            }
        }

        // Print ticket details
        std::cout << "\033[34m"; 
        std::cout << "Ticket Information:\n";
        std::cout << "Movie Name: " << movieName << "\n";
        std::cout << "Room ID: " << roomId << "\n";
        std::cout << "Show Date: " << showDate << "\n";
        std::cout << "Show Time: " << showTime << "\n";
        std::cout << "Seats: ";
        for (const auto& seat : seatIds) {
            std::cout << seat << " ";
        }
        std::cout << "\n";
        std::cout << "Total Price: " << price << "\n";
        std::cout << "\033[0m"; 

        // Confirm ticket booking
        char confirmation;
        std::cout << "\033[31m";

        std::cout << "\033[33m";
        std::cout << "Please confirm your ticket booking (y/n): ";
        std::cout << "\033[0m";
        std::cin >> confirmation;

        if (confirmation == 'y' || confirmation == 'Y') {
            // Generate a unique ticket ID
            std::string ticketId = "T" + std::to_string(std::time(0));

            // Create a Ticket object and save it
            Ticket ticket(ticketId, showtimeId, seatIds, price);
            Ticket::save(ticket);

            std::cout << "\033[33m"; 
            std::cout << "Your ticket has been successfully booked!\n";
            std::cout << "Ticket ID: " << ticketId << "\n";
            std::cout << "\033[0m"; 
        } else {
            std::cout << "\031[0m"; 
            std::cout << "Ticket booking cancelled.\n";
            std::cout << "\033[0m"; 
        }
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error: " << e.what() << "\n";
        std::cout << "\033[0m";
    }
}