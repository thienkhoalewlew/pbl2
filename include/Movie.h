#pragma once
#include <string>
#include <vector>

class Movie {
    private:
        int id;
        std::string name;  
        std::string duration;
        std::string showStartDate;
        std::string showStopDate;

    public:
        Movie(int id, std::string name, std::string duration, std::string showStartDate, std::string showStopDate);

        int getId() const;
        std::string getName() const; 
        std::string getDuration() const;           
        std::string getShowStartDate() const;
        std::string getShowStopDate() const;

        static Movie getbyId(int id);
        static std::vector<Movie> getAll();
        static void save(const Movie& Movie);
        static void update(const Movie& Movie);

        std::string toString() const;
        static Movie fromString(const std::string& str);
};