#ifndef __PERSON_H__
#define __PERSON_H__
#include <string>
#include <vector>
#include "exceptions.hpp"

class Trip;
class Person
{
public:
    Person(std::string name);
    std::string get_name() { return name; }

    virtual void check_not_being_passenger() = 0;
    virtual void check_not_being_driver() = 0;
    virtual void without_active_trip_passenger() = 0;
    virtual void without_active_trip_driver() = 0;
    virtual void active_a_trip(Trip *trip) = 0;
    virtual void delete_active_trip() = 0;
    virtual void accept_a_trip(int trip_id) = 0;
    virtual void finish_current_trip(int id) = 0;

protected:
    std::string name;
    int num_of_trips_pass;
};

#endif