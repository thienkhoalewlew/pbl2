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
void loadShowtimesForMovie(const std::string& movieId);
void loadSeatForShowtime(const std::string& showtimeId);
void printTicket(const std::string& movieId, const std::string& showtimeId, const std::vector<std::string>& seatIds);

void customerFunctionality(const std::string& currentDate) {
    std::cout << "Welcome to the movie booking system!\n";
    loadMovieAvailable(currentDate);

    std::string movieId;
    std::cout << "Enter Movie ID to continue: ";
    std::cin >> movieId;
    loadShowtimesForMovie(movieId);

    std::string showtimeId;
    std::cout << "Enter Showtime ID to continue: ";
    std::cin >> showtimeId;
    loadSeatForShowtime(showtimeId);

    std::string seatInput;
    std::cout << "Enter Seat IDs to book (separated by commas): ";
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
    
    std::cout << "Available movies for " << currentDate << ":\n";
    
    for (const auto& showtime : showtimes) {
        if (showtime.getShowDate() == currentDate) {
            std::string movieId = showtime.getMovieId();
            if (std::find(availableMovieIds.begin(), availableMovieIds.end(), movieId) == availableMovieIds.end()) {
                availableMovieIds.push_back(movieId);
                try {
                    Movie movie = Movie::getbyId(movieId);
                    std::cout << "- Movie ID: " << movie.getId() << "\n";
                    std::cout << "  Name: " << movie.getName() << "\n";
                    std::cout << "  Duration: " << movie.getDuration() << " minutes\n";
                    std::cout << "  Show date: " << currentDate << "\n\n";
                    found = true;
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
            }
        }
    }
    
    if (!found) {
        std::cout << "No movies available for today.\n";
    }
}

bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& stopDate) {
    return date >= startDate && date <= stopDate;
}

void loadShowtimesForMovie(const std::string& movieId) {
    try {
        Movie movie = Movie::getbyId(movieId);
        std::string movieName = movie.getName();

        std::vector<ShowTime> showtimes = ShowTime::getAll();
        bool found = false;

        std::cout << "Showtimes for \"" << movieName << "\":\n";

        for (const auto& showtime : showtimes) {
            if (showtime.getMovieId() == movieId) {
                std::cout << "- Showtime ID: " << showtime.getId() << "\n";
                std::cout << "  Show Time: " << showtime.getShowTime() << "\n";
                std::cout << "  Show Date: " << showtime.getShowDate() << "\n";
                std::cout << "  Room ID: " << showtime.getRoomId() << "\n\n";
                found = true;
            }
        }

        if (!found) {
            std::cout << "No showtimes available for this movie.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
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
        std::cout << "Available seats for showtime " << showtimeId << " in room " << roomId << ":\n";
        bool found = false;
        for (const auto& seat : allSeats) {
            if (std::find(bookedSeats.begin(), bookedSeats.end(), seat) == bookedSeats.end()) {
                std::cout << seat << " ";
                found = true;
            }
        }
        if (!found) {
            std::cout << "No available seats.\n";
        } else {
            std::cout << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
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

        // Confirm ticket booking
        char confirmation;
        std::cout << "Please confirm your ticket booking (y/n): ";
        std::cin >> confirmation;

        if (confirmation == 'y' || confirmation == 'Y') {
            // Generate a unique ticket ID
            std::string ticketId = "T" + std::to_string(std::time(0));

            // Create a Ticket object and save it
            Ticket ticket(ticketId, showtimeId, seatIds, price);
            Ticket::save(ticket);

            std::cout << "Your ticket has been successfully booked!\n";
            std::cout << "Ticket ID: " << ticketId << "\n";
        } else {
            std::cout << "Ticket booking cancelled.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}