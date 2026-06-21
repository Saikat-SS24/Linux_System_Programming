
# Library Management System

Project Structure

```bash
library_system/
├── common.h           
├── book_database.h    
├── book_database.cpp 
├── server.cpp         
├── client.cpp         
└── Makefile           
```

To run

- Step - 1: Build

```bash
make
```
- Step - 2: Terminal 1: Start the server

```bash
./server
```

- Step - 3: Open Terminal 2, start the client

```bash
./client           # connects to localhost
./client 192.168.x.x  # or any remote IP
```




