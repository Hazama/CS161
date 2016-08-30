#include <iostream>
#include "Library.hpp"
using std::cout;
using std::endl;

int main()
{
	//now to write extensive tests

	Book b1("123", "War and Peace", "Tolstoy");
	Book b2("234", "Moby Dick", "Melville");
	Book b3("345", "Phantom Tollbooth", "Juster");
	Patron p1("abc", "Felicity");
	Patron p2("bcd", "Waldo");
	Library lib;
	lib.addBook(&b1);
	lib.addBook(&b2);
	lib.addBook(&b3);

	cout << "Library has 3 books. Now let us try to have patron p1 check out book b1, when p1 is not a member." << endl;
	cout << "Should get patron not found." << endl;
	cout << lib.checkOutBook("abc", "123") << endl;

	cout << "Now test a book that isn't in the library." << endl;
	cout << "Should get book not found" << endl;
	cout << lib.checkOutBook("abc", "666") << endl;

	cout << "Now add patron p1 to library and retest." << endl;
	cout << "Should get check out successful and book not found" << endl;

	lib.addPatron(&p1);
	cout << lib.checkOutBook("abc", "123") << endl;
	cout << lib.checkOutBook("abc", "666") << endl;

	cout << "p1 has checked out 1 book. size of his vector should be 1..." << endl;
	cout << (p1.getCheckedOutBooks()).size() << endl;
	cout << "b1 was checked out... location should be CHECKED OUT, or 2" << endl;
	cout << b1.getLocation() << endl;

	//cout << "Testing payfine with 0 fine. " << endl;

	//lib.payFine("abc", 0.3);

	//cout << p1.getFineAmount() << endl;
	
	cout << "Book was checked out on day 0. Now let us make 21 days pass in the library." << endl;

	for (int i = 0; i < 21; i++)
	{
		lib.incrementCurrentDate();
	}

	cout << "Now let us have them check out another book on day 21..." << endl;

	lib.addBook(&b2);
	lib.checkOutBook("abc", "234");

	cout << "Let us iterate through the books p1 has checked out." << endl;

	for (int i = 0; i < p1.getCheckedOutBooks().size(); i++)
	{
		cout << (p1.getCheckedOutBooks()[i])->getTitle() << endl;
	}

	for (int i = 0; i < 2; i++)
	{
		lib.incrementCurrentDate();
	}

	lib.addPatron(&p2); 

	cout << "p2 added to library members." << endl;
	cout << "Have p2 try to check out book b1." << endl;

	cout << lib.checkOutBook("bcd", "123") << endl;

	cout << "Now have p2 try to request book b1." << endl;

	cout << lib.requestBook("bcd", "123") << endl;

	cout << "Now where is book b1 (should be 2 still) : " << b1.getLocation() << endl;

	cout << "p1 has 1 overdue book, that has been overdue for 2 days. Fine should be 20 cents." << endl;

	cout << "p1 fine: " << p1.getFineAmount() << endl; 

	lib.returnBook("123"); 

	cout << "book 1 was returned, and is on request. Location should be 1: " << b1.getLocation() << endl;
	cout << "book 1 has been returned, but they still have a second book. However tht was checked out on day 21" << endl;
	cout << "It is now day 23. In 20 days that book will be overdue. So lets move on 20 days." << endl;

	cout << "But before that lets iterate again through p1's checked out books to see if our remove works" << endl;

	for (int i = 0; i < p1.getCheckedOutBooks().size(); i++)
	{
		cout << (p1.getCheckedOutBooks()[i])->getTitle() << endl;
	}

	for (int i = 0; i < 20; i++)
	{
		lib.incrementCurrentDate();
	}

	cout << "p1 fine should now be 30 cents: " << p1.getFineAmount() << endl;

	lib.payFine(p1.getIdNum(), .3);

	cout << "p1 has payed his fine. fine should be 0 now: " << p1.getFineAmount() << endl;

	cout << "Now have p1 try to check out and request book b1 , which is on hold for p2." << endl;
	cout << lib.checkOutBook("abc", "123") << endl;
	cout << lib.requestBook("abc", "123") << endl;

	cout << "Now have p2 check out his requested book." << endl; 
	cout << lib.checkOutBook("bcd", "123") << endl;

	cout << "And for good measure check location of book, which should be 2: " << b1.getLocation() << endl;

	cout << "Now have p2 return the book, and check location, which should be 0" << endl;

	cout << lib.returnBook("123") << endl;

	cout << b1.getLocation() << endl; 

	return 0;
}