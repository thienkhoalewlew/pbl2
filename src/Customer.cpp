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
#include <conio.h>
#include <windows.h>

bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& stopDate);
std::string loadMovieAvailable(const std::string& currentDate);
std::string loadShowtimesForMovie(const std::string& movieId, const std::string& currentDate);
std::string loadSeatForShowtime(const std::string& showtimeId);
void printTicket(const std::string& movieId, const std::string& showtimeId, const std::vector<std::string>& seatIds);

void customerFunctionality(const std::string& currentDate) {
    std::string movieId=loadMovieAvailable(currentDate);
    std::string showtimeId = loadShowtimesForMovie(movieId, currentDate);
    std::string seatInput = loadSeatForShowtime(showtimeId);

    std::vector<std::string> seatIds;
    std::istringstream iss(seatInput);
    std::string seatId;
    while (std::getline(iss, seatId, ',')) {
        seatIds.push_back(seatId);
    }

    printTicket(movieId, showtimeId, seatIds);
}

std::string loadMovieAvailable(const std::string& currentDate) {
    std::vector<ShowTime> showtimes = ShowTime::getAll();
    std::vector<std::string> availableMovieIds;
    std::vector<Movie> availableMovies;

    // Collect available movies
    for (const auto& showtime : showtimes) {
        if (showtime.getShowDate() == currentDate) {
            std::string movieId = showtime.getMovieId();
            if (std::find(availableMovieIds.begin(), availableMovieIds.end(), movieId) == availableMovieIds.end()) {
                availableMovieIds.push_back(movieId);
                try {
                    Movie movie = Movie::getbyId(movieId);
                    availableMovies.push_back(movie);
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
            }
        }
    }

    if (availableMovies.empty()) {
        std::cout << "\033[31mNo movies available for today.\033[0m\n";
        exit(0);
    }

    int selectedIndex = 0;
    int key;

    while (true) {
        system("cls");  // Clear the console
        std::cout << "\033[32mAvailable movies for " << currentDate << ":\033[0m\n\n";

        for (size_t i = 0; i < availableMovies.size(); ++i) {
            if (i == selectedIndex) {
                std::cout << "\033[44m";  // Blue background for selected movie
            }
            std::cout << "- Movie ID: " << availableMovies[i].getId() << "\n";
            std::cout << "  Name: " << availableMovies[i].getName() << "\n";
            std::cout << "  Duration: " << availableMovies[i].getDuration() << " minutes\n";
            std::cout << "  Show date: " << currentDate << "\n\n";
            if (i == selectedIndex) {
                std::cout << "\033[0m";  // Reset color
            }
        }

        std::cout << "\033[33mUse arrow keys to navigate, Enter to select.\033[0m\n";

        key = _getch();  // Get user input without pressing Enter
        switch (key) {
            case 72:  // Up arrow
                selectedIndex = (selectedIndex - 1 + availableMovies.size()) % availableMovies.size();
                break;
            case 80:  // Down arrow
                selectedIndex = (selectedIndex + 1) % availableMovies.size();
                break;
            case 13:  // Enter key
                return availableMovies[selectedIndex].getId();
        }
    }
}

bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& stopDate) {
    return date >= startDate && date <= stopDate;
}

std::string loadShowtimesForMovie(const std::string& movieId, const std::string& currentDate) {
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

        if (filteredShowtimes.empty()) {
            std::cout << "\033[31m";
            std::cout << "No showtimes available for this movie.\n";
            std::cout << "\033[0m";
            return "No showtimes available for this movie.";
        }

        std::cout << "\033[34m"; 
        int selectedOption = 0;
        int key;
        while (true) {
            system("cls"); 
            std::cout << "Showtimes today for \"" << movieName << "\":\n";
            for (size_t i = 0; i < filteredShowtimes.size(); ++i) {
                if (i == selectedOption) {
                    std::cout << "\033[44m" << i + 1 << ". Showtime ID: " << filteredShowtimes[i].getId() << "\n";
                    std::cout << "   Show Time: " << filteredShowtimes[i].getShowTime() << "\n";
                    std::cout << "   Show Date: " << filteredShowtimes[i].getShowDate() << "\n";
                    std::cout << "   Room ID: " << filteredShowtimes[i].getRoomId() << "\n\n";
                    std::cout << "\033[0m"; 
                } else {
                    std::cout << i + 1 << ". Showtime ID: " << filteredShowtimes[i].getId() << "\n";
                    std::cout << "   Show Time: " << filteredShowtimes[i].getShowTime() << "\n";
                    std::cout << "   Show Date: " << filteredShowtimes[i].getShowDate() << "\n";
                    std::cout << "   Room ID: " << filteredShowtimes[i].getRoomId() << "\n\n";
                }
            }
            key = _getch();  // Get user input without pressing Enter
            switch (key) {
                case 72:  // Up arrow
                    selectedOption = (selectedOption - 1 + filteredShowtimes.size()) % filteredShowtimes.size();
                    break;
                case 80:  // Down arrow
                    selectedOption = (selectedOption + 1) % filteredShowtimes.size();
                    break;
                case 13:  // Enter key
                    const auto& selectedShowtime = filteredShowtimes[selectedOption];
                    std::cout << "\033[32m";
                    std::cout << "You have selected showtime ID: " << selectedShowtime.getId() << "\n";
                    std::cout << "\033[0m";
                    return selectedShowtime.getId();
            }
        }
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error: " << e.what() << "\n";
        std::cout << "Movie ID not found. Please enter a valid movie ID.\n";
        std::cout << "\033[0m";
        return "No showtimes available for this movie.";
    }
}

