/*
* Name: Lauren Yeiser
* Section: 401
* Date: 3/10/2015
* Description: class declaration file for the book class. Created as part of the final
* project for CS162.
*/

#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <iostream>

using namespace std;
class Patron;  // forward declaration


// These three locations are mutually exclusive, but note that
// a Book can be on request for a Patron while being checked
// out to another Patron.  In that case the Book's location is
// CHECKED_OUT, and when it is returned, it's location will
// become ON_HOLD_SHELF.
enum Locale {ON_SHELF, ON_HOLD_SHELF, CHECKED_OUT};


class Book
{
private:
    std::string idCode;
    std::string title;
    std::string author;
    Locale location;
    Patron* checkedOutBy;
    Patron* requestedBy;
    int dateCheckedOut;
    void setOtherFields();
public:
    static const int CHECK_OUT_LENGTH = 21;
    Book();
    Book(std::string idc, std::string t, std::string a);
    std::string getIdCode() { return idCode; };
    std::string getTitle() {return title; };
    std::string getAuthor() {return author; };
    Locale getLocation() {return location; } ;
    void setLocation(Locale lo) {location = lo; };
    Patron* getCheckedOutBy() {return checkedOutBy; };
    void setCheckedOutBy(Patron* p) {checkedOutBy = p; };
    Patron* getRequestedBy() {return requestedBy; };
    void setRequestedBy(Patron* p) {requestedBy = p; };
    int getDateCheckedOut() {return dateCheckedOut; };
    void setDateCheckedOut(int d) { dateCheckedOut = d; };
};

#endif
