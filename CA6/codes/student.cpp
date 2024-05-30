#include "student.hpp"
using namespace std;

Student::Student(string name, string _student_id) : Person(name)
{
    if (_student_id == "")
        throw runtime_error("Empty field");
    student_id = _student_id;
    borrowed = 0;
}
void Student::borrow_document(Document *doc,int today)
{
    if (borrowed == STUDENT_MAX_BORROWED)
        throw runtime_error("Maximum number of allowed borrows exceeded\n");
    check_doc_not_borrow(doc->get_title());
    borrowed++;
    doc->borrow();
    doc->set_borrow_day(today);
    borrow_docs.push_back(doc);
}
