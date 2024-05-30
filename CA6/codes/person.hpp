#ifndef __PERSON_H__
#define __PERSON_H__
#include <string>
#include <stdexcept>
#include <vector>
#include "document.hpp"

class Person
{
public:
    Person(std::string _name);

    std::string get_name() { return name; }
    int get_borrowed() { return borrowed; }
    void extend_returning_day(std::string doc_name, int today);
    void return_doc(std::string doc_name, int today);
    int return_total_penalty(int today);

    virtual void borrow_document(Document *doc, int today) = 0;

protected:
    std::string name;
    int borrowed;
    std::vector<Document *> borrow_docs;
    int total_penalty;
    void check_doc_not_borrow(std::string doc_title);
    int find_doc_index_from_title(std::string doc_title);
};

#endif