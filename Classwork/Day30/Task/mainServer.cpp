// server.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>

class Employee {
public:
    std::string name;
    int id;
    double salary;

    void print() const {
        std::cout << "\nEmployee details received:\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "ID: " << id << "\n";
        std::cout << "Salary: " << salary << "\n";
    }
};

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    const int PORT = 8080;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen failed");
        close(server_fd);
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << "...\n";

    if ((client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len)) < 0) {
        perror("accept failed");
        close(server_fd);
        return 1;
    }

    std::cout << "Client connected.\n";

    char buffer[1024];
    int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes <= 0) {
        std::cerr << "No data received.\n";
        close(client_fd);
        close(server_fd);
        return 1;
    }
    buffer[bytes] = '\0';

    std::string data(buffer);
    std::istringstream iss(data);
    std::string token;
    Employee emp;

    std::getline(iss, emp.name, '|');
    std::getline(iss, token, '|'); emp.id = std::stoi(token);
    std::getline(iss, token, '|'); emp.salary = std::stod(token);

    emp.print();

    close(client_fd);
    close(server_fd);
    return 0;
}