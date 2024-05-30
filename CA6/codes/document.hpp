#ifndef __DOCUMENT_H__
#define __DOCUMENT_H__

#include <string>
#include <stdexcept>

class Document
{
public:
    Document(std::string _title, int copies);
    void borrow();
    void return_doc();

    std::string get_title() { return title; }
    int get_copies() { return copies; }

    virtual void extend_returning_day(int today) = 0;
    virtual void set_borrow_day(int today) = 0;
    virtual int calculate_penalty(int today) = 0;

protected:
    std::string title;
    int copies;
    int day_borrow;
    int day_to_return;
    int last_penalty_calculated;
    int num_of_extend;
};

#endif