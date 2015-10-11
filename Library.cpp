/*
* Name: Lauren Yeiser
* Section: 401
* Date: 3/10/2015
* Description: implementation file for the Library class. Created as part of the final
* project for CS162.
*/

#include "Book.hpp"
#include "Patron.hpp"
#include "Library.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
* Default constructor. Initializes currentDate to zero.
*/
Library::Library() {
    currentDate = 0;
}

/*
* Function adds an instance of class book to Library member
* variable holdings.
*/
void Library::addBook () {
    // prompt the user for idCode, title, and author, assign to unique variables.
    string idCode, title, author;
    cin.ignore();
    cout << "Please enter the title of the book: " << endl;
    getline(cin, title);
    cout << "Please enter the name of the author: " << endl;
    getline(cin, author);
    cout << "Please enter the id code of the book: " << endl;
    getline(cin, idCode);

    //Loop over every member of holdings to ensure that the new idcode is unique.
    bool uniqueIdCode;
    do {
        uniqueIdCode = true;
        for (int i = 0; i < holdings.size(); i++ ) {
            if (idCode.compare(holdings[i].getIdCode()) == 0) {
                uniqueIdCode = false;
                cout << "That idCode was not unique. Please enter a new code" << endl;
                getline(cin, idCode);
            }
        }
    } while (!uniqueIdCode);

    // initiate a new instance of class Book, add to the holdings vector.
    Book newBook(idCode, title, author);
    holdings.push_back(newBook);
}

/*
* Function adds a n instance of the class Patron to the
* Library variable members
*/

void Library::addMember() {

    // prompt user for idCode and name, assign to local variables.
    string idCode, name;
    cin.ignore();
    cout << "Please enter the name of the new library member" << endl;
    getline(cin,name);
    cout << "Please enter a unique idCode for the new member" << endl;
    getline(cin, idCode);

    // Loop over every member of members to ensure that the new idCode is unique.
    bool uniqueIdCode;
    do {
        uniqueIdCode = true;
        for (int i = 0; i < members.size(); i++) {
            if(idCode.compare(members[i].getIdNum()) == 0) {
                uniqueIdCode = false;
                cout << "That idCode was not unique. Please enter a new code" << endl;
                getline(cin,idCode);
            }
        }
    } while (!uniqueIdCode);

    // initiate a new instance of the class Patron, add to the members vector.
    Patron newPatron(idCode, name);
    members.push_back(newPatron);
}

/*
* Function allow a user to check out a book from the library.
* @param {String} patronId
* @param {String} bookId
*/
void Library::checkOutBook(string patronId, string bookId) {
    // declare and initialize patronIndex. Will be initialzed to index of the patron with
    // idNum matching the passed patronId.
    int patronIndex = validatePatron(patronId);
    // declare and initialize bookIndex. Will be initialzed to index of the book with
    // idCode matching the passed bookId.
    int bookIndex = validateBook(bookId);

    //if the book and patrons belong to the library amd the book is not checked out
    // or on hold by another member check it out.
    if(bookIndex == -1 || patronIndex == -1) {
        cout << "The book or the patron is not registered with the library." << endl;
    } else {
        if(holdings[bookIndex].getLocation() == 0) {
            holdings[bookIndex].setLocation(CHECKED_OUT);
            holdings[bookIndex].setCheckedOutBy(&members[patronIndex]);
            holdings[bookIndex].setDateCheckedOut(currentDate);
            members[patronIndex].addBook(&holdings[bookIndex]);
            cout << holdings[bookIndex].getTitle() << " was checked out by " << members[patronIndex].getName() << endl;
        } else if(holdings[bookIndex].getLocation() == 1 &&
                    holdings[bookIndex].getRequestedBy()->getIdNum() == patronId) {
            cout << "This book is on hold by the requesting member and can be checked out." << endl;
            char userInput;
            cout << "Would you like to check this book out? press 'y' for yes and 'n' for no" << endl;
            cin >> userInput;

            if (userInput == 'y') {
                holdings[bookIndex].setLocation(CHECKED_OUT);
                holdings[bookIndex].setCheckedOutBy(&members[patronIndex]);
                holdings[bookIndex].setRequestedBy(NULL);
                holdings[bookIndex].setDateCheckedOut(currentDate);
                members[patronIndex].addBook(&holdings[bookIndex]);
                cout << holdings[bookIndex].getTitle() << " was checked out by " << members[patronIndex].getName() << endl;
            }

        } else {
            cout << "This book is checked out or reserved by a different library member" << endl;
        }
    }
}

