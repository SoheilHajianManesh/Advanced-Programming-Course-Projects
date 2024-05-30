#include "driver.hpp"
using namespace std;

Driver::Driver(string _name) : Person(_name)
{
}
void Driver::check_not_being_passenger() {}
void Driver::check_not_being_driver()
{
    throw Import_except(INACCESSIBILITY_MASSAGE);
}
void Driver::without_active_trip_passenger()
{
    throw Import_except(INACCESSIBILITY_MASSAGE);
}
void Driver::without_active_trip_driver()
{
    if (num_of_trips_pass != 0)
        if (current_trip_status == TRAVELLING)
            throw Import_except(WRONG_DEMAND_MASSAGE);
}
void Driver::active_a_trip(Trip *trip)
{
    throw Import_except(INACCESSIBILITY_MASSAGE);
}
void Driver::delete_active_trip()
{
    throw Import_except(INACCESSIBILITY_MASSAGE);
}
void Driver::accept_a_trip(int trip_id)
{
    current_trip_status = TRAVELLING;
    current_trip_id = trip_id;
    num_of_trips_pass++;
}
void Driver::finish_current_trip(int id)
{
    if (current_trip_id != id)
        throw Import_except(INACCESSIBILITY_MASSAGE);
    if (current_trip_status == FINISHED)
        throw Import_except(WRONG_DEMAND_MASSAGE);
    current_trip_status = FINISHED;
}
