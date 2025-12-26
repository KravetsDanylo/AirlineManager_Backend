#include <pybind11/pybind11.h>
#include <pybind11/stl.h> 
#include "AirlineManager.h"
#include "Passenger.h"
#include "Flight.h"
#include "Ticket.h"
#include "Enums.h"

namespace py = pybind11;

PYBIND11_MODULE(airline_backend, m) {
    m.doc() = "Airline Manager C++ Backend";

  
    py::enum_<SeatClass>(m, "SeatClass")
        .value("ECONOMY", SeatClass::ECONOMY)
        .value("BUSINESS", SeatClass::BUSINESS)
        .value("FIRST_CLASS", SeatClass::FIRST_CLASS)
        .export_values();

    py::enum_<SortCriteria>(m, "SortCriteria")
        .value("BY_MAX_SEATS", SortCriteria::BY_MAX_SEATS)
        .value("BY_DURATION", SortCriteria::BY_DURATION)
        .value("BY_DESTINATION", SortCriteria::BY_DESTINATION)
        .export_values();

    
    py::class_<Passenger, std::shared_ptr<Passenger>>(m, "Passenger")
        .def("getId", &Passenger::getId)
        .def("getName", &Passenger::getName)
        .def("getPassport", &Passenger::getPassport)
        .def("getPhone", &Passenger::getPhone)
        .def("getEmail", &Passenger::getEmail)
        .def("getAddress", &Passenger::getAddress)
        .def("getBirthDate", &Passenger::getBirthDate)
        .def("__repr__", &Passenger::toString);

    
    py::class_<Ticket, std::shared_ptr<Ticket>>(m, "Ticket")
        .def("getId", &Ticket::getId)
        .def("getFlightId", &Ticket::getFlightId)
        .def("getPrice", &Ticket::getPrice)
        .def("getSeatClass", &Ticket::getSeatClass)
        .def("getSeatClassStr", &Ticket::getSeatClassStr)
        .def("getPassenger", &Ticket::getPassenger);

   
    py::class_<Flight, std::shared_ptr<Flight>>(m, "Flight")
        .def("getId", &Flight::getId)
        .def("getDestination", &Flight::getDestination)
        .def("getDateTime", &Flight::getDateTime)
        .def("getDuration", &Flight::getDuration)
        .def("getMaxSeats", &Flight::getMaxSeats)
        .def("getBookedSeats", &Flight::getBookedSeats)
        .def("getTickets", &Flight::getTickets)
        .def("__repr__", &Flight::toString);

 
    py::class_<AirlineManager>(m, "AirlineManager")
        .def(py::init<>())

        .def("createPassenger", &AirlineManager::createPassenger)
        .def("getAllPassengers", &AirlineManager::getAllPassengers)
        .def("getPassengerById", &AirlineManager::getPassengerById)
        .def("createFlight", &AirlineManager::createFlight)
        .def("cancelFlight", &AirlineManager::cancelFlight)
        .def("getAllFlights", &AirlineManager::getAllFlights)
        .def("getFlightById", &AirlineManager::getFlightById)
        .def("bookTicket", &AirlineManager::bookTicket)
        .def("cancelTicket", &AirlineManager::cancelTicket)
        .def("sortFlights", &AirlineManager::sortFlights)
        .def("searchFlights", &AirlineManager::searchFlights)
        .def("saveData", &AirlineManager::saveData)
        .def("loadData", &AirlineManager::loadData);
}