#pragma once
#include<vector>
#include<string>

class Room {
    private:
        std::string id;  
        int capacity;
        
    public:
        Room(std::string id, int capacity);  

        std::string getId() const; 
        int getCapacity() const;

        static void save(const Room& Room);
        static void update(const Room& room);
        static void remove(const std::string& id);
        static Room getById(const std::string& id); 
        static std::vector<Room> getAll();

        std::string toString() const;
        static Room fromString(const std::string& str); 
};