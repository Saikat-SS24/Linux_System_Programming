FROM ubuntu:22.04
RUN apt update && apt install -y g++
COPY server.cpp /server.cpp
RUN g++ /server.cpp -o /server
EXPOSE 9090
CMD ["/server"]