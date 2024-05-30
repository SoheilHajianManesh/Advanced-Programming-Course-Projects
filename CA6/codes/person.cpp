#include "person.hpp"
using namespace std;
Person::Person(string _name)
{
    if (_name == "")
        throw runtime_error("Empty field");
    name = _name;
    borrowed = 0;
    total_penalty = 0;
}
void Person::check_doc_not_borrow(std::string doc_title)
{
    for (int i = 0; i < borrow_docs.size(); i++)
        if (borrow_docs[i]->get_title() == doc_title)
            throw runtime_error("You borrowed this document already\n");
}
int Person::find_doc_index_from_title(string doc_title)
{
    int i;
    for (i = 0; i < borrow_docs.size(); i++)
        if (borrow_docs[i]->get_title() == doc_title)
            break;
    if (i == borrow_docs.size())
        throw runtime_error("You have not borrowed this document\n");
    return i;
}
void Person::extend_returning_day(string doc_name, int today)
{
    borrow_docs[find_doc_index_from_title(doc_name)]->extend_returning_day(today);
}
void Person::return_doc(string doc_name, int today)
{
    total_penalty += borrow_docs[find_doc_index_from_title(doc_name)]->calculate_penalty(today);
    borrow_docs.erase(borrow_docs.begin() + find_doc_index_from_title(doc_name));
    borrowed--;
}
int Person::return_total_penalty(int today)
{
    for (int i = 0; i < borrow_docs.size(); i++)
        total_penalty += borrow_docs[i]->calculate_penalty(today);
    return total_penalty;
}