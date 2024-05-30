#include <iostream>
#include "utaxi_server.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Interface interface(read_locs(argv[1]));
    Handle_system taxi_system(&interface);
    taxi_system.handle_input();
    return 0;
}