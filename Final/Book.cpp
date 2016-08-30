/*********************************************************************
** Author: Jeff Goss
** Date: 12/1/15
** Description: Book.cpp file. Our class implementation file for the Book class.
Represents a book in our library. Books have an id code (unique), a title, an author, and a location.
Books also has two pointers to Patron objects, which will hold point to the Patron who checked out or requested the book.
Books also have a datecheckedout variable which marks when the book was checked out of the library. Books may be checked out for 21 days before fines occur.
*********************************************************************/


#include "Book.hpp"
#include <cstdlib>

/*********************************************************************
** Description: Constructor. Initializes idcode, title, and author of a book. Initial location of a book is on shelf, with book not requested or checked out.
**
*********************************************************************/
Book::Book(std::string idc, std::string t, std::string a)
{
	idCode = idc; //idcode of book, unique to that book
	title = t; //title of book, may be shared with other books
	author = a; //author of book, may be shared with other books
	location = ON_SHELF;
	checkedOutBy = NULL;
	requestedBy = NULL;

}

//basic get and set functions below. Allow us to access private member variables outside of this class, and allows us to change value of these variables.

int Book::getCheckOutLength()
{
	return CHECK_OUT_LENGTH;
}

std::string Book::getIdCode()
{
	return idCode;
}

std::string Book::getTitle()
{
	return title;
}

std::string Book::getAuthor()
{
	return author;
}

Locale Book::getLocation()
{
	return location;
}

void Book::setLocation(Locale loc)
{
	location = loc;
}

Patron* Book::getCheckedOutBy()
{
	return checkedOutBy;
}

void Book::setCheckedOutBy(Patron* pptr)
{
	checkedOutBy = pptr;
}

Patron* Book::getRequestedBy()
{
	return requestedBy;
}

void Book::setRequestedBy(Patron* rptr)
{
	requestedBy = rptr;
}

int Book::getDateCheckedOut()
{
	return dateCheckedOut;
}

void Book::setDateCheckedOut(int i)
{
	dateCheckedOut = i;
}
