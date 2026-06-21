// client.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class Employee {
public:
    std::string name;
    int id;
    double salary;

    std::string toString() const {
        return name + "|" + std::to_string(id) + "|" + std::to_string(salary);
    }
};

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    const char* SERVER_IP = "127.0.0.1";  
    const int PORT = 8080;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported.\n";
        close(sock);
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect failed");
        close(sock);
        return 1;
    }

    Employee emp;
    std::cout << "Enter employee name: ";
    std::getline(std::cin, emp.name);
    std::cout << "Enter employee ID: ";
    std::cin >> emp.id;
    std::cout << "Enter employee salary: ";
    std::cin >> emp.salary;

    std::string data = emp.toString();
    send(sock, data.c_str(), data.size(), 0);

    std::cout << "Employee data sent to server.\n";

    close(sock);
    return 0;
}