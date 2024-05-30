#include "document.hpp"
using namespace std;

Document::Document(string _title, int copies) : copies(copies)
{
    if (_title == "")
        throw runtime_error("Empty field\n");
    title = _title;
    last_penalty_calculated=0;
    num_of_extend = 0;
}
void Document::borrow()
{
    copies--;
}
void Document::return_doc()
{
    copies++;
}
