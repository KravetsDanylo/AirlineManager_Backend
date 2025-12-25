#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Ticket.h"

class Flight {
private:
    int id;
    std::string destination;
    std::string dateTime;
    int durationMinutes;
    int maxSeats;
    std::vector<std::shared_ptr<Ticket>> tickets;

public:
    Flight(int id, std::string dest, std::string date, int duration, int maxSeats);

    int getId() const;
    std::string getDestination() const;
    std::string getDateTime() const;
    int getDuration() const;
    int getMaxSeats() const;
    int getBookedSeats() const;

    bool addTicket(std::shared_ptr<Ticket> ticket);
    bool removeTicket(int ticketId);

    std::string toString() const;

    const std::vector<std::shared_ptr<Ticket>>& getTickets() const;
};