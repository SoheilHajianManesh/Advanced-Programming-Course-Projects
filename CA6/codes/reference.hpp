#ifndef __REFERENCE_H__
#define __REFERENCE_H__

#include "document.hpp"
#include "consts.hpp"

class Reference : public Document
{
public:
    Reference(std::string reference_title, int copies);
    virtual void extend_returning_day(int today);
    virtual void set_borrow_day(int today);
    virtual int calculate_penalty(int today);
};

#endif