#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Flight.h"
#include "Passenger.h"
#include "Ticket.h"
#include "Enums.h"

class AirlineManager {
private:
    std::vector<std::shared_ptr<Flight>> flights;
    std::vector<std::shared_ptr<Passenger>> passengers;
    std::vector<std::shared_ptr<Ticket>> allTickets;

public:
    
    int createPassenger(std::string name, std::string passport, std::string phone, std::string email, std::string address, std::string birthDate);
    std::vector<std::shared_ptr<Passenger>> getAllPassengers() const;
    std::shared_ptr<Passenger> getPassengerById(int id);

    
    void createFlight(int id, std::string dest, std::string date, int duration, int seats);
    bool cancelFlight(int flightId);
    std::vector<std::shared_ptr<Flight>> getAllFlights() const;
    std::shared_ptr<Flight> getFlightById(int id);

    
    void bookTicket(int flightId, int passengerId, double price, SeatClass sc);
    bool cancelTicket(int ticketId);
    std::vector<std::shared_ptr<Ticket>> getAllTickets() const;

    void sortFlights(SortCriteria criteria);
    std::vector<std::shared_ptr<Flight>> searchFlights(std::string destination);

    
    void saveData() const;
    void loadData();
};