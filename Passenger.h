#pragma once
#include <string>

class Passenger {
private:
    static int globalIdCounter;
    int id;
    std::string name;
    std::string passportNumber;
    std::string phoneNumber;
    std::string email;

public:
    Passenger(std::string name, std::string passport, std::string phone, std::string email);
    Passenger(int id, std::string name, std::string passport, std::string phone, std::string email);

    int getId() const;
    std::string getName() const;
    std::string getPassport() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string toString() const;
    static void updateIdCounter(int maxId);
};
