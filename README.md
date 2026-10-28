# Circular Library Book Display System

A menu-driven C++ console application that rotates through a library's featured books using a **circular singly linked list**. Built for **Lab 06: Implementation of a Circular Linked List**.

The library has a digital screen near the entrance that must keep cycling through the featured books. After the last book is shown, it returns to the first book and continues. A normal singly linked list ends at `nullptr`, but in a circular linked list the last node points back to the first node, so traversal never reaches the end.

## Features

- Display all books with their index, ID, and title, with a marker on the book currently shown on the screen
- **Move to Next Book** with automatic wrap-around from the last book to the first
- Insert a book at the head (the node next to the pivot) or at any index
- Remove a book from the head or from any index
- Swap two books by index
- Sort books by ID (ascending)
- Reverse the circular collection
- Check collection status and confirm that the last book links back to the first book
- Circular index handling: negative and out-of-range indexes wrap around the circle
- Input validation for menu choices, IDs, and indexes
- Starts with five predefined books for quick testing

## Project Structure

```
.
├── CircularLinkedList.h   # BookNode struct, CircularLinkedList class, CreateBook() helper
├── main.cpp               # Menu-driven console program
└── README.md
```

## How the Circular List Works

The list keeps a single pointer called `head`, which points to the **last node** (the pivot). The first node is always `head->next`.

```
        +-----------------------------------------------+
        |                                               |
        v                                               |
   [ First ] --> [ Book 2 ] --> [ Book 3 ] --> [ Last ]-+
   (head->next)                                (head)
```

Because the pivot is the last node, inserting or removing at the front and at the back both take constant time, and there is no `nullptr` at the end of the list. All loops use the book count to stop after one full round.

The class also keeps a `current` pointer that marks the book shown on the display screen. `MoveNext()` advances it, and removing the displayed book moves the pointer forward so it never points to a deleted node.

## Linked List Operations

| Method | Description |
|---|---|
| `Insert(book)` | Insert at the node next to the head (front of the list) |
| `Remove()` | Remove and return the node next to the head |
| `InsertAt(book, index)` | Insert at an index; `index == count` appends, larger or negative indexes wrap around |
| `RemoveAt(index)` | Remove at an index; indexes wrap around the circle |
| `Swap(index1, index2)` | Swap the book data at two indexes (indexes wrap around) |
| `Sort()` | Sort by book ID in ascending order |
| `Reverse()` | Reverse the circular list by re-linking the nodes |
| `MoveNext()` | Move the display to the next book, wrapping at the end |
| `Print()` | Display exactly `count` books and mark the current one |
| `PrintCircularLink()` | Show that the last book links back to the first book |
| `IsEmpty()` / `IsNotEmpty()` | Check whether the list has any books |
| `GetCount()` | Return the number of books |

The class also follows the Rule of Three: a copy constructor, an assignment operator, and a destructor that releases all nodes.

## Requirements

- A C++ compiler with C++11 support or later (g++, clang++, or MSVC)
- Optional: [Visual Studio Code](https://code.visualstudio.com/) with the Microsoft **C/C++** extension

Check that your compiler is installed:

```bash
g++ --version
```

## Build and Run

Clone the repository and move into its folder:

```bash
git clone <your-repository-url>
cd <repository-folder>
```

Compile:

```bash
g++ -std=c++11 main.cpp -o circular
```

Run:

| Platform | Command |
|---|---|
| Windows (PowerShell) | `.\circular.exe` |
| Windows (Command Prompt) | `circular.exe` |
| macOS / Linux | `./circular` |

Keep `main.cpp` and `CircularLinkedList.h` in the same folder, because `main.cpp` includes the header with `#include "CircularLinkedList.h"`.

## Running in VS Code

1. Open the project folder with **File → Open Folder**.
2. Open the terminal with `` Ctrl+` ``.
3. Run the compile command above.
4. Run the executable.

## Menu

```
========================================
  CIRCULAR LIBRARY BOOK DISPLAY SYSTEM
========================================
1.  Display All Books
2.  Insert Book at Head
3.  Remove Book from Head
4.  Insert Book at Index
5.  Remove Book at Index
6.  Swap Books
7.  Sort Books by ID
8.  Reverse Book Collection
9.  Move to Next Book
10. Check Collection Status
11. Exit
Enter your choice:
```

## Sample Output

Option 1 with the predefined books:

```
Index   Book ID Title
-----------------------------------
0       103     Operating Systems   <-- now displayed
1       101     Data Structures
2       105     Computer Networks
3       102     Database Systems
4       104     Software Engineering
Total books: 5
```

Choosing option 9 repeatedly moves the display forward. After the last book it wraps around:

```
Now displaying: [101] Data Structures  (index 1)
Now displaying: [105] Computer Networks  (index 2)
Now displaying: [102] Database Systems  (index 3)
Now displaying: [104] Software Engineering  (index 4)
Now displaying: [103] Operating Systems  (index 0)
The display wrapped around to the first book.
```

Option 10 confirms the circular link:

```
Status: The collection is NOT empty. Total books: 5

Last book  : [104] Software Engineering
   |  next pointer (not nullptr)
   v
First book : [103] Operating Systems
```

## Why a Circular Linked List?

The featured-book screen must visit the books again and again in a cycle. A circular linked list fits this because moving to the next book never needs a special case for the end of the list.

| Feature | Singly Linked List | Circular Linked List |
|---|---|---|
| Last node points to | `nullptr` | The first node |
| Repeated cyclic traversal | Must restart from the head | Continues naturally |
| Access to first and last node | Needs a tail pointer for the last | `head` is the last, `head->next` is the first |
| Insert / remove at the front | O(1) | O(1) |
| Insert at the back | O(n) without a tail pointer | O(1) with the pivot |

## Notes

- Indexes are zero-based.
- `Swap()` and `Sort()` exchange the data stored in nodes (ID and title) rather than re-linking the nodes themselves.
- Because swapping and sorting move data between nodes, the display marker stays on the same position, not on the same book.
- Memory for removed nodes is released with `delete` in `main.cpp`, and the destructor frees any remaining nodes when the program ends.

## Part B: Individual Project

Part B of the lab applies the same circular design to a real-world situation where items are processed repeatedly in a cycle. To adapt this code, change the `BookNode` fields and `CreateBook()` in `CircularLinkedList.h`, then write a new `main.cpp` that demonstrates it with your project's data.

## Author

ABDUL REHMAN
AI /  
University of Engineering and Technology,Lahore

## License

This project was created for educational purposes as part of a university lab assignment.
