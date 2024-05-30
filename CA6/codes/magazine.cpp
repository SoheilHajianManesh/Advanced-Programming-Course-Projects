#include "magazine.hpp"

using namespace std;

Magazine::Magazine(string magazine_title, int _year, int _number, int copies)
    : Document(magazine_title, copies)
{
    if (_number <= 0)
        throw runtime_error("invalid number\n");
    if (_year <= 0)
        throw runtime_error("invalid year\n");
    number = _number;
    year = _year;
}
void Magazine::extend_returning_day(int today)
{
    throw runtime_error("You can't renew magazines\n");
}
void Magazine::set_borrow_day(int today)
{
    day_borrow = today;
    day_to_return = day_borrow + MAGAZINE_DEADLINE;
}
int Magazine::calculate_penalty(int today)
{
    int penalty;
    int delay = today - day_to_return;
    if (delay <= 0)
        penalty = 0;
    else if (year < 1390)
        penalty = delay * MAGAZINE_FIRST_PENALTY;
    else
        penalty = delay * MAGAZINE_SECOND_PENALTY;
    penalty -= last_penalty_calculated;
    last_penalty_calculated += penalty;
    return penalty;
}
