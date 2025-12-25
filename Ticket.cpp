#include "Ticket.h"

int Ticket::globalTicketCounter = 10000;

Ticket::Ticket(int flightId, std::shared_ptr<Passenger> pass, double price, SeatClass sc) : flightId(flightId), passenger(pass), price(price), seatClass(sc) {
	this->id = globalTicketCounter++;
}
Ticket::Ticket(int tId, int fId, std::shared_ptr<Passenger> pass, double pr, SeatClass sc)
    : id(tId), flightId(fId), passenger(pass), price(pr), seatClass(sc)
{
    if (tId >= globalTicketCounter) globalTicketCounter = tId + 1;
}
int Ticket::getId() const { return id; }
int Ticket::getFlightId() const { return flightId; }
double Ticket::getPrice() const { return price; }
std::shared_ptr<Passenger> Ticket::getPassenger() const { return passenger; }
std::string Ticket::getSeatClassStr() const {
    switch (seatClass) {
    case SeatClass::ECONOMY: return "Economy"; 
    case SeatClass::BUSINESS: return "Business";
    case SeatClass::FIRST_CLASS: return "First Class";
    default: return "Unknown";
    }
}
void Ticket::updateIdCounter(int maxId) {
    if (maxId >= globalTicketCounter) globalTicketCounter = maxId + 1;
}