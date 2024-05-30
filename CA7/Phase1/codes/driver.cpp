#include "driver.hpp"
using namespace std;

Driver::Driver(string _name) : Person(_name)
{
}
void Driver::check_not_being_passenger() {}
void Driver::check_not_being_driver()
{
    throw Import_except("Permition Denied\n");
}
void Driver::without_active_trip_passenger()
{
    throw Import_except("Permition denied\n");
}
void Driver::without_active_trip_driver()
{
    if (num_of_trips_pass != 0)
        if (current_trip->get_status() == TRAVELLING)
            throw Import_except("Bad Request\n");
}
void Driver::active_a_trip(Trip *trip)
{
    throw Import_except("Permition Denied\n");
}
void Driver::delete_active_trip()
{
    throw Import_except("Permition Denied\n");
}
void Driver::accept_a_trip(Trip *trip)
{
    current_trip = trip;
    num_of_trips_pass++;
}
void Driver::finish_current_trip(int id)
{
    if (current_trip->get_id() != id)
        throw Import_except("Permition Denied\n");
    if (current_trip->get_status() == FINISHED)
        throw Import_except("Bad Request\n");
    current_trip->trip_finish();
}
