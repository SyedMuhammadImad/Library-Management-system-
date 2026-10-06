// Library Management System
// Stores and retrieves books using a self-balancing AVL Tree, keyed by ISBN,
// so search and insert stay efficient (O(log n)) even as the catalog grows.

#include <iostream>
#include <limits>
#include <string>
using namespace std;

struct Book {
    string ISBN, title, author;
};

struct Node {
    Book book;
    Node *left = nullptr, *right = nullptr;
    int height = 1;
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* createNode(Book book) {
    return new Node{book};
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* insert(Node* root, Book book) {
    if (!root)
        return createNode(book);

    if (book.ISBN < root->book.ISBN)
        root->left = insert(root->left, book);
    else if (book.ISBN > root->book.ISBN)
        root->right = insert(root->right, book);
    else
        return root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && book.ISBN < root->left->book.ISBN)
        return rotateRight(root);

    if (balance < -1 && book.ISBN > root->right->book.ISBN)
        return rotateLeft(root);

    if (balance > 1 && book.ISBN > root->left->book.ISBN) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && book.ISBN < root->right->book.ISBN) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* search(Node* root, string ISBN) {
    if (!root || root->book.ISBN == ISBN)
        return root;

    return ISBN < root->book.ISBN ? search(root->left, ISBN) : search(root->right, ISBN);
}

void inOrder(Node* root) {
    if (!root) return;

    inOrder(root->left);
    cout << root->book.ISBN << " - " << root->book.title << " by " << root->book.author << endl;
    inOrder(root->right);
}

void destroy(Node* root) {
    if (!root) return;
    destroy(root->left); destroy(root->right); delete root;
}

int main() {
    Node* root = nullptr;
    int choice;
    string ISBN, title, author;

    while (true) {
        cout << "\n1. Add Book\n2. Search Book\n3. Display Books\n4. Exit\nEnter choice: ";
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cerr << "Invalid input: enter a menu number." << endl;
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "Enter ISBN: "; getline(cin, ISBN);
            cout << "Enter Title: "; getline(cin, title);
            cout << "Enter Author: "; getline(cin, author);
            if (ISBN.empty() || title.empty() || author.empty()) { cerr << "Book fields cannot be empty." << endl; continue; }
            root = insert(root, {ISBN, title, author});
        } else if (choice == 2) {
            cout << "Enter ISBN to search: "; getline(cin, ISBN);
            Node* found = search(root, ISBN);
            cout << (found ? "Book found: " + found->book.ISBN + " - " + found->book.title + " by " + found->book.author : "Book not found.") << endl;
        } else if (choice == 3) {
            cout << "All Books (Sorted by ISBN):\n";
            inOrder(root);
        } else if (choice == 4) break;
    }
    destroy(root);
    return 0;
}
