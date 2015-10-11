/*
* Name: Lauren Yeiser
* Section: 401
* Date: 3/10/2015
* Description: class declaration file for the patron class. Created as part of the final
* project for CS162.
*/

#ifndef PATRON_HPP
#define PATRON_HPP

#include <string>
#include <vector>

class Book;  // forward declaration

class Patron
{
private:
    std::string idNum;
    std::string name;
    std::vector<Book*> checkedOutBooks;
    double fineAmount;
public:
    Patron();
    Patron(std::string idn, std::string n);
    std::string getIdNum() {return idNum; };
    std::string getName() { return name; };
    std::vector<Book*> getCheckedOutBooks() {return checkedOutBooks; };
    void addBook(Book* b);
    void removeBook(Book* b);
    double getFineAmount() {return fineAmount; };
    void amendFine(double amount);
};

#endif
