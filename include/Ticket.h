#pragma once
#include <vector>
#include <string>

class Ticket {
    private:
        std::string id;
        std::string showTimeId;
        std::vector<std::string> seatIds; 
        double price;

    public:
        Ticket(const std::string& id, const std::string& showTimeId, const std::vector<std::string>& seatIds, double price);

        std::string getId() const;
        std::string getShowTimeId() const;
        std::vector<std::string> getSeatIds() const; 
        double getPrice() const;
        static std::vector<Ticket> getByShowTimeId(const std::string& showTimeId);

        static void save(const Ticket& ticket);
        static void update(const Ticket& ticket);
        static Ticket getById(const std::string& id);
        static void remove(const std::string& id);
        static std::vector<Ticket> getAll();

        std::string toString() const;
        static Ticket fromString(const std::string& str);
};
