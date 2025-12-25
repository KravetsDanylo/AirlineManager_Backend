#include<iostream>
#include "Enums.h"
#include "Passenger.h"
#include "Ticket.h"
#include "Flight.h"
int main() {
	std::shared_ptr<Passenger> p1 = std::make_shared<Passenger>("danylo", "21371", "fdslkf2133", "ff11212");
	std::shared_ptr<Passenger> p2 = std::make_shared<Passenger>("ivan", "97979", "fyweqiu=789", "xx8999");
	std::vector<Passenger> passengers;
	passengers.push_back(*p1);
	passengers.push_back(*p2);
	auto it = passengers.begin();
	for (; it != passengers.end(); it++) {
		std::cout << (*it).toString();
	}
	return 0;
}