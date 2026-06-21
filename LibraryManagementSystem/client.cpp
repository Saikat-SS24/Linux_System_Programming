#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "common.h"

// ── ANSI colours ──────────────────────────────────────────────────────────────
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"

// ── helpers ───────────────────────────────────────────────────────────────────

static void printBanner() {
    std::cout << BOLD << CYAN
              << "\n╔══════════════════════════════════════════╗\n"
              << "║     Library Management Client v1.0      ║\n"
              << "╚══════════════════════════════════════════╝\n"
              << RESET;
}

static void printMenu() {
    std::cout << BOLD << "\n┌─── MENU ───────────────────────────────┐\n" << RESET;
    std::cout << "│  " << YELLOW << "1" << RESET << "  Check Book Availability           │\n";
    std::cout << "│  " << YELLOW << "2" << RESET << "  Borrow a Book                     │\n";
    std::cout << "│  " << YELLOW << "3" << RESET << "  Return a Book                     │\n";
    std::cout << "│  " << YELLOW << "4" << RESET << "  List All Books                    │\n";
    std::cout << "│  " << YELLOW << "5" << RESET << "  Search Books by Author            │\n";
    std::cout << "│  " << RED    << "0" << RESET << "  Exit                              │\n";
    std::cout << BOLD << "└────────────────────────────────────────┘\n" << RESET;
    std::cout << "Enter choice: ";
}

static void printResponse(const Response& resp) {
    std::cout << "\n";
    if (resp.status == SUCCESS) {
        std::cout << GREEN << "✔  " << RESET << resp.message << "\n";
    } else if (resp.status == NOT_FOUND) {
        std::cout << RED << "✘  NOT FOUND: " << RESET << resp.message << "\n";
    } else if (resp.status == NOT_AVAILABLE) {
        std::cout << YELLOW << "⚠  NOT AVAILABLE: " << RESET << resp.message << "\n";
    } else {
        std::cout << RED << "✘  ERROR: " << RESET << resp.message << "\n";
    }
}

// ── main ──────────────────────────────────────────────────────────────────────
int main(int argc, char* argv[]) {
    const char* serverIP = (argc >= 2) ? argv[1] : "127.0.0.1";

    printBanner();
    std::cout << BLUE << "[*] Connecting to server at "
              << serverIP << ":" << PORT << " ..." << RESET << "\n";

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port   = htons(PORT);
    if (inet_pton(AF_INET, serverIP, &serverAddr.sin_addr) <= 0) {
        std::cerr << RED << "Invalid server IP address.\n" << RESET;
        return 1;
    }

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << RED
                  << "Connection failed. Make sure the server is running.\n"
                  << RESET;
        return 1;
    }
    std::cout << GREEN << "[✔] Connected to server!\n" << RESET;

    Request  req;
    Response resp;
    int      choice;

    while (true) {
        printMenu();
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 0) {
            memset(&req, 0, sizeof(req));
            req.type = EXIT_CLIENT;
            send(sock, &req, sizeof(req), 0);
            std::cout << CYAN << "Goodbye!\n" << RESET;
            break;
        }

        memset(&req, 0, sizeof(req));

        switch (choice) {

        case 1: // Check availability
            req.type = CHECK_AVAILABILITY;
            std::cout << "Enter book title: ";
            std::cin.getline(req.bookTitle, sizeof(req.bookTitle));
            break;

        case 2: // Borrow
            req.type = BORROW_BOOK;
            std::cout << "Enter book title to borrow: ";
            std::cin.getline(req.bookTitle, sizeof(req.bookTitle));
            break;

        case 3: // Return
            req.type = RETURN_BOOK;
            std::cout << "Enter book title to return: ";
            std::cin.getline(req.bookTitle, sizeof(req.bookTitle));
            break;

        case 4: // List all
            req.type = LIST_ALL_BOOKS;
            break;

        case 5: // Search by author
            req.type = SEARCH_BY_AUTHOR;
            std::cout << "Enter author name: ";
            std::cin.getline(req.authorName, sizeof(req.authorName));
            break;

        default:
            std::cout << RED << "Invalid option. Try again.\n" << RESET;
            continue;
        }

        // Send request
        if (send(sock, &req, sizeof(req), 0) < 0) {
            std::cerr << RED << "Failed to send request.\n" << RESET;
            break;
        }

        // Receive response
        if (recv(sock, &resp, sizeof(resp), 0) <= 0) {
            std::cerr << RED << "Server disconnected.\n" << RESET;
            break;
        }

        printResponse(resp);
    }

    close(sock);
    return 0;
}
