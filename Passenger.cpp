#include "Passenger.h"
#include <sstream>

int Passenger::globalIdCounter = 1;
Passenger::Passenger(std::string name, std::string pass, std::string ph, std::string mail, std::string address, std::string birthDate) 
    : name(name), passportNumber(pass), phoneNumber(ph), email(mail), address(address), birthDate(birthDate) {
	this->id = globalIdCounter++;
}

Passenger::Passenger(int i, std::string n, std::string pass, std::string ph, std::string mail, std::string address, std::string birthDate)
    : id(i), name(n), passportNumber(pass), phoneNumber(ph), email(mail), address(address), birthDate(birthDate) {
    if (i >= globalIdCounter) {
        globalIdCounter = i + 1;
    }
}
int Passenger::getId() const { return id; } 
std::string Passenger::getName() const { return name; }
std::string Passenger::getPassport() const { return passportNumber; }
std::string Passenger::getPhone() const { return phoneNumber; }
std::string Passenger::getEmail() const { return email; }
std::string Passenger::getAddress() const { return address; }
std::string Passenger::getBirthDate() const { return birthDate; }

std::string Passenger::toString() const {
    std::stringstream ss;
    ss << "ID: " << id << " | " << name << " (" << passportNumber << ")";
    return ss.str();
}

void Passenger::updateIdCounter(int maxId) {
    if (maxId >= globalIdCounter) {
        globalIdCounter = maxId + 1;
    }
}