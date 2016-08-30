/*********************************************************************
** Author: Jeff Goss
** Date: 12/1/15
** Description: Patron.cpp file. Our class implementation file for the Patron class.
Represents a patron of our library. Patrons have an idnumber (unique), name, and a fine amount which is initially 0.
Patrons also have a vector that contains pointers to Books, representing books that the patron has checked out of the library.
*********************************************************************/


#include "Patron.hpp"
#include <iostream>
using std::cout;
using std::endl;

/*********************************************************************
** Description: Constructor. Initializes member variables.
**
*********************************************************************/
Patron::Patron(std::string idn, std::string n)
{
	idNum = idn; //id number of patron. unique to that patron
	name = n; //name of patron. may be shared with other patrons
	fineAmount = 0; //patron's fines
}

std::string Patron::getIdNum()
{
	return idNum;
}

std::string Patron::getName()
{
	return name;
}

//vector containing pointers to Books that the patron has checked out
std::vector<Book*> Patron::getCheckedOutBooks()
{
	return checkedOutBooks;
}

/*********************************************************************
** Description: addBook function. Adds a pointer to a Book object to the vector checkedoutBooks. Represents the patron checking out a book.
**
*********************************************************************/
void Patron::addBook(Book* b)
{
	checkedOutBooks.push_back(b); //adds pointer to Book object to the vector
}

/*********************************************************************
** Description: removeBook function. Deletes a pointer to a Book object from the vector checkedOutBooks.
Used when the patron returns a book and thus no longer has it checked out.
**
*********************************************************************/
void Patron::removeBook(Book* b)
{
	for (int i = 0; i < checkedOutBooks.size(); i++) //iterate over elements in vector, which are pointers to Books
	{
		if (checkedOutBooks.at(i) == b) //if book is checked out by Patron
		{
			checkedOutBooks.erase(checkedOutBooks.begin() + i); //remove book from checked out
		}
	}
}

double Patron::getFineAmount()
{
	return fineAmount;
}

/*********************************************************************
** Description: amendFine function. Takes a double as an argument, and changes the fine that the patron has. A positive argument means an increase in fines.
**
*********************************************************************/
void Patron::amendFine(double amount)
{
	fineAmount += amount;
}
