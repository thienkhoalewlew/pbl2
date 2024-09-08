#pragma once
#include <string>
#include <vector>

class Movie {
    private:
        std::string id;  
        std::string name; 
        std::string duration;
        std::string showStartDate;
        std::string showStopDate;

    public:
        Movie(std::string id, std::string name, std::string duration, std::string showStartDate, std::string showStopDate);

        std::string getId() const; 
        std::string getName() const; 
        std::string getDuration() const;           
        std::string getShowStartDate() const;
        std::string getShowStopDate() const;

        static Movie getbyId(const std::string& id); 
        static std::vector<Movie> getAll();
        static void save(const Movie& Movie);
        static void update(const Movie& Movie);
        static void remove(const std::string& id);  

        std::string toString() const;
        static Movie fromString(const std::string& str);
};