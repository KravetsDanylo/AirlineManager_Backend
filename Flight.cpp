#include "Flight.h"
#include <algorithm>
#include <sstream>
Flight::Flight(int id, std::string origin, std::string dest, std::string date, int duration, int maxSeats)
    : id(id), origin(origin), destination(dest), dateTime(date), durationMinutes(duration), maxSeats(maxSeats) { }

int Flight::getId() const { return id; }
std::string Flight::getOrigin() const { return origin; }
std::string Flight::getDestination() const { return destination; }
std::string Flight::getDateTime() const { return dateTime; }
int Flight::getDuration() const { return durationMinutes; }
int Flight::getMaxSeats() const { return maxSeats; }
int Flight::getBookedSeats() const { return tickets.size(); }

bool Flight::addTicket(std::shared_ptr<Ticket> ticket) {
    if (getBookedSeats() < getMaxSeats()) {
        tickets.push_back(ticket);
        return true;
    }
    return false;
}
bool Flight::removeTicket(int ticketId) {
    auto it = std::remove_if(tickets.begin(), tickets.end(), [ticketId](const std::shared_ptr<Ticket>& t) {return t->getId() == ticketId; });
    if (it != tickets.end()) {
        tickets.erase(it, tickets.end());
        return true;
    }
    return false;
}
std::string Flight::toString() const {
    std::stringstream ss;
    ss << destination << " (" << dateTime << ") - Seats: "
        << getBookedSeats() << "/" << maxSeats;
    return ss.str();
} 
const std::vector<std::shared_ptr<Ticket>>& Flight::getTickets() const {
    return tickets;
}