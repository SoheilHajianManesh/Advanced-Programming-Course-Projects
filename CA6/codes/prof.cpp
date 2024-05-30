#include "prof.hpp"
using namespace std;

Prof::Prof(string name) : Person(name)
{
    borrowed = 0;
}
void Prof::borrow_document(Document *doc,int today)
{
    if (borrowed == PROF_MAX_BORROWED)
        throw runtime_error("Maximum number of allowed borrows exceeded\n");
    check_doc_not_borrow(doc->get_title());
    borrowed++;
    doc->borrow();
    doc->set_borrow_day(today);
    borrow_docs.push_back(doc);
}