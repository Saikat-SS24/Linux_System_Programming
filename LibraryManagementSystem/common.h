#ifndef COMMON_H
#define COMMON_H

#include <string>

#define PORT 8080
#define MAX_BUFFER 1024
#define MAX_BOOKS 100

// Request types from client to server
enum RequestType {
    CHECK_AVAILABILITY = 1,
    BORROW_BOOK        = 2,
    RETURN_BOOK        = 3,
    LIST_ALL_BOOKS     = 4,
    SEARCH_BY_AUTHOR   = 5,
    EXIT_CLIENT        = 0
};

// Response status from server to client
enum ResponseStatus {
    SUCCESS       = 200,
    NOT_FOUND     = 404,
    NOT_AVAILABLE = 409,
    ERROR_RESP    = 500
};

// Request packet sent by client
struct Request {
    RequestType type;
    char        bookTitle[256];
    char        authorName[256];
};

// Response packet sent by server
struct Response {
    ResponseStatus status;
    char           message[768];
    int            availableCopies;
    int            totalCopies;
};

#endif // COMMON_H
