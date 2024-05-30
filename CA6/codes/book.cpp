#include "book.hpp"

using namespace std;

Book::Book(string book_title, int copies) : Document(book_title, copies)
{
}
void Book::extend_returning_day(int today)
{
    if (today == day_borrow)
        throw runtime_error("You can't extend and borrow a document on the same day\n");
    if (today > day_to_return)
        throw runtime_error("You can't renew a document after receiving a penalty\n");
    if (num_of_extend >= MAXIMUM_NUM_OF_EXTEND)
        throw runtime_error("You can't renew a document more than two times\n");
    day_to_return += 10;
    num_of_extend += 1;
}
void Book::set_borrow_day(int today)
{
    day_borrow = today;
    day_to_return = day_borrow + BOOK_DEADLINE;
}
int Book::calculate_penalty(int today)
{
    int penalty;
    int delay = today - day_to_return;
    if (delay <= 0)
        penalty = 0;
    else if (delay <= BOOK_FIRST_PENALTY_PERIOD)
        penalty = delay * BOOK_FIRST_PENALTY;
    else if (delay > BOOK_FIRST_PENALTY_PERIOD && delay <= BOOK_SECOND_PENALTY_PERIOD)
        penalty = (BOOK_FIRST_PENALTY_PERIOD * BOOK_FIRST_PENALTY) 
             + ((delay - BOOK_FIRST_PENALTY_PERIOD) * BOOK_SECOND_PENALTY);
    else
        penalty = (BOOK_FIRST_PENALTY_PERIOD * BOOK_FIRST_PENALTY) 
            + ((BOOK_SECOND_PENALTY_PERIOD - BOOK_FIRST_PENALTY_PERIOD) * BOOK_SECOND_PENALTY) 
                + ((delay - BOOK_SECOND_PENALTY_PERIOD) * BOOK_THIRD_PENALTY);
    penalty -= last_penalty_calculated;
    last_penalty_calculated += penalty;
    return penalty;
}
