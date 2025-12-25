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
    std::string address;    
    std::string birthDate;

public:
    Passenger(std::string name, std::string passport, std::string phone, std::string email, std::string address, std::string birthDate);
    Passenger(int id, std::string name, std::string passport, std::string phone, std::string email, std::string address, std::string birthDate);

    int getId() const;
    std::string getName() const;
    std::string getPassport() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getAddress() const;
    std::string getBirthDate() const;

    std::string toString() const;
    static void updateIdCounter(int maxId);
};
