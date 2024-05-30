#ifndef __BOOK_H__
#define __BOOK_H__

#include "document.hpp"
#include "consts.hpp"
#include <string>

class Book : public Document
{
public:
    Book(std::string book_title, int copies);
    virtual void extend_returning_day(int today);
    virtual void set_borrow_day(int today);
    virtual int calculate_penalty(int today);

};

#endif