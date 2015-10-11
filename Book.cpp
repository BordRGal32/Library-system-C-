/*
* Name: Lauren Yeiser
* Section: 401
* Date: 3/10/2015
* Description: implementation file for the book class. Created as part of the final
* project for CS162.
*/

#include "Book.hpp"
#include "Patron.hpp"
#include <string>

using namespace std;

/*
* Default constructor
*/
Book::Book() {
    idCode = "";
    title = "";
    author = "";
    setOtherFields();
}

/*
*  Constructor
* @param {String} idCode
* @param {String} title
* @param {String} author
*/
Book::Book(string newId, string newTitle, string newAuthor) {
        idCode = newId;
        title = newTitle;
        author = newAuthor;
        setOtherFields();

}

/*
* Function to set location, checkedOutBy and requestedBy from constructors.
*/
void Book::setOtherFields() {
    setLocation(ON_SHELF);
    setCheckedOutBy(NULL);
    setRequestedBy(NULL);
}