/*
* Function will return a book to the library unless if it is checked out
* and not on hold. If it is on hold the book will be checked by the requested patron.
* @param {String} bookId
*/
void Library::returnBook(string bookId) {
    // declare and initialize bookIndex. Will be initialzed to index of the book with
    // idCode matching the passed bookId.
    int bookIndex = validateBook(bookId);

    // if the book is not registered with the library let the user know.
    if(bookIndex == -1) {
        cout << "That book is not registered with the Library. " << endl;
    } else {
        // if the book is checked out.
        if (holdings[bookIndex].getLocation() == 2) {
           holdings[bookIndex].getCheckedOutBy()->removeBook(&holdings[bookIndex]);

            // if the book is on hold check out the book by the requested patron.
            if (holdings[bookIndex].getRequestedBy() != NULL) {
                string requestedById = holdings[bookIndex].getRequestedBy()->getIdNum();
                //return book to shelf so it can be checked out.
                holdings[bookIndex].setLocation(ON_SHELF);
                checkOutBook(requestedById, bookId);
                holdings[bookIndex].setRequestedBy(NULL);
            // if the book is not on hold return the book to the shelf.
            } else {
                holdings[bookIndex].setCheckedOutBy(NULL);
                holdings[bookIndex].setLocation(ON_SHELF);
                cout << "The book " << holdings[bookIndex].getTitle() << " has been returned to the library" << endl;
            }
        // if the book is not checked out let the user know.
        } else {
            cout << "That book is not checked out" << endl;
        }
    }
}

/*
* Function will place a book on hold.
* @param {String} patronId
* @param {STring} bookId
*/
void Library::requestBook(string patronId, string bookId) {
    // declare and initialize patronIndex. Will be initialzed to index of the patron with
    // idNum matching the passed patronId.
    int patronIndex = validatePatron(patronId);
    // declare and initialize bookIndex. Will be initialzed to index of the book with
    // idCode matching the passed bookId.
    int bookIndex = validateBook(bookId);

    //if the book or patron are not registered with the library let the user know.
    if(bookIndex == -1 || patronIndex == -1 ) {
        cout << "The book or the patron is registered with the library" << endl;
    } else {
        // if the book is on hold let the user know.
        if(holdings[bookIndex].getRequestedBy() != NULL) {
            cout << "The requested book is already on hold" << endl;
        // if the book is checked out by the requesting member let the user know. If not set
        // requestedBy property of the target book.
        } else if(holdings[bookIndex].getLocation() == 2 ) {
            if (holdings[bookIndex].getCheckedOutBy()->getIdNum().compare(patronId) == 0 ) {
                cout << "The book is already checked out by the requested mamber." << endl;
            } else  {
                holdings[bookIndex].setRequestedBy(&members[patronIndex]);
                cout << "The book " << holdings[bookIndex].getTitle() << " is now on hold by " << members[patronIndex].getName() << endl;
            }
        // if the book is on the shelf set the location to ON_HOLD_SHELF and set
        // the requested by property of the target book to the requesting patron.
        } else {
             holdings[bookIndex].setRequestedBy(&members[patronIndex]);
             holdings[bookIndex].setLocation(ON_HOLD_SHELF);
             cout << "The book " << holdings[bookIndex].getTitle() << " is now on hold by " << members[patronIndex].getName() << endl;
        }
    }
}
 /*
 * Function will call Patron member function ammend Fine to pay a fine.
 * @param {String} patronId.
 * @param {double} amountl
 */
void Library::payFine( string patronId, double amount ) {
    // declare and initialize patronIndex. Will be initialzed to index of the patron with
    // idNum matching the passed patronId.
    int patronIndex = validatePatron(patronId);

    //if the patron does not belong to the library let the user know.
    if (patronIndex == -1 ) {
        cout << "The requested patron is not registered with the library" << endl;
    } else {
        // if the patron exists call amendFine to pay the fine.
        members[patronIndex].amendFine(amount*-1);
        cout << "Patron, " << members[patronIndex].getName() << " has a late fee total of " << members[patronIndex].getFineAmount() << endl;
    }

}

/*
* Function increments the currentDate by one and adds a fine of ten
* cents to a patron's fineAmount for any book checked out for more than 21 days.
*/
void Library::incrementCurrentDate() {
    currentDate += 1;

    //call Patron member function amendFine to increase a patrons fine amount
    // by ten cents for all overdue books.
    for (int i = 0; i < holdings.size(); i++ ) {
        cout << "Date book checked out " << holdings[i].getDateCheckedOut() << endl;
        if ((currentDate - holdings[i].getDateCheckedOut()) > Book::CHECK_OUT_LENGTH ) {
            holdings[i].getCheckedOutBy()->amendFine(0.10);
        }
    }
    cout << "The current date is now " << currentDate << endl;
}

