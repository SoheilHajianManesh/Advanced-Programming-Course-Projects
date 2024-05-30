#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include "const.hpp"
#include "person.hpp"
#include "trip.hpp"
#include "exceptions.hpp"

class Trip;

class Passenger : public Person
{
public:
    Passenger(std::string _name);

    virtual void check_not_being_passenger();
    virtual void check_not_being_driver();
    virtual void without_active_trip_passenger();
    virtual void without_active_trip_driver();
    virtual void active_a_trip(Trip *trip);
    virtual void delete_active_trip();
    virtual void accept_a_trip(int trip_id);
    virtual void finish_current_trip(int id);

private:
    Trip *taken_trip;
};

#endif