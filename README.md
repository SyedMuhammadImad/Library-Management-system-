# Library Management System (AVL Tree)

A console-based C++ library catalog that stores books in a **self-balancing AVL tree**,
keyed by ISBN, so inserts and searches stay fast (`O(log n)`) even as the catalog scales.

## Features

- Add a book (ISBN, title, author)
- Search for a book by ISBN
- Display all books in sorted order (in-order traversal)
- Automatic tree rebalancing on insert (left, right, left-right, right-left rotations)

## Data Structure

- **AVL Tree** implemented from scratch, keyed on ISBN
- Each node tracks its height for O(1) balance-factor checks
- Rebalancing handled via standard `rotateLeft` / `rotateRight` operations

## How to Run

```bash
g++ main.cpp -o library_management_system
./library_management_system
```

## Menu Options

```
1. Add Book
2. Search Book
3. Display Books
4. Exit
```

## Tech

- C++
- Custom AVL tree (no STL container used for storage)
