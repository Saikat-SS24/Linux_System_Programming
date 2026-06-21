#ifndef BOOK_DATABASE_H
#define BOOK_DATABASE_H

#include <string>
#include <vector>
#include "common.h"

struct Book {
    int         id;
    std::string title;
    std::string author;
    std::string genre;
    int         totalCopies;
    int         availableCopies;
};

class BookDatabase {
public:
    BookDatabase();

    // Returns index of found book, -1 if not found
    int findBookByTitle(const std::string& title) const;

    // Returns all books by a given author
    std::vector<int> findBooksByAuthor(const std::string& author) const;

    // Check availability of a book
    bool checkAvailability(int index) const;

    // Borrow a book (decrease available copies)
    bool borrowBook(int index);

    // Return a book (increase available copies)
    bool returnBook(int index);

    // Get all books
    const std::vector<Book>& getAllBooks() const;

    // Get book at index
    const Book& getBook(int index) const;

private:
    std::vector<Book> books_;
    void              seedDatabase();
};

#endif // BOOK_DATABASE_H
