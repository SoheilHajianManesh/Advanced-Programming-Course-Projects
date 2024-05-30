#ifndef __TRIP_H__
#define __TRIP_H__
#include <iostream>
#include "location.hpp"
#include "const.hpp"
#include "person.hpp"
#include "passenger.hpp"
#include "driver.hpp"
#include "exceptions.hpp"

class Passenger;

class Trip
{
public:
    Trip(Location *_origin, Location *_destination, int _id, Passenger *_passenger);
    void show_info();
    void clear(std::string passenger_name);
    void trip_accepted();
    void trip_finish();

    int get_id() { return id; }
    int get_status() { return status; }

private:
    void show_status();
    Location *origin;
    Location *destination;
    Passenger *passenger;
    int status;
    int id;
};

#endif