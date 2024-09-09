#pragma once
#include <string>
#include <vector>

class ShowTime {
    private:
        std::string id;
        std::string movieId;
        std::string roomId;
        std::string showTime;
        std::string showDate;

    public:
        ShowTime(std::string id, std::string movieId, std::string roomId, std::string showTime, std::string showDate);

        std::string getId() const;
        std::string getMovieId() const;
        std::string getRoomId() const;
        std::string getShowTime() const;
        std::string getShowDate() const;
        static std::vector<ShowTime> getByMovieId(const std::string& movieId);

        static void save(const ShowTime& ShowTime);
        static void update(const ShowTime& ShowTime);
        static void remove(const std::string& id);
        static ShowTime getById(const std::string& id);
        static std::vector<ShowTime> getAll();

        std::string toString() const;
        static ShowTime fromString(const std::string& str);
};