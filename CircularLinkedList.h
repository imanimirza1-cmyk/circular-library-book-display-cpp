#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include <iostream>
#include <string>
#include <utility>
using namespace std;

// ========================================
// Book Node
// ========================================
struct BookNode
{
    int bookID;
    string title;
    BookNode* next;
};

// ========================================
// Circular Linked List Class
// head points to the last node (pivot)
// head->next points to the first node
// current points to the book now shown on the display screen
// ========================================
class CircularLinkedList
{
private:
    BookNode* head;     // last node (pivot)
    BookNode* current;  // book currently displayed on the screen
    int count;

    // Get node at an index (index must be 0..count-1)
    BookNode* GetNodeAt(int index)
    {
        if (head == nullptr)
            return nullptr;
        BookNode* node = head->next;
        for (int i = 0; i < index; i++)
            node = node->next;
        return node;
    }

    // Swap the data of two nodes
    void SwapData(BookNode* a, BookNode* b)
    {
        swap(a->bookID, b->bookID);
        swap(a->title, b->title);
    }

    // Normalize a circular index to 0..count-1
    int NormalizeIndex(int index)
    {
        return ((index % count) + count) % count;
    }

public:
    // Constructor
    CircularLinkedList()
    {
        head = nullptr;
        current = nullptr;
        count = 0;
    }

    // Check whether the list is empty
    bool IsEmpty()
    {
        return count == 0;
    }

    bool IsNotEmpty()
    {
        return count > 0;
    }

    int GetCount()
    {
        return count;
    }

    // ====================================
    // Insert at node next to head (front)
    // ====================================
    void Insert(BookNode* book)
    {
        if (book == nullptr)
            return;

        if (head == nullptr)
        {
            head = book;
            book->next = book;
            current = book;
        }
        else
        {
            book->next = head->next;
            head->next = book;
        }
        count++;
    }

    // ====================================
    // Remove node next to head (front)
    // ====================================
    BookNode* Remove()
    {
        if (IsEmpty())
            return nullptr;

        BookNode* first = head->next;

        if (first == head)
        {
            head = nullptr;
            current = nullptr;
        }
        else
        {
            head->next = first->next;
            if (current == first)
                current = first->next;
        }

        first->next = nullptr;
        count--;
        return first;
    }

    // ====================================
    // Insert at an index
    // ====================================
    void InsertAt(BookNode* book, int index)
    {
        if (book == nullptr)
            return;

        if (count == 0)
        {
            head = book;
            book->next = book;
            current = book;
            count++;
            return;
        }

        // Negative indexes wrap around the circle
        if (index < 0)
            index = NormalizeIndex(index);

        // Index greater than count wraps around
        if (index > count)
            index %= count;

        // Insert at the beginning
        if (index == 0)
        {
            Insert(book);
            return;
        }

        // Insert at the end
        if (index == count)
        {
            book->next = head->next;
            head->next = book;
            head = book;
            count++;
            return;
        }

        // Insert in the middle
        BookNode* previous = GetNodeAt(index - 1);
        book->next = previous->next;
        previous->next = book;
        count++;
    }

    // ====================================
    // Remove at an index
    // ====================================
    BookNode* RemoveAt(int index)
    {
        if (IsEmpty())
            return nullptr;

        index = NormalizeIndex(index);

        if (index == 0)
            return Remove();

        BookNode* previous = GetNodeAt(index - 1);
        BookNode* target = previous->next;
        previous->next = target->next;

        // Keep the display pointer valid
        if (current == target)
            current = target->next;

        // Update head if removing the last node
        if (target == head)
            head = previous;

        target->next = nullptr;
        count--;
        return target;
    }

    // ====================================
    // Swap data at two indexes
    // ====================================
    void Swap(int index1, int index2)
    {
        if (IsEmpty())
            return;

        index1 = NormalizeIndex(index1);
        index2 = NormalizeIndex(index2);

        if (index1 == index2)
            return;

        BookNode* first = GetNodeAt(index1);
        BookNode* second = GetNodeAt(index2);
        SwapData(first, second);
    }

