#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include "CircularLinkedList.h"
using namespace std;

// Read an integer safely (re-asks until valid input)
int ReadInt(const string& prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        if (cin.eof())
        {
            cout << "\nInput closed. Exiting.\n";
            exit(0);
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
    }
}

// Read a full line (title may contain spaces)
string ReadTitle()
{
    string title;
    cout << "Enter Book Title: ";
    getline(cin, title);
    return title;
}

void ShowMenu()
{
    cout << "\n========================================\n";
    cout << "  CIRCULAR LIBRARY BOOK DISPLAY SYSTEM\n";
    cout << "========================================\n";
    cout << "1.  Display All Books\n";
    cout << "2.  Insert Book at Head\n";
    cout << "3.  Remove Book from Head\n";
    cout << "4.  Insert Book at Index\n";
    cout << "5.  Remove Book at Index\n";
    cout << "6.  Swap Books\n";
    cout << "7.  Sort Books by ID\n";
    cout << "8.  Reverse Book Collection\n";
    cout << "9.  Move to Next Book\n";
    cout << "10. Check Collection Status\n";
    cout << "11. Exit\n";
}

int main()
{
    CircularLinkedList library;

    // Predefined featured books
    library.InsertAt(CreateBook(103, "Operating Systems"), 0);
    library.InsertAt(CreateBook(101, "Data Structures"), 1);
    library.InsertAt(CreateBook(105, "Computer Networks"), 2);
    library.InsertAt(CreateBook(102, "Database Systems"), 3);
    library.InsertAt(CreateBook(104, "Software Engineering"), 4);

    int choice = 0;

    do
    {
        ShowMenu();
        choice = ReadInt("Enter your choice: ");

        switch (choice)
        {
        case 1:
        {
            library.Print();
            break;
        }
        case 2:
        {
            int id = ReadInt("Enter Book ID: ");
            string title = ReadTitle();
            library.Insert(CreateBook(id, title));
            cout << "\nBook inserted at the head (next to the pivot).\n";
            break;
        }
        case 3:
        {
            BookNode* removed = library.Remove();
            if (removed != nullptr)
            {
                cout << "\nRemoved from head: " << removed->title
                     << " (ID " << removed->bookID << ")\n";
                delete removed;
            }
            else
                cout << "\nThe collection is empty. Nothing to remove.\n";
            break;
        }
        case 4:
        {
            int id = ReadInt("Enter Book ID: ");
            string title = ReadTitle();
            int index = ReadInt("Enter index to insert at: ");
            library.InsertAt(CreateBook(id, title), index);
            cout << "\nBook inserted. (Index " << index
                 << " wraps around the circle if out of range.)\n";
            break;
        }
        case 5:
        {
            if (library.IsEmpty())
            {
                cout << "\nThe collection is empty. Nothing to remove.\n";
                break;
            }
            int index = ReadInt("Enter index to remove: ");
            BookNode* removed = library.RemoveAt(index);
            if (removed != nullptr)
            {
                cout << "\nRemoved book: " << removed->title
                     << " (ID " << removed->bookID << ")\n";
                delete removed;
            }
            break;
        }
        case 6:
        {
            if (library.GetCount() < 2)
            {
                cout << "\nAt least two books are needed to swap.\n";
                break;
            }
            int i1 = ReadInt("Enter first index: ");
            int i2 = ReadInt("Enter second index: ");
            library.Swap(i1, i2);
            cout << "\nBooks swapped. (Indexes wrap around the circle.)\n";
            break;
        }
        case 7:
        {
            library.Sort();
            cout << "\nBooks sorted by ID in ascending order.\n";
            break;
        }
        case 8:
        {
            library.Reverse();
            cout << "\nBook collection reversed.\n";
            break;
        }
        case 9:
        {
            if (library.IsEmpty())
            {
                cout << "\nThe collection is empty. Nothing to display.\n";
                break;
            }
            BookNode* shown = library.MoveNext();
            cout << "\nNow displaying: [" << shown->bookID << "] "
                 << shown->title
                 << "  (index " << library.GetCurrentIndex() << ")\n";
            if (library.GetCurrentIndex() == 0)
                cout << "The display wrapped around to the first book.\n";
            break;
        }
        case 10:
        {
            if (library.IsEmpty())
                cout << "\nStatus: The collection is EMPTY.\n";
            else
            {
                cout << "\nStatus: The collection is NOT empty. "
                     << "Total books: " << library.GetCount() << "\n\n";
                library.PrintCircularLink();
            }
            break;
        }
        case 11:
            cout << "\nExiting the Circular Library Display System. Goodbye!\n";
            break;
        default:
            cout << "\nInvalid choice. Please enter 1-11.\n";
        }

    } while (choice != 11);

    return 0;
}