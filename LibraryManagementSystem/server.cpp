#include <iostream>
#include <cstring>
#include <cstdio>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include "common.h"
#include "book_database.h"

// ── ANSI colours ──────────────────────────────────────────────────────────────
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"
#define MAGENTA "\033[35m"

// ── global database (shared; add a mutex for production use) ──────────────────
static BookDatabase g_db;

// ── per-client thread argument ────────────────────────────────────────────────
struct ClientArg {
    int         socket;
    sockaddr_in addr;
};

// ── request handler ───────────────────────────────────────────────────────────
static void handleRequest(int /*clientSock*/, const Request& req, Response& resp) {
    memset(&resp, 0, sizeof(resp));

    switch (req.type) {

    case CHECK_AVAILABILITY: {
        int idx = g_db.findBookByTitle(req.bookTitle);
        if (idx == -1) {
            resp.status = NOT_FOUND;
            snprintf(resp.message, sizeof(resp.message),
                     "Book \"%s\" not found in the library.", req.bookTitle);
        } else {
            const Book& b = g_db.getBook(idx);
            resp.status          = SUCCESS;
            resp.availableCopies = b.availableCopies;
            resp.totalCopies     = b.totalCopies;
            snprintf(resp.message, sizeof(resp.message),
                     "Book: \"%s\" | Author: %s | Genre: %s | "
                     "Available: %d / %d copies",
                     b.title.c_str(), b.author.c_str(), b.genre.c_str(),
                     b.availableCopies, b.totalCopies);
        }
        break;
    }

    case BORROW_BOOK: {
        int idx = g_db.findBookByTitle(req.bookTitle);
        if (idx == -1) {
            resp.status = NOT_FOUND;
            snprintf(resp.message, sizeof(resp.message),
                     "Book \"%s\" not found.", req.bookTitle);
        } else if (!g_db.borrowBook(idx)) {
            resp.status = NOT_AVAILABLE;
            snprintf(resp.message, sizeof(resp.message),
                     "Sorry! \"%s\" has no available copies right now.",
                     req.bookTitle);
        } else {
            const Book& b = g_db.getBook(idx);
            resp.status          = SUCCESS;
            resp.availableCopies = b.availableCopies;
            resp.totalCopies     = b.totalCopies;
            snprintf(resp.message, sizeof(resp.message),
                     "Successfully borrowed \"%s\". Remaining copies: %d",
                     b.title.c_str(), b.availableCopies);
        }
        break;
    }

    case RETURN_BOOK: {
        int idx = g_db.findBookByTitle(req.bookTitle);
        if (idx == -1) {
            resp.status = NOT_FOUND;
            snprintf(resp.message, sizeof(resp.message),
                     "Book \"%s\" not found.", req.bookTitle);
        } else if (!g_db.returnBook(idx)) {
            resp.status = ERROR_RESP;
            snprintf(resp.message, sizeof(resp.message),
                     "Cannot return \"%s\" — all copies already in library.",
                     req.bookTitle);
        } else {
            const Book& b = g_db.getBook(idx);
            resp.status          = SUCCESS;
            resp.availableCopies = b.availableCopies;
            resp.totalCopies     = b.totalCopies;
            snprintf(resp.message, sizeof(resp.message),
                     "Successfully returned \"%s\". Available copies: %d",
                     b.title.c_str(), b.availableCopies);
        }
        break;
    }

    case LIST_ALL_BOOKS: {
        const auto& books = g_db.getAllBooks();
        std::ostringstream oss;
        oss << "\n=== LIBRARY CATALOG (" << books.size() << " books) ===\n";
        for (const auto& b : books) {
            oss << "  [" << b.id << "] " << b.title
                << " — " << b.author
                << " | " << b.genre
                << " | Copies: " << b.availableCopies
                << "/" << b.totalCopies << "\n";
        }
        resp.status = SUCCESS;
        strncpy(resp.message, oss.str().c_str(), sizeof(resp.message) - 1);
        break;
    }

    case SEARCH_BY_AUTHOR: {
        auto indices = g_db.findBooksByAuthor(req.authorName);
        if (indices.empty()) {
            resp.status = NOT_FOUND;
            snprintf(resp.message, sizeof(resp.message),
                     "No books found for author \"%s\".", req.authorName);
        } else {
            std::ostringstream oss;
            oss << "\nBooks by \"" << req.authorName << "\":\n";
            for (int i : indices) {
                const Book& b = g_db.getBook(i);
                oss << "  - " << b.title
                    << " | Genre: " << b.genre
                    << " | Available: " << b.availableCopies
                    << "/" << b.totalCopies << "\n";
            }
            resp.status = SUCCESS;
            strncpy(resp.message, oss.str().c_str(), sizeof(resp.message) - 1);
        }
        break;
    }

    default:
        resp.status = ERROR_RESP;
        snprintf(resp.message, sizeof(resp.message), "Unknown request type.");
        break;
    }
}

// ── per-client thread ─────────────────────────────────────────────────────────
static void* clientThread(void* arg) {
    ClientArg* ca = reinterpret_cast<ClientArg*>(arg);
    int         sock = ca->socket;
    char        clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ca->addr.sin_addr, clientIP, sizeof(clientIP));
    delete ca;

    std::cout << CYAN << "[+] Client connected: " << clientIP << RESET << "\n";

    Request  req;
    Response resp;

    while (true) {
        ssize_t bytes = recv(sock, &req, sizeof(req), 0);
        if (bytes <= 0) break;                // client disconnected

        if (req.type == EXIT_CLIENT) {
            std::cout << YELLOW << "[-] Client " << clientIP
                      << " disconnected." << RESET << "\n";
            break;
        }

        handleRequest(sock, req, resp);
        send(sock, &resp, sizeof(resp), 0);

        std::cout << MAGENTA << "[REQ] " << clientIP
                  << " | Type=" << req.type
                  << " | Status=" << resp.status << RESET << "\n";
    }

    close(sock);
    return nullptr;
}

// ── main ──────────────────────────────────────────────────────────────────────
int main() {
    std::cout << BOLD << GREEN
              << "╔══════════════════════════════════════╗\n"
              << "║   Library Management Server v1.0     ║\n"
              << "╚══════════════════════════════════════╝\n"
              << RESET;

    // Create socket
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock < 0) { perror("socket"); return 1; }

    // Allow port reuse
    int opt = 1;
    setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind
    sockaddr_in addr{};
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(PORT);

    if (bind(serverSock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind"); return 1;
    }

    // Listen
    if (listen(serverSock, 10) < 0) { perror("listen"); return 1; }

    std::cout << GREEN << "[*] Server listening on port " << PORT
              << " ..." << RESET << "\n\n";

    // Accept loop
    while (true) {
        sockaddr_in clientAddr{};
        socklen_t   addrLen = sizeof(clientAddr);
        int clientSock = accept(serverSock, (sockaddr*)&clientAddr, &addrLen);
        if (clientSock < 0) { perror("accept"); continue; }

        ClientArg* arg  = new ClientArg{clientSock, clientAddr};
        pthread_t  tid;
        pthread_create(&tid, nullptr, clientThread, arg);
        pthread_detach(tid);
    }

    close(serverSock);
    return 0;
}