std::string loadSeatForShowtime(const std::string& showtimeId) {
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

        std::vector<int> selectedSeats;
        int currentSeat = 0;
        int key;
        while (true) {
            system("cls"); 
            std::cout << "\033[33m"; 
            std::cout << "Available seats for showtime " << showtimeId << " in room " << roomId << ":\n";
            std::cout << "\033[0m"; 
            for (size_t i = 0; i < allSeats.size(); ++i) {
                if (i == currentSeat) {
                    std::cout << "\033[44m"; // Highlight current seat with blue background
                }
                if (std::find(selectedSeats.begin(), selectedSeats.end(), i) != selectedSeats.end()) {
                    std::cout << "\033[42m" << allSeats[i] << " \033[0m"; // Green background for selected seats
                } else if (std::find(bookedSeats.begin(), bookedSeats.end(), allSeats[i]) != bookedSeats.end()) {
                    std::cout << "\033[40m" << allSeats[i] << " \033[0m"; // Dark background for booked seats
                } else {
                    std::cout << allSeats[i] << " ";
                }
                if (i == currentSeat) {
                    std::cout << "\033[0m"; // Reset color after current seat
                }
            }
            std::cout << "\n";
            std::cout << "\033[33m";
            std::cout << "Use arrow keys to navigate. Press Space to select/deselect. Press Enter when done.\n";
            std::cout << "\033[0m";
            
            key = _getch();  // Get user input without pressing Enter
            switch (key) {
                case 75:  // Left arrow
                    do {
                        currentSeat = (currentSeat - 1 + allSeats.size()) % allSeats.size();
                    } while (std::find(bookedSeats.begin(), bookedSeats.end(), allSeats[currentSeat]) != bookedSeats.end());
                    break;
                case 77:  // Right arrow
                    do {
                        currentSeat = (currentSeat + 1) % allSeats.size();
                    } while (std::find(bookedSeats.begin(), bookedSeats.end(), allSeats[currentSeat]) != bookedSeats.end());
                    break;
                case 32:  // Space bar
                    if (std::find(selectedSeats.begin(), selectedSeats.end(), currentSeat) != selectedSeats.end()) {
                        // Deselect the seat
                        selectedSeats.erase(std::remove(selectedSeats.begin(), selectedSeats.end(), currentSeat), selectedSeats.end());
                    } else {
                        // Select the seat
                        selectedSeats.push_back(currentSeat);
                    }
                    break;
                case 13:  // Enter key
                    if (!selectedSeats.empty()) {
                        std::vector<std::string> selectedSeatIds;
                        for (int seat : selectedSeats) {
                            selectedSeatIds.push_back(allSeats[seat]);
                        }
                        std::cout << "\033[32m";
                        std::cout << "You have selected seats: ";
                        for (const auto& seat : selectedSeatIds) {
                            std::cout << seat << " ";
                        }
                        std::cout << "\n";
                        std::cout << "\033[0m";
                        std::string result;
                        for (size_t i = 0; i < selectedSeatIds.size(); ++i) {
                            result += selectedSeatIds[i];
                            if (i < selectedSeatIds.size() - 1) {
                                result += ",";
                            }
                        }
                        return result;
                    } else {
                        std::cout << "\033[31m";
                        std::cout << "Please select at least one seat.\n";
                        std::cout << "\033[0m";
                        std::cin.ignore();
                        std::cin.get();
                    }
                    break;
            }
        }
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error: " << e.what() << "\n";
        std::cout << "\033[0m";
        return "No available seats.";
        std::cin.ignore();
        std::cin.get();
    }
    return "No available seats.";
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
            std::cout << "\033[31m"; 
            std::cout << "Ticket booking cancelled.\n";
            std::cout << "\033[0m"; 
        }
    } catch (const std::exception& e) {
        std::cout << "\033[31m";
        std::cerr << "Error: " << e.what() << "\n";
        std::cout << "\033[0m";
    }
}