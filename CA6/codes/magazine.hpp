#ifndef __MAGAZINE_H__
#define __MAGAZINE_H__

#include "consts.hpp"
#include "document.hpp"
#include <string>
#include <stdexcept>

class Magazine : public Document
{
public:
    Magazine(std::string magazine_title, int _year, int _number, int copies);
    virtual void extend_returning_day(int today);
    virtual void set_borrow_day(int today);
    virtual int calculate_penalty(int today);

private:
    int year;
    int number;
};

#endif