    // ====================================
    // Sort by book ID (ascending)
    // ====================================
    void Sort()
    {
        if (count < 2)
            return;

        BookNode* node = head->next;
        for (int i = 0; i < count - 1; i++)
        {
            BookNode* nextNode = node->next;
            for (int j = i + 1; j < count; j++)
            {
                if (node->bookID > nextNode->bookID)
                    SwapData(node, nextNode);
                nextNode = nextNode->next;
            }
            node = node->next;
        }
    }

    // ====================================
    // Reverse the circular linked list
    // ====================================
    void Reverse()
    {
        if (count < 2)
            return;

        BookNode* oldTail = head;
        BookNode* oldFirst = head->next;
        BookNode* previous = oldTail;
        BookNode* node = oldFirst;

        while (node != oldTail)
        {
            BookNode* nextNode = node->next;
            node->next = previous;
            previous = node;
            node = nextNode;
        }

        oldTail->next = previous;
        head = oldFirst;   // Old first becomes the new last node
    }

    // ====================================
    // Move the display to the next book
    // (wraps from the last book to the first)
    // ====================================
    BookNode* MoveNext()
    {
        if (IsEmpty())
            return nullptr;

        current = current->next;
        return current;
    }

    // Book currently on the display screen
    BookNode* GetCurrent()
    {
        return current;
    }

    // Index of the book currently on the display screen
    int GetCurrentIndex()
    {
        if (IsEmpty())
            return -1;

        BookNode* node = head->next;
        for (int i = 0; i < count; i++)
        {
            if (node == current)
                return i;
            node = node->next;
        }
        return -1;
    }

    // ====================================
    // Show that the last node links back to the first node
    // ====================================
    void PrintCircularLink()
    {
        if (IsEmpty())
        {
            cout << "No books in the collection.\n";
            return;
        }

        cout << "Last book  : [" << head->bookID << "] " << head->title << endl;
        cout << "   |  next pointer (not nullptr)" << endl;
        cout << "   v" << endl;
        cout << "First book : [" << head->next->bookID << "] "
             << head->next->title << endl;
    }

    // ====================================
    // Print exactly count nodes
    // ====================================
    void Print()
    {
        if (IsEmpty())
        {
            cout << "No books in the collection.\n";
            return;
        }

        BookNode* node = head->next;

        cout << "\nIndex\tBook ID\tTitle\n";
        cout << "-----------------------------------\n";
        for (int i = 0; i < count; i++)
        {
            cout << i << "\t"
                 << node->bookID << "\t"
                 << node->title;
            if (node == current)
                cout << "   <-- now displayed";
            cout << endl;
            node = node->next;
        }
        cout << "Total books: " << count << endl;
    }

    // ====================================
    // Copy constructor
    // ====================================
    CircularLinkedList(const CircularLinkedList& other)
    {
        head = nullptr;
        current = nullptr;
        count = 0;

        if (other.head == nullptr)
            return;

        BookNode* node = other.head->next;
        for (int i = 0; i < other.count; i++)
        {
            BookNode* copy = new BookNode{ node->bookID, node->title, nullptr };
            InsertAt(copy, count);
            node = node->next;
        }
    }

    // ====================================
    // Assignment operator
    // ====================================
    CircularLinkedList& operator=(const CircularLinkedList& other)
    {
        if (this == &other)
            return *this;

        while (IsNotEmpty())
            delete Remove();

        if (other.head == nullptr)
            return *this;

        BookNode* node = other.head->next;
        for (int i = 0; i < other.count; i++)
        {
            BookNode* copy = new BookNode{ node->bookID, node->title, nullptr };
            InsertAt(copy, count);
            node = node->next;
        }
        return *this;
    }

    // ====================================
    // Destructor
    // ====================================
    ~CircularLinkedList()
    {
        while (IsNotEmpty())
            delete Remove();
    }
};

// ========================================
// Create a Book Node
// ========================================
inline BookNode* CreateBook(int id, string title)
{
    BookNode* book = new BookNode;
    book->bookID = id;
    book->title = title;
    book->next = nullptr;
    return book;
}

#endif