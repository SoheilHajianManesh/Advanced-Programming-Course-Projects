#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "person.hpp"
#include "trip.hpp"
#include "const.hpp"
#include "exceptions.hpp"

class Trip;
class Driver : public Person
{
public:
    Driver(std::string _name);

    virtual void check_not_being_passenger();
    virtual void check_not_being_driver();
    virtual void without_active_trip_passenger();
    virtual void without_active_trip_driver();
    virtual void active_a_trip(Trip *trip);
    virtual void delete_active_trip();
    virtual void accept_a_trip(Trip *trip);
    virtual void finish_current_trip(int id);

private:
    Trip *current_trip;
};

#endif