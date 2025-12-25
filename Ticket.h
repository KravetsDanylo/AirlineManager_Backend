#pragma once
#include <memory>
#include <string>
#include "Enums.h"
#include "Passenger.h"

class Ticket {
private:
    static int globalTicketCounter;
    int id;
    int flightId;
    double price;
    SeatClass seatClass;
    std::shared_ptr<Passenger> passenger;

public:
    Ticket(int flightId, std::shared_ptr<Passenger> pass, double price, SeatClass sc);
    Ticket(int id, int flightId, std::shared_ptr<Passenger> pass, double price, SeatClass sc);

    int getId() const;
    int getFlightId() const;
    double getPrice() const;
    SeatClass getSeatClass() const;
    std::string getSeatClassStr() const;
    std::shared_ptr<Passenger> getPassenger() const;

    static void updateIdCounter(int maxId);
};
