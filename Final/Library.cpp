/*********************************************************************
** Author: Jeff Goss
** Date: 12/1/15
** Description: Library.cpp file. Our class implementation file for the Library class.
Represents a library. Libraries contain books and patrons, represented here by vectors containing pointers to Book and Patron objects.
Library functions allow books and patrons to be added to the library. Functions allow books to be checked out, requested, and returned.
The date of the library is initially set to 0.
Date is changed with a function that will also calculate the fines of each patron who has a book checked out for more than 21 days.
Payment of fines are handled within this class.
*********************************************************************/


#include "Library.hpp"
#include <iostream>

/*********************************************************************
** Description: Constructor. Initializes currentDate to 0.
**
*********************************************************************/
Library::Library()
{
	currentDate = 0;
}

/*********************************************************************
** Description: addBook function. Adds a book to the library's selection of books.
**
*********************************************************************/
void Library::addBook(Book* book)
{
	holdings.push_back(book); //adds pointer to Book object to our holdings vector
}

/*********************************************************************
** Description: addPatron function. Adds a patron to the library's member list.
**
*********************************************************************/
void Library::addPatron(Patron* patron)
{
	members.push_back(patron); //adds a pointer to Patron object to our members vector
}

/*********************************************************************
** Description: Allows a patron to check out a book. Can handle cases where the book does not exist in the library, the patron is not a member,
the book is already checked out, or the book is on hold.
If the book is on hold, will check if the patron checking it out is the one who requested it.
If check out is successful, status of the book and patron will be updated by this function.

Returns a string to let user know status of check out.
**
*********************************************************************/
std::string Library::checkOutBook(std::string pID, std::string bID)
{

	if (getBook(bID) == NULL) //book not in library
	{
		return "book not found";
	}

	if (getPatron(pID) == NULL) //patron not member of library
	{
		return "patron not found";
	}

	if (getBook(bID)->getLocation() == CHECKED_OUT) //if book is checked out
	{
		return "book already checked out";
	}


	if (getBook(bID)->getLocation() == ON_HOLD_SHELF) //if book is on hold
	{
		if (getBook(bID)->getRequestedBy() != getPatron(pID)) //if a different patron already has the book on request
		{
			return "book on hold by other patron";
		}

		else //if book is on hold, and it is being held for the patron requested it
		{
			getBook(bID)->setCheckedOutBy(getPatron(pID)); //update Book's checkedoutby variable
			getPatron(pID)->addBook(getBook(bID)); //update patron's checked out books
			getBook(bID)->setDateCheckedOut(currentDate); //date checked out is current date
			getBook(bID)->setLocation(CHECKED_OUT); //book is now checked out
			getBook(bID)->setRequestedBy(NULL); //book is no longer on hold

			return "check out successful";

		}

	}

	else //book was ON_SHELF, and it being checked out.
	{
		getBook(bID)->setCheckedOutBy(getPatron(pID)); //update Book's checkedoutby variable
		getPatron(pID)->addBook(getBook(bID)); //update patron's checked out books
		getBook(bID)->setDateCheckedOut(currentDate); //set date checked out to current date
		getBook(bID)->setLocation(CHECKED_OUT); //book is now checked out

		return "check out successful";

	}
}

/*********************************************************************
** Description: Allows a patron to return a book. Can handle cases where the book is already in the library, or where the book is not property of the library.

If return is successful, will update the status of patron and book.
If the book was requested by someone while checked out, book will be moved to hold shelf rather than regular shelf.

Returns a string to let user know status of return.
**
*********************************************************************/
std::string Library::returnBook(std::string bID)
{
	if (getBook(bID) == NULL) //book not in library
	{
		return "book not found";
	}

	if (getBook(bID)->getLocation() != CHECKED_OUT) //book not checked out
	{
		return "book already in library";
	}

	else
	{
		Patron* patron = getBook(bID)->getCheckedOutBy(); //patron will point to Patron who checked out book
		patron->removeBook(getBook(bID)); //remove book from patron's checked out vector
		getBook(bID)->setCheckedOutBy(NULL); //book no longer checked out

		if (getBook(bID)->getRequestedBy() != NULL) //if book is requested by someone
		{
			getBook(bID)->setLocation(ON_HOLD_SHELF); //move book to hold shelf
		}
		else //book not requested by anyone
		{
			getBook(bID)->setLocation(ON_SHELF); //move book to shelf
		}

		return "return successful";
	}
}

