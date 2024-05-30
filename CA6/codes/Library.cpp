#include "Library.hpp"

using namespace std;

Library::Library()
{
    today = 1;
}

int Library::find_member_index_from_name(std::string name)
{
    for (int i = 0; i < members.size(); i++)
        if (members[i]->get_name() == name)
            return i;
    throw runtime_error("member not exist\n");
}

int Library::find_doc_index_from_title(string doc_title)
{
    int i;
    for (i = 0; i < documents.size(); i++)
        if (documents[i]->get_title() == doc_title)
            break;
    if (documents[i]->get_copies() == 0 || i == documents.size())
        throw runtime_error("This document does not exist\n");
    return i;
}

void Library::check_duplicate_name(std::string member_name)
{
    for (int i = 0; i < members.size(); i++)
        if (members[i]->get_name() == member_name)
            throw runtime_error("Name already exists\n");
}
void Library::check_duplicate_title(std::string title)
{
    for (int i = 0; i < documents.size(); i++)
        if (documents[i]->get_title() == title)
            throw runtime_error("A document with the specified name already exists\n");
}

void Library::add_student_member(std::string student_id, std::string student_name)
{
    try
    {
        Student *new_std = new Student(student_name, student_id);
        check_duplicate_name(new_std->get_name());
        members.push_back(new_std);
    }
    catch (runtime_error &except)
    {
        cout << except.what() << endl;
        exit(EXIT_SUCCESS);
    };
}
void Library::add_prof_member(std::string prof_name)
{
    try
    {
        Prof *new_prof = new Prof(prof_name);
        check_duplicate_name(new_prof->get_name());
        members.push_back(new_prof);
    }
    catch (runtime_error &except)
    {
        cout << except.what() << endl;
        exit(EXIT_SUCCESS);
    };
}
void Library::add_book(std::string book_title, int copies)
{
    try
    {
        Book *new_book = new Book(book_title, copies);
        check_duplicate_title(new_book->get_title());
        documents.push_back(new_book);
    }
    catch (runtime_error &except)
    {
        cout << except.what() << endl;
        exit(EXIT_SUCCESS);
    };
}
void Library::add_magazine(std::string magazine_title, int year, int number, int copies)
{
    try
    {
        Magazine *new_mgn = new Magazine(magazine_title, year, number, copies);
        check_duplicate_title(new_mgn->get_title());
        documents.push_back(new_mgn);
    }
    catch (runtime_error &except)
    {
        cout << except.what() << endl;
        exit(EXIT_SUCCESS);
    };
}
void Library::add_reference(std::string reference_title, int copies)
{
    try
    {
        Reference *new_rfc = new Reference(reference_title, copies);
        check_duplicate_title(new_rfc->get_title());
        documents.push_back(new_rfc);
    }
    catch (runtime_error &except)
    {
        cout << except.what() << endl;
        exit(EXIT_SUCCESS);
    };
}
void Library::borrow(string member_name, string document_title)
{
    try
    {
        int index = find_doc_index_from_title(document_title);
        members[find_member_index_from_name(member_name)]->borrow_document(documents[index], today);
    }
    catch (runtime_error &except)
    {
        cout << except.what() << endl;
        exit(EXIT_SUCCESS);
    }
}
void Library::extend(string member_name, string document_title)
{
    try
    {
        members[find_member_index_from_name(member_name)]->extend_returning_day(document_title, today);
    }
    catch (runtime_error &except)
    {
        cout << except.what() << endl;
        exit(EXIT_SUCCESS);
    }
}
void Library::return_document(string member_name, string document_title)
{
    try
    {
        documents[find_doc_index_from_title(document_title)]->return_doc();
        members[find_member_index_from_name(member_name)]->return_doc(document_title, today);
    }
    catch (runtime_error &except)
    {
        cout << except.what() << endl;
        exit(EXIT_SUCCESS);
    }
}
int Library::get_total_penalty(std::string member_name)
{
    return members[find_member_index_from_name(member_name)]->return_total_penalty(today);
}
vector<string> Library::available_titles()
{
    vector<string> available_titles;
    for (int i = 0; i < documents.size(); i++)
        if (documents[i]->get_copies() > 0)
            available_titles.push_back(documents[i]->get_title());
    return available_titles;
}
void Library::time_pass(int days)
{
    try
    {
        if (days < 0)
            throw runtime_error("Invalid day\n");
        today += days;
    }
    catch (runtime_error &except)
    {
        cout << except.what() << endl;
        exit(EXIT_SUCCESS);
    }
}
