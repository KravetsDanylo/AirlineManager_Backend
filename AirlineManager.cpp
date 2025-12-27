#include "AirlineManager.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>



int AirlineManager::createPassenger(std::string name, std::string passport, std::string phone, std::string email, std::string address, std::string birthDate) {
    if (name.empty() || passport.empty()) {
        throw std::invalid_argument("Name and passport cannot be empty!");
    }
    auto p = std::make_shared<Passenger>(name, passport, phone, email, address, birthDate);
    passengers.push_back(p);
    return p->getId(); 
}

std::vector<std::shared_ptr<Passenger>> AirlineManager::getAllPassengers() const {
    return passengers;
}

std::shared_ptr<Passenger> AirlineManager::getPassengerById(int id) {
    for (auto& p : passengers) {
        if (p->getId() == id) return p;
    }
    return nullptr;
}

void AirlineManager::createFlight(int id, std::string dest, std::string date, int duration, int seats) {
    if (duration <= 0 || seats <= 0) {
        throw std::invalid_argument("Duration and seats must be positive integers!");
    }
    if (getFlightById(id) != nullptr) {
        throw std::invalid_argument("Flight with this ID already exists!");
    }
    auto f = std::make_shared<Flight>(id, dest, date, duration, seats);
    flights.push_back(f);
}
bool AirlineManager::cancelFlight(int flightId) {
   
    auto flightIt = std::find_if(flights.begin(), flights.end(),
        [flightId](const std::shared_ptr<Flight>& f) {
            return f->getId() == flightId;
        });

    if (flightIt == flights.end()) {
        return false; 
    }

    allTickets.erase(
        std::remove_if(allTickets.begin(), allTickets.end(),
            [flightId](const std::shared_ptr<Ticket>& t) {
                return t->getFlightId() == flightId;
            }),
        allTickets.end()
    );

    flights.erase(flightIt);

    return true;
}

std::vector<std::shared_ptr<Flight>> AirlineManager::getAllFlights() const {
    return flights;
}

std::shared_ptr<Flight> AirlineManager::getFlightById(int id) {
    for (auto& f : flights) {
        if (f->getId() == id) return f;
    }
    return nullptr;
}

void AirlineManager::bookTicket(int flightId, int passengerId, double price, SeatClass sc) {
    if (price < 0) {
        throw std::invalid_argument("Price cannot be negative!");
    }
    auto flight = getFlightById(flightId);
    if (!flight) {
        throw std::runtime_error("Flight not found!"); 
    }
    auto passenger = getPassengerById(passengerId);
    if (!passenger) {
        throw std::runtime_error("Passenger not found!");
    }
    if (flight->getBookedSeats() >= flight->getMaxSeats()) {
        throw std::runtime_error("No seats available on this flight!");
    }

    const auto& flightTickets = flight->getTickets();

    for (const auto& t : flightTickets) {
        
        if (t->getPassenger()->getId() == passengerId) {
             throw std::runtime_error("Passenger with this ID is already booked on this flight!");
        }
    }

    auto ticket = std::make_shared<Ticket>(flightId, passenger, price, sc);
    allTickets.push_back(ticket);
    flight->addTicket(ticket);
}

bool AirlineManager::cancelTicket(int ticketId) {
    auto it = std::find_if(allTickets.begin(), allTickets.end(),
        [ticketId](const std::shared_ptr<Ticket>& t) {
            return t->getId() == ticketId;
        });

    if (it == allTickets.end()) {
        return false; 
    }

    std::shared_ptr<Ticket> ticketToRemove = *it;
    int flightId = ticketToRemove->getFlightId();

    auto flight = getFlightById(flightId);
    if (flight) {
        flight->removeTicket(ticketId);
    }

    allTickets.erase(it);
    return true;
}

void AirlineManager::sortFlights(SortCriteria criteria) {
    std::sort(flights.begin(), flights.end(),
        [criteria](const std::shared_ptr<Flight>& a, const std::shared_ptr<Flight>& b) {
            switch (criteria) {
            case SortCriteria::BY_DURATION:
                return a->getDuration() < b->getDuration();
            case SortCriteria::BY_DESTINATION:
                return a->getDestination() < b->getDestination();
            case SortCriteria::BY_MAX_SEATS:
                return a->getMaxSeats() < b->getMaxSeats();
            default:
                return false;
            }
        });
}

