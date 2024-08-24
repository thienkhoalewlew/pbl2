#include "../include/LoginForm.h"
#include "../include/User.h"
#include "../include/Movie.h"
#include "../include/ShowTime.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string getCurrentDate();
bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& stopDate);
void loadMovieAvailable(const std::string& currentDate);
void loadShowtimesForMovie(int movieId);

int main() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::string role = LoginForm::login(username, password);

    if (role == "Admin") {
        //them sua xoa
    } else if (role == "Normal User") {
        std::string currentDate = getCurrentDate();
        std::cout << "Welcome to the movie booking system!\n";
        loadMovieAvailable(currentDate);

        int movieId;
        std::cout << "Enter Movie ID to continue: ";
        std::cin >> movieId;
        loadShowtimesForMovie(movieId);


    } else {
        std::cout << "Login failed. Please try again." << std::endl;
    }

    return 0;
}

std::string getCurrentDate() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

void loadMovieAvailable(const std::string& currentDate) {
    std::vector<Movie> movies = Movie::getAll();
    bool found = false;
    
    std::cout << "Available movies for " << currentDate << ":\n";
    
    for (const auto& movie : movies) {
        if (isDateInRange(currentDate, movie.getShowStartDate(), movie.getShowStopDate())) {
            std::cout << "- Movie ID: " << movie.getId() << "\n";
            std::cout << "  Name: " << movie.getName() << "\n";
            std::cout << "  Duration: " << movie.getDuration() << "\n";
            std::cout << "  Show period: " << movie.getShowStartDate() << " to " << movie.getShowStopDate() << "\n\n";
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "No movies available for today.\n";
    }
}

bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& stopDate) {
    return date >= startDate && date <= stopDate;
}


void loadShowtimesForMovie(int movieId) {
    std::vector<ShowTime> showtimes = ShowTime::getAll();
    bool found = false;
    
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
}