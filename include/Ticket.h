#pragma once
#include <vector>
#include <string>

class Ticket{
    private:
        int id;
        int showTimeId;
        int seatId;

    public:
        Ticket(int id, int showTimeId, int seatId);

        int getId() const;
        int getShowTimeId() const;
        int getSeatId() const;

        static void save(const Ticket& Ticket);
        static void update(const Ticket& Ticket);
        static Ticket getById(int id);
        static std::vector<Ticket> getAll();

        std::string toString() const;
        static Ticket fromString(const std::string& str);
};