std::vector<std::shared_ptr<Flight>> AirlineManager::searchFlights(std::string destination) {
    std::vector<std::shared_ptr<Flight>> result;
    for (const auto& f : flights) {
        
        if (f->getDestination().find(destination) != std::string::npos) {
            result.push_back(f);
        }
    }
    return result;
}

void AirlineManager::saveData() const {
    
    std::ofstream pFile("passengers.csv");
    if (!pFile.is_open()) {
        throw std::runtime_error("Critical Error: Failed to open passengers.csv for writing. Check file permissions.");
    }

    for (const auto& p : passengers) {
        pFile << p->getId() << "|" << p->getName() << "|" << p->getPassport() << "|"
            << p->getPhone() << "|" << p->getEmail() << "|"
            << p->getAddress() << "|" << p->getBirthDate() << "\n";
    }
    pFile.close();

    std::ofstream fFile("flights.csv");
    if (!fFile.is_open()) {
        throw std::runtime_error("Critical Error: Failed to open flights.csv for writing.");
    }

    for (const auto& f : flights) {
        fFile << f->getId() << "|" << f->getDestination() << "|" << f->getDateTime() << "|"
            << f->getDuration() << "|" << f->getMaxSeats() << "\n";
    }
    fFile.close();

    std::ofstream tFile("tickets.csv");
    if (!tFile.is_open()) {
        throw std::runtime_error("Critical Error: Failed to open tickets.csv for writing.");
    }

    for (const auto& t : allTickets) {
        tFile << t->getId() << "|" << t->getFlightId() << "|" << t->getPassenger()->getId() << "|"
            << t->getPrice() << "|" << static_cast<int>(t->getSeatClass()) << "\n";
    }
    tFile.close();
}

void AirlineManager::loadData() {
    passengers.clear();
    flights.clear();
    allTickets.clear();

    std::string line;

    std::ifstream pFile("passengers.csv");
    if (pFile.is_open()) {
        int maxPId = 0;
        while (std::getline(pFile, line)) {
            if (line.empty()) continue; 
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> row;
            while (std::getline(ss, segment, '|')) row.push_back(segment);

            if (row.size() >= 7) {
                try {
                    int id = std::stoi(row[0]); 
                    auto p = std::make_shared<Passenger>(id, row[1], row[2], row[3], row[4], row[5], row[6]);
                    passengers.push_back(p);
                    if (id > maxPId) maxPId = id;
                }
                catch (...) {
                    continue; 
                }
            }
        }
        Passenger::updateIdCounter(maxPId);
        pFile.close();
    }

    
    std::ifstream fFile("flights.csv");
    if (fFile.is_open()) {
        while (std::getline(fFile, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> row;
            while (std::getline(ss, segment, '|')) row.push_back(segment);

            if (row.size() >= 5) {
                try {
                    auto f = std::make_shared<Flight>(std::stoi(row[0]), row[1], row[2], std::stoi(row[3]), std::stoi(row[4]));
                    flights.push_back(f);
                }
                catch (...) {
                    continue;
                }
            }
        }
        fFile.close();
    }

    
    std::ifstream tFile("tickets.csv");
    if (tFile.is_open()) {
        int maxTId = 0;
        while (std::getline(tFile, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> row;
            while (std::getline(ss, segment, '|')) row.push_back(segment);

            if (row.size() >= 5) {
                try {
                    int tId = std::stoi(row[0]);
                    int fId = std::stoi(row[1]);
                    int pId = std::stoi(row[2]);
                    double price = std::stod(row[3]);
                    int seatClassInt = std::stoi(row[4]);

                    auto flight = getFlightById(fId);
                    auto passenger = getPassengerById(pId);

                    if (flight && passenger) {
                        SeatClass sc = static_cast<SeatClass>(seatClassInt);
                        auto t = std::make_shared<Ticket>(tId, fId, passenger, price, sc);
                        allTickets.push_back(t);
                        flight->addTicket(t);
                        if (tId > maxTId) maxTId = tId;
                    }
                }
                catch (...) {
                    continue;
                }
            }
        }
        Ticket::updateIdCounter(maxTId);
        tFile.close();
    }
}