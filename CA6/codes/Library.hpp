#ifndef __LIBRARY_HH__
#define __LIBRARY_HH__

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "person.hpp"
#include "document.hpp"
#include "student.hpp"
#include "prof.hpp"
#include "book.hpp"
#include "reference.hpp"
#include "magazine.hpp"
class Person;
class Document;

class Library
{
public:
	Library();
	void add_student_member(std::string student_id, std::string student_name);
	void add_prof_member(std::string prof_name);
	void add_book(std::string book_title, int copies);
	void add_magazine(std::string magazine_title, int year, int number, int copies);
	void add_reference(std::string reference_title, int copies);
	void borrow(std::string member_name, std::string document_title);
	void extend(std::string member_name, std::string document_title);
	void return_document(std::string member_name, std::string document_title);
	int get_total_penalty(std::string member_name);
	std::vector<std::string> available_titles();
	void time_pass(int days);

private:
	std::vector<Person *> members;
	std::vector<Document *> documents;
	int today;
	int find_member_index_from_name(std::string name);
	int find_doc_index_from_title(std::string doc_title);
	void check_duplicate_name(std::string member_name);
	void check_duplicate_title(std::string title);
};

#endif