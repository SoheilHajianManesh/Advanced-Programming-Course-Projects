#ifndef __PROF_H__
#define __PROF_H__
#include "person.hpp"
#include "consts.hpp"
#include <string>

class Prof : public Person
{
public:
    Prof(std::string name);
    virtual void borrow_document(Document *doc,int today);
};

#endif