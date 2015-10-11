/*
* Name: Lauren Yeiser
* Section: 401
* Date: 3/10/2015
* Description: implementation main menu file for a program that mimicks a library system. Created as part of the final
* project for CS162.
*/
#include "Book.hpp"
#include "Patron.hpp"
#include "Library.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
    Library library;

    char userInput;
    do {
        cout << "Please select 'a' to add a book to the library" << endl;
        cout << "Please select 'p' to add a patron to the library" << endl;
        cout << "Please select 'c' to check out a book" << endl;
        cout << "please select 'r' to return a book" << endl;
        cout << "please press 'x' to request a book" << endl;
        cout << "Please press 'f' to pay a patrons fine" << endl;
        cout << "Please press 'i' to increment the date" << endl;
        cout << "Please press 'v' to view a patrons information" << endl;
        cout << "Pleaes press 's' to view a books information" << endl;
        cout << "Please select 'q' to quit" << endl;
        cin >> userInput;

        switch(userInput) {
            case 'a': {
                library.addBook();
                break;
            }
            case 'p': {
                library.addMember();
                break;
            }
            case 'c': {
                string patronId, bookId;
                cin.ignore();
                cout << "Please enter the member id" << endl;
                getline(cin, patronId);
                cout << "Please enter the book id" << endl;
                getline(cin, bookId);
                library.checkOutBook(patronId, bookId);
                break;
            }
            case 'r': {
                string bookId;
                cout << "Please enter the book id" << endl;
                cin >> bookId;
                library.returnBook(bookId);
                break;
            }
            case 'x': {
                string patronId, bookId;
                cin.ignore();
                cout << "Please enter the member id" << endl;
                getline(cin, patronId);
                cout << "Please enter the book id" << endl;
                getline(cin, bookId);
                library.requestBook(patronId, bookId);
                break;

            }
            case  'f': {
                string patronId;
                double amount;
                cin.ignore();
                cout << "Please enter the member id" << endl;
                getline(cin, patronId);
                cout << "please enter the amount the member would like to pay" << endl;
                cin >> amount;
                library.payFine(patronId, amount);
                break;
            }
            case 'i': {
                library.incrementCurrentDate();
                break;
            }
            case 'v': {
                string patronId;
                cin.ignore();
                cout << "Please enter the member id" << endl;
                getline(cin, patronId);
                library.viewPatronInfo(patronId);
                break;
            }
            case 's': {
                string bookId;
                cin.ignore();
                cout << "Please enter the book id" << endl;
                getline(cin, bookId);
                library.viewBookInfo(bookId);
            }
        }

    } while (userInput != 'q');

return 0;
}