/*********************************************************************
** Description: Allows a patron to request a book. Can handle cases where the book is already requested, where the book is not one owned by the library,
or where the patron is not a member of the library.

If request is successful, will update the status the book. If book was on shelf, it will be moved to hold shelf.

Returns a string to let user know status of request.
**
*********************************************************************/
std::string Library::requestBook(std::string pID, std::string bID)
{
	if (getBook(bID) == NULL) //book not in library
	{
		return "book not found";
	}

	if (getPatron(pID) == NULL) //patron not member of library
	{
		return "patron not found";
	}

	if (getBook(bID)->getLocation() == ON_HOLD_SHELF) //if book is on hold and thus already requested
	{
		return "book already on hold";
	}

	else
	{
		getBook(bID)->setRequestedBy(getPatron(pID)); //update requestedby of book

		if (getBook(bID)->getLocation() == ON_SHELF) //if book on shelf and not checked out
		{
			getBook(bID)->setLocation(ON_HOLD_SHELF); //move to hold shelf
		}

		return "request successful";
	}
}

/*********************************************************************
** Description: Handles the payment of fines. Calls on a member function of patron to accomplish this.
Can handle cases where patron is not a member of the library.
**
*********************************************************************/
std::string Library::payFine(std::string pID, double payment)
{
	double negpay = (0 - payment); //gets negative of payment for amend function

	if (getPatron(pID) == NULL) //patron not member of library
	{
		return "patron not found";
	}

	else
	{
		getPatron(pID)->amendFine(negpay); //alter the fine to reflect payment
		return "payment successful";
	}
}

/*********************************************************************
** Description: Will increment the date by 1 day. After incrementing date this function will then check the status of each patron in the library.
If the patron has a checked out book, it will then check to see if the book is overdue. The user will incur a fine of 10 cents/day for each overdue book.
**
*********************************************************************/
void Library::incrementCurrentDate()
{
	currentDate += 1;
	std::cout << "current date: " << currentDate << std::endl;

	for (int i = 0; i < members.size(); i++) //iterate over members of library
	{
		std::vector<Book*> booktoloop = members.at(i)->getCheckedOutBooks(); //booktoloop will be members checked out books
		int numbooksover = 0; //will hold number of books the patron has that are overdue

		for (int j = 0; j < booktoloop.size(); j++) //loop through checked out books of a member
		{
			int dayspassed = (currentDate - booktoloop.at(j)->getDateCheckedOut()); //gets number of days a book has been checked out

			if (dayspassed > booktoloop.at(j)->getCheckOutLength()) //if number of days book has been checked out exceeds 21
			{
				numbooksover += 1; //we have an overdue book

			}
		}

		//after looping over all books of that particular patron, amend fine. 10 cents for each overdue book.
		members.at(i)->amendFine(0.10 * numbooksover);
	}
}


Patron* Library::getPatron(std::string pID)
{
	for (int i = 0; i < members.size(); i++) //iteate over Patron objects in library
	{
		if (pID == (members.at(i)->getIdNum())) //if Patron is in members
		{
			return members.at(i); //return pointer to that Patron
		}

	}

	return NULL;
}

Book* Library::getBook(std::string bID)
{

	for (int i = 0; i < holdings.size(); i++) //iterate over Book objects in library
	{
		if (bID == (holdings.at(i)->getIdCode())) //if Book is in holdings
		{
			return holdings.at(i); //return pointer to that Book
		}
	}

	return NULL;  //book not found, return NULL.
}
