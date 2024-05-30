#include "interface.hpp"

using namespace std;
Interface::Interface(vector<Location> locs) : locs(locs)
{
}
void Interface::check_duplicate_name(string name)
{
    for (int i = 0; i < members.size(); i++)
    {
        if (members[i]->get_name() == name)
            throw Import_except("BAD REQUEST\n");
    }
}
void Interface::signup(string name, string role)
{
    check_duplicate_name(name);
    if (role == "driver")
    {
        Driver *new_drv = new Driver(name);
        members.push_back(new_drv);
    }
    else if (role == "passenger")
        members.push_back(new Passenger(name));
    else
        throw Import_except("BAD REQUEST\n");
    cout << "OK\n";
}
int Interface::find_member_index(string name)
{
    for (int i = 0; i < members.size(); i++)
        if (members[i]->get_name() == name)
            return i;
    throw Import_except("Not Found\n");
}
int Interface::find_location_index(string loc_name)
{
    for (int i = 0; i < locs.size(); i++)
        if (locs[i].get_name() == loc_name)
            return i;
    throw Import_except("Not Found\n");
}
void Interface::check_member_exist(string username)
{
    for (int j = 0; j < members.size(); j++)
        if (members[j]->get_name() == username)
            return;
    throw Import_except("NOT FOUND\n");
}
void Interface::add_new_trip(string passenger_name, int origin_index, int destination_index)
{
    check_member_exist(passenger_name);
    int index = find_member_index(passenger_name);
    members[index]->without_active_trip_passenger();
    trips.push_back(Trip(&locs[origin_index], &locs[destination_index], trips.size() + 1, (Passenger *)members[index]));
    members[index]->active_a_trip(&trips[trips.size() - 1]);
    cout << trips.size() << endl;
}
void Interface::show_trips(string name)
{
    members[find_member_index(name)]->check_not_being_passenger();
    int num_of_deleted = 0;
    for (int i = 0; i < trips.size(); i++)
    {
        if (trips[i].get_status() == DELETE)
        {
            num_of_deleted++;
            continue;
        }
        trips[i].show_info();
    }
    if (num_of_deleted == trips.size() || trips.size() == 0)
        throw Import_except("EMPTY\n");
}
void Interface::show_requested_trip_info(string name, int id)
{
    members[find_member_index(name)]->check_not_being_passenger();
    if (trips[id - 1].get_status() == DELETE)
        throw Import_except("Not Found\n");
    trips[id - 1].show_info();
}
void Interface::delete_a_trip(string passenger_name, int trip_id)
{
    members[find_member_index(passenger_name)]->check_not_being_driver();
    if (trip_id > trips.size() || trips[trip_id - 1].get_status() == DELETE)
        throw Import_except("Not Found\n");
    trips[trip_id - 1].clear(passenger_name);
    cout << "OK\n";
}
void Interface::accept_a_trip_by_driver(string driver_name, int trip_id)
{
    if (trip_id > trips.size() || trips[trip_id - 1].get_status() == DELETE)
        throw Import_except("Not Found\n");
    members[find_member_index(driver_name)]->without_active_trip_driver();
    trips[trip_id - 1].trip_accepted();
    members[find_member_index(driver_name)]->accept_a_trip(&trips[trip_id - 1]);
    cout << "OK\n";
}
void Interface::finish_a_trip(string driver_name, int trip_id)
{
    if (trip_id > trips.size() || trips[trip_id - 1].get_status() == DELETE)
        throw Import_except("Not Found\n");
    members[find_member_index(driver_name)]->finish_current_trip(trip_id);
    cout << "OK\n";
}