/*
* Function will print the Patron's ID, name, the titles of any checked out Books,
* and their current fines
* @param {String} PatronId
*/
void Library::viewPatronInfo(string patronId) {
    // declare and initialize patronIndex. Will be initialzed to index of the patron with
    // idNum matching the passed patronId.
    int patronIndex = validatePatron(patronId);

    // if the patron does not exist let the user know.
    if (patronIndex == -1) {
        cout << "The requested patron is not registered with the library" << endl;
    } else {
        //Print the patron's, name, id, current checked out books, and fine amount.
        cout << "Patron Name: " << members[patronIndex].getName() << endl;
        cout << "Patron Id: " << members[patronIndex].getIdNum() << endl;
        cout << "Current checked out books: " << endl;
        for (int i = 0; i < members[patronIndex].getCheckedOutBooks().size(); i ++ ){
            cout << i + 1 << ". " << members[patronIndex].getCheckedOutBooks()[i]->getTitle() << endl;
        }
        cout << "Current requested books: " << endl;
        for (int j = 0; j < holdings.size(); j++ ) {
            if(holdings[j].getRequestedBy() &&
                holdings[j].getRequestedBy()->getIdNum() == patronId) {
                cout <<j + 1 << ". " << holdings[j].getTitle() << endl;
            }
        }

        cout << "Current fine amount: " << members[patronIndex].getFineAmount() << endl;
    }
}

/*
* Function will print the Book's ID, title, author and location;
* the name of the Patron whom it's requested by; the name of the Patron
* whom it's checked out by (if any), and the number of days left till
* it's due (or the word "overdue")
* @param {String} bookId
*/
void Library::viewBookInfo(string bookId) {
     // declare and initialize bookIndex. Will be initialzed to index of the book with
    // idCode matching the passed bookId.
    int bookIndex = validateBook(bookId);

    // if the book is not registered with the library let the user know.
    if (bookIndex == -1) {
        cout << "The requested book is not registered with the library" << endl;
    } else {
        // Use the current location of the book to build a string reflecting
        // the current location.
        Locale currentLocation = holdings[bookIndex].getLocation();
        string bookLocation;
        switch(currentLocation) {
            case 0:
                bookLocation = " on the shelf ";
                break;
            case 1:
                bookLocation = " on hold ";
                break;
            case 2:
                bookLocation = " checked out ";
                break;
        }

        // print the book title, author, idnumber, location. Print requested by if book is requested and
        // checked out by, and days until due if book is checked out.
        cout << "Book Title: " << holdings[bookIndex].getTitle() << endl;
        cout << "Book Author: " << holdings[bookIndex].getAuthor() << endl;
        cout << "Book ID number: " << holdings[bookIndex].getIdCode() << endl;
        cout << "Location:" << bookLocation << endl;
        if (holdings[bookIndex].getRequestedBy()) {
            cout << "Requested by: " << holdings[bookIndex].getRequestedBy()->getName() << endl;
        }
        if (holdings[bookIndex].getCheckedOutBy()) {
            cout << "Checked out by: " << holdings[bookIndex].getCheckedOutBy()->getName() << endl;
             // calculate the number of days until the book is due.
            int dueDate = holdings[bookIndex].getDateCheckedOut() + Book::CHECK_OUT_LENGTH;
            int dueIn = dueDate - currentDate;
            if(dueIn < 0 ) {
                cout << "Days until due: overdue" << endl;
            } else {
                cout << "Days until due: " << dueIn << endl;
            }
        }

    }
}

/*
* Function validates the existence of a patron with patronId matching the passed argument.
* returns -1 if the patron does not exist and the index of the patron within members otherwise.
* @param {String} patronId
* @return {Integer}
*/
int Library::validatePatron(string patronId) {
    // declare return variable, initialze to -1.
    int patronIndex = -1;
    // if the passed patronId matches the idNum of a patron in members set
    // patron index to i.
    for(int i = 0; i < members.size(); i++ ) {
        if(patronId.compare(members[i].getIdNum()) == 0) {
            patronIndex = i;
        }
    }
    return patronIndex;
}


/*
* Function validates the existence of a book with bookId matching the passed argument.
* returns -1 if the book does not exist and the index of the book within holdings otherwise.
* @param {String} patronId
* @return {Integer}
*/
int Library::validateBook(string bookId) {
     // declare return variable, initialze to -1.
    int bookIndex = -1;
    // if the passed bookId matches the idCode of a book in holdings set
    //  bookIndex to i.
    for (int j = 0; j < holdings.size(); j ++ ) {
        if(bookId.compare(holdings[j].getIdCode()) == 0) {
            bookIndex = j;

        }
    }
    return bookIndex;
}

















