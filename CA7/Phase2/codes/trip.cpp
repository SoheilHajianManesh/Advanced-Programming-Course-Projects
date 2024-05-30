#include "trip.hpp"
using namespace std;
Trip::Trip(Location *origin, Location *destination, int id, Passenger *passenger, bool in_hurry) : origin(origin), destination(destination), passenger(passenger), id(id), in_hurry(in_hurry)
{
    status = WAITING;
    calculate_price();
}
void Trip::show_status()
{
    if (status == 0)
        cout << "waiting" << endl;
    else if (status == 1)
        cout << "traveling" << endl;
    else if (status == 2)
        cout << "finished" << endl;
}
void Trip::show_info()
{
    cout << id << ' ' << passenger->get_name() << ' ' << origin->get_name() << ' ' << destination->get_name() << ' ';
    printf("%.2lf ", price);
    show_status();
}
void Trip::clear(string passenger_name)
{
    if (status == DELETE)
        throw Import_except(NOT_EXIST_MASSAGE);
    if (status == TRAVELLING || status == FINISHED || passenger->get_name() != passenger_name)
        throw Import_except(WRONG_DEMAND_MASSAGE);
    status = DELETE;
}
void Trip::trip_accepted()
{
    if (status != WAITING)
        throw Import_except(WRONG_DEMAND_MASSAGE);
    status = TRAVELLING;
}
void Trip::trip_finish()
{
    status = FINISHED;
}
void Trip::calculate_price()
{
    double dist = ONE_DEGREE_IN_KILOMETER * (sqrt(
                                                pow(destination->get_latitude() - origin->get_latitude(), 2) +
                                                pow(destination->get_longtitude() - origin->get_longtitude(), 2)));
    price = dist * (origin->get_traffic() + destination->get_traffic()) * ENTRY_FEE;
    if (in_hurry)
        price *= IN_HURRY_RATE;
}