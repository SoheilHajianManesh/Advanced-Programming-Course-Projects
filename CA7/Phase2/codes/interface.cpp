#include "interface.hpp"

using namespace std;
Interface::Interface(vector<Location> locs) : locs(locs)
{
}
void Interface::check_duplicate_name(string name)
{
    for (int i = 0; i < members.size(); i++)
        if (members[i]->get_name() == name)
            throw Import_except(WRONG_DEMAND_MASSAGE);
}
void Interface::sort_trips_by_id()
{
    if (trips.size() == 0)
        return;
    for (int i = 0; i < trips.size() - 1; i++)
        for (int j = i + 1; j < trips.size(); j++)
            if (trips[i].get_id() > trips[j].get_id())
                iter_swap(trips.begin() + i, trips.begin() + j);
}
void Interface::sort_trips_by_cost()
{
    if (trips.size() == 0)
        return;
    for (int i = 0; i < trips.size() - 1; i++)
        for (int j = i + 1; j < trips.size(); j++)
            if (trips[i].get_price() < trips[j].get_price())
                iter_swap(trips.begin() + i, trips.begin() + j);
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
        throw Import_except(WRONG_DEMAND_MASSAGE);
    cout << SUCCESSFUL_MASSAGE;
}
int Interface::find_trip_index(int id)
{
    for (int i = 0; i < trips.size(); i++)
        if (trips[i].get_id() == id)
            return i;
    throw Import_except(NOT_EXIST_MASSAGE);
}
int Interface::find_member_index(string name)
{
    for (int i = 0; i < members.size(); i++)
        if (members[i]->get_name() == name)
            return i;
    throw Import_except(NOT_EXIST_MASSAGE);
}
int Interface::find_location_index(string loc_name)
{
    for (int i = 0; i < locs.size(); i++)
        if (locs[i].get_name() == loc_name)
            return i;
    throw Import_except(NOT_EXIST_MASSAGE);
}
void Interface::check_member_exist(string username)
{
    for (int j = 0; j < members.size(); j++)
        if (members[j]->get_name() == username)
            return;
    throw Import_except(NOT_EXIST_MASSAGE);
}
void Interface::add_new_trip(string passenger_name, int origin_index, int destination_index, bool in_hurry)
{
    check_member_exist(passenger_name);
    int index = find_member_index(passenger_name);
    members[index]->without_active_trip_passenger();
    trips.push_back(Trip(&locs[origin_index], &locs[destination_index], trips.size() + 1, (Passenger *)members[index], in_hurry));
    members[index]->active_a_trip(&trips[trips.size() - 1]);
    cout << trips.size() << endl;
}
void Interface::get_cost(string passenger_name, int origin_index, int destination_index, bool in_hurry)
{
    check_member_exist(passenger_name);
    int member_index = find_member_index(passenger_name);
    members[member_index]->check_not_being_driver();
    Trip *trip = new Trip(&locs[origin_index], &locs[destination_index], 0, (Passenger *)members[member_index], in_hurry);
    printf("%.2lf\n", trip->get_price());
    delete trip;
}
void Interface::show_trips(string name, bool sort_by_cost)
{
    members[find_member_index(name)]->check_not_being_passenger();
    if (sort_by_cost)
        sort_trips_by_cost();
    else
        sort_trips_by_id();
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
        throw Import_except(EMPTY_MASSAGE);
}
void Interface::show_requested_trip_info(string name, int id)
{
    int trip_index = find_trip_index(id);
    members[find_member_index(name)]->check_not_being_passenger();
    if (trips[find_trip_index(id)].get_status() == DELETE)
        throw Import_except(NOT_EXIST_MASSAGE);
    trips[trip_index].show_info();
}
void Interface::delete_a_trip(string passenger_name, int trip_id)
{
    int trip_index = find_trip_index(trip_id);
    members[find_member_index(passenger_name)]->check_not_being_driver();
    if (trips[trip_index].get_status() == DELETE)
        throw Import_except(NOT_EXIST_MASSAGE);
    trips[trip_index].clear(passenger_name);
    cout << SUCCESSFUL_MASSAGE;
}
void Interface::accept_a_trip_by_driver(string driver_name, int trip_id)
{
    int trip_index = find_trip_index(trip_id);
    if (trips[trip_index].get_status() == DELETE)
        throw Import_except(NOT_EXIST_MASSAGE);
    members[find_member_index(driver_name)]->without_active_trip_driver();
    trips[trip_index].trip_accepted();
    members[find_member_index(driver_name)]->accept_a_trip(trip_id);
    cout << SUCCESSFUL_MASSAGE;
}
void Interface::finish_a_trip(string driver_name, int trip_id)
{
    int trip_index = find_trip_index(trip_id);
    if (trips[trip_index].get_status() == DELETE)
        throw Import_except(NOT_EXIST_MASSAGE);
    members[find_member_index(driver_name)]->finish_current_trip(trip_id);
    trips[trip_index].trip_finish();
    cout << SUCCESSFUL_MASSAGE;
}