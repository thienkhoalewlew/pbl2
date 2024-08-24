#pragma once
#include <string>
#include<vector>

class ShowTime{
    private:
        int id;
        int movieId;
        int roomId;
        std::string showTime;
        std::string showDate;

    public:
        ShowTime(int id, int movieId, int roomId, std::string showTime, std::string showDate);

        int getId() const;
        int getMovieId() const;
        int getRoomId() const;
        std::string getShowTime() const;
        std::string getShowDate() const;

        static void save(const ShowTime& ShowTime);
        static void update(const ShowTime& ShowTime);
        static ShowTime getById(int id);
        static std::vector<ShowTime> getAll();

        std::string toString() const;
        static ShowTime fromString(const std::string& str);
};