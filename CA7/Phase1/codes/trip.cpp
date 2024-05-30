#include "trip.hpp"
using namespace std;
Trip::Trip(Location *origin, Location *destination, int id, Passenger *passenger) : origin(origin), destination(destination), passenger(passenger), id(id)
{
    status = WAITING;
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
    show_status();
}
void Trip::clear(string passenger_name)
{
    if (status == DELETE)
        throw Import_except("Not Found\n");
    if (status == TRAVELLING || status == FINISHED || passenger->get_name() != passenger_name)
        throw Import_except("Bad Request\n");
    status = DELETE;
}
void Trip::trip_accepted()
{
    if (status != WAITING)
        throw Import_except("Bad Request\n");
    status = TRAVELLING;
}
void Trip::trip_finish()
{
    status = FINISHED;
}