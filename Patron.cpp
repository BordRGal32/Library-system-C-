/*
* Name: Lauren Yeiser
* Section: 401
* Date: 3/10/2015
* Description: implementation file for the patron class. Created as part of the final
* project for CS162.
*/

#include "Patron.hpp"
#include "Book.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
* Default constructor. Sets idNum and name to an empty string.
*/
Patron::Patron()  {
    idNum ="";
    name ="";
    fineAmount = 0.00;
}

/*
* Patron constructor sets idNumber and name to passed arguments.
*/
Patron::Patron(string newId, string newName) {
    idNum = newId;
    name = newName;
    fineAmount = 0.00;
}

/*
* Function adds a book to the member variable checkedOutBooks.
* @param {Pointer} targetBook
*/
void Patron::addBook( Book *targetBook ) {
    checkedOutBooks.push_back(targetBook);
}

/*
* Function removes the passed book from the member variable checkedOutBooks.
* @param {Pointer} targetBook
*/
void Patron::removeBook(Book *targetBook) {
    int index = -1;

    // find the index of the target book.
    for (int i = 0; i < (checkedOutBooks.size()); i++) {
        if (targetBook->getIdCode() == checkedOutBooks[i]->getIdCode()) {
            checkedOutBooks.erase(checkedOutBooks.begin() + i);

        }
    }
}

/*
* Function ammends the fine amount by the increment of the passed argument.
* @param {Double} amount
*/
void Patron::amendFine(double amount ) {
    fineAmount += amount;
}
