#include "reference.hpp"

using namespace std;

Reference::Reference(string reference_title, int copies) : Document(reference_title, copies)
{
}
void Reference::extend_returning_day(int today)
{
    if (today == day_borrow)
        throw runtime_error("You can't extend and borrow a document on the same day\n");
    if (today > day_to_return)
        throw runtime_error("You can't renew a document after receiving a penalty\n");
    if (num_of_extend >= 2)
        throw runtime_error("You can't renew a document more than two times\n");
    day_to_return += 5;
    num_of_extend++;
}
void Reference::set_borrow_day(int today)
{
    day_borrow = today;
    day_to_return = day_borrow + REFERENCE_DEADLINE;
}
int Reference::calculate_penalty(int today)
{
    int penalty;
    int delay = today - day_to_return;
    if (delay <= 0)
        penalty = 0;
    else if (delay <= REF_FIRST_PENALTY_PERIOD)
        penalty = delay * REF_FIRST_PENALTY;
    else
        penalty = (REF_FIRST_PENALTY_PERIOD * REF_FIRST_PENALTY)
            + ((delay - REF_FIRST_PENALTY_PERIOD) * REF_SECOND_PENALTY);
    penalty -= last_penalty_calculated;
    last_penalty_calculated += penalty;
    return penalty;
}
