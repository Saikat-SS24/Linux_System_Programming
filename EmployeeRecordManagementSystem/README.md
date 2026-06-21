# Employee Record Management System

Project Structure
```bash
emp_system/
├── common.h       
├── shm_helper.h    
├── shm_helper.c   
├── server.c       
├── client.c        
└── Makefile
```
To run

Step - 1: Build

```bash
make
```
Step - 2-> Terminal 1: Start the server

```bash
./server
```
#### The server creates the shared memory.

Step - 3-> Terminal 2: Start the client:

```bash
./client
```
#### The client attaches to the same shared memory. We can run multiple clients at the same time.
