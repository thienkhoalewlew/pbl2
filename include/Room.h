#pragma once
#include<vector>
#include<string>

class Room{
    private:
        int id;
        int capacity;
        
    public:
        Room(int id, int capacity);

        int getId() const;
        int getCapacity() const;

        static void save(const Room& Room);
        static void update(const Room& room);
        static Room getById(int id);
        static std::vector<Room> getAll();

        std::string toString() const;
        static Room fromString(const std::string& str); 
};