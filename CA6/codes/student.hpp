#ifndef __STUDENT_H__
#define __STUDENT_H__
#include "person.hpp"
#include "consts.hpp"
#include <string>
#include <stdexcept>

class Student : public Person
{
public:
    Student(std::string name, std::string _student_id);
    virtual void borrow_document(Document* doc,int today);

    std::string get_id() { return student_id; }

private:
    std::string student_id;
};

#endif