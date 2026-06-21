#include "book_database.h"
#include <algorithm>
#include <cctype>

// ── helpers ──────────────────────────────────────────────────────────────────

static std::string toLower(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return out;
}

// ── constructor ───────────────────────────────────────────────────────────────

BookDatabase::BookDatabase() {
    seedDatabase();
}

// ── seed data ─────────────────────────────────────────────────────────────────

void BookDatabase::seedDatabase() {
    books_ = {
        {1,  "The Great Gatsby",               "F. Scott Fitzgerald", "Fiction",         3, 3},
        {2,  "To Kill a Mockingbird",           "Harper Lee",          "Fiction",         4, 2},
        {3,  "1984",                            "George Orwell",       "Dystopian",       5, 5},
        {4,  "Animal Farm",                     "George Orwell",       "Satire",          3, 1},
        {5,  "Pride and Prejudice",             "Jane Austen",         "Romance",         4, 4},
        {6,  "Sense and Sensibility",           "Jane Austen",         "Romance",         2, 2},
        {7,  "The Catcher in the Rye",          "J.D. Salinger",       "Fiction",         3, 0},
        {8,  "Harry Potter and the Sorcerer",   "J.K. Rowling",        "Fantasy",         6, 4},
        {9,  "The Hobbit",                      "J.R.R. Tolkien",      "Fantasy",         4, 3},
        {10, "The Lord of the Rings",           "J.R.R. Tolkien",      "Fantasy",         3, 2},
        {11, "Brave New World",                 "Aldous Huxley",       "Dystopian",       3, 3},
        {12, "The Alchemist",                   "Paulo Coelho",        "Adventure",       5, 5},
        {13, "Crime and Punishment",            "Fyodor Dostoevsky",   "Classic",         2, 2},
        {14, "The Brothers Karamazov",          "Fyodor Dostoevsky",   "Classic",         2, 1},
        {15, "Moby Dick",                       "Herman Melville",     "Adventure",       2, 2},
        {16, "War and Peace",                   "Leo Tolstoy",         "Historical",      2, 0},
        {17, "Anna Karenina",                   "Leo Tolstoy",         "Romance",         3, 3},
        {18, "The Odyssey",                     "Homer",               "Epic Poetry",     3, 3},
        {19, "Don Quixote",                     "Miguel de Cervantes", "Classic",         2, 2},
        {20, "One Hundred Years of Solitude",   "Gabriel Garcia Marquez","Magical Realism",3,3},
    };
}

// ── public methods ────────────────────────────────────────────────────────────

int BookDatabase::findBookByTitle(const std::string& title) const {
    std::string query = toLower(title);
    for (int i = 0; i < (int)books_.size(); ++i) {
        if (toLower(books_[i].title).find(query) != std::string::npos)
            return i;
    }
    return -1;
}

std::vector<int> BookDatabase::findBooksByAuthor(const std::string& author) const {
    std::string query = toLower(author);
    std::vector<int> results;
    for (int i = 0; i < (int)books_.size(); ++i) {
        if (toLower(books_[i].author).find(query) != std::string::npos)
            results.push_back(i);
    }
    return results;
}

bool BookDatabase::checkAvailability(int index) const {
    return books_[index].availableCopies > 0;
}

bool BookDatabase::borrowBook(int index) {
    if (books_[index].availableCopies > 0) {
        --books_[index].availableCopies;
        return true;
    }
    return false;
}

bool BookDatabase::returnBook(int index) {
    if (books_[index].availableCopies < books_[index].totalCopies) {
        ++books_[index].availableCopies;
        return true;
    }
    return false;
}

const std::vector<Book>& BookDatabase::getAllBooks() const {
    return books_;
}

const Book& BookDatabase::getBook(int index) const {
    return books_[index];